#include "../minishell.h"

t_command *create_command_node(char *cmd) {
    t_command *new_node = malloc(sizeof(t_command));
    if (!new_node) return NULL;
    new_node->args = ft_split(cmd, ' ');
    new_node->output_file = NULL;
    new_node->input_file = NULL;
    new_node->append_output = 0;
    new_node->next = NULL;
    return new_node;
}

void add_command(t_piped *piped, char *cmd) {
    t_command *new_node = create_command_node(cmd);
    if (!new_node) return;

    if (!piped->commands) {
        piped->commands = new_node;
    } else {
        t_command *current = piped->commands;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void parse_redirections(t_command *cmd_node) {
    for (int i = 0; cmd_node->args[i]; i++) 
    {
        if (strcmp(cmd_node->args[i], ">") == 0) 
        {
            cmd_node->output_file = strdup(cmd_node->args[i + 1]);
            cmd_node->args[i] = NULL;
        } 
        else if (strcmp(cmd_node->args[i], ">>") == 0) {
            cmd_node->output_file = strdup(cmd_node->args[i + 1]);
            cmd_node->append_output = 1;
            cmd_node->args[i] = NULL;
        } else if (strcmp(cmd_node->args[i], "<") == 0) {
            cmd_node->input_file = strdup(cmd_node->args[i + 1]);
            cmd_node->args[i] = NULL;
        }
    }
}

int creat_pipe(t_piped *piped, char **envp, char **av, int num_cmds) {
    int i = 0;

    piped->num_cmds = num_cmds;
    piped->env = envp;
    piped->commands = NULL;
    for (int j = 0; j < num_cmds; j++) {
        add_command(piped, av[j]);
    }
    piped->fd = malloc(sizeof(int *) * (num_cmds - 1));
    for (int j = 0; j < num_cmds - 1; j++) {
        piped->fd[j] = malloc(sizeof(int) * 2);
        if (pipe(piped->fd[j]) == ERROR)
            return 0;
    }
    piped->pid = malloc(sizeof(pid_t) * num_cmds);
    piped->stdin_cpy = dup(0);
    piped->stdout_cpy = dup(1);
    while (strncmp("PATH=", envp[i], 5))
        i++;
    piped->paths = ft_split(envp[i] + 5, ':');

    t_command *current = piped->commands;
    while (current) {
        parse_redirections(current);
        current = current->next;
    }

    return 1;
}

char *get_cmd_pipe(t_piped *piped, char *av) {
    int i = 0;
    char *fullcmd;
    char *tmp;

    if (!is_builtin(av))
        return (av);
    while (piped->paths[i]) {
        tmp = ft_strjoin(piped->paths[i], "/");
        fullcmd = ft_strjoin(tmp, av);
        free(tmp);
        if (access(fullcmd, F_OK | X_OK) == 0)
            return fullcmd;
        free(fullcmd);
        i++;
    }
    return NULL;
}

void    red_dealer(char *cmd, t_command *cmd_node, t_piped *piped)
{
    int fd;
    pid_t   pid;
    pid = fork();
    if (pid == 0)
    {
        if (cmd_node->input_file) 
        {
            fd = open(cmd_node->input_file, O_RDONLY);
            if (fd == ERROR) {
                perror("Input file open error");
                exit(1);
            }
            dup2(fd, 0);
            execve(cmd, cmd_node->args, piped->env);
            close(fd);
        }
        if (cmd_node->output_file) 
        {
            if (cmd_node->append_output) {
                fd = open(cmd_node->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            } else {
                fd = open(cmd_node->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }
            if (fd == ERROR) {
                perror("Output file open error");
                exit(1);
            }
            dup2(fd, 1);
            execve(cmd, cmd_node->args, piped->env);
            close(fd);
        }
    }
    else
    {
        wait(&pid);
        close(fd);
    }
}

void execute_command(t_piped *piped, int cmd_index, t_envb *env) 
{
    t_command *cmd_node = piped->commands;
    pid_t   pid;
    char *cmd;

    for (int i = 0; i < cmd_index; i++) 
    {
        cmd_node = cmd_node->next;
    }
    cmd = get_cmd_pipe(piped, cmd_node->args[0]);
    if (!cmd) 
    {
        perror("Command not found");
        exit(1);
    }
    if (cmd_node->input_file || cmd_node->output_file)
        red_dealer(cmd, cmd_node, piped);
    if (cmd_index == 0) {
        dup2(piped->fd[cmd_index][1], 1);
    } else if (cmd_index == piped->num_cmds - 1) {
        dup2(piped->fd[cmd_index - 1][0], 0);
    } else {
        dup2(piped->fd[cmd_index - 1][0], 0);
        dup2(piped->fd[cmd_index][1], 1);
    }
    
    for (int i = 0; i < piped->num_cmds - 1; i++) {
        close(piped->fd[i][0]);
        close(piped->fd[i][1]);
    }
    if (!is_builtin(cmd_node->args[0]))
    {
        exec_builtin(cmd_node->args, env);
        exit(0);
    }
    execve(cmd, cmd_node->args, piped->env);
    perror("execve failed");
    exit(1);
}

int end_process(t_piped *piped) {
    int status;
    for (int i = 0; i < piped->num_cmds - 1; i++) {
        close(piped->fd[i][0]);
        close(piped->fd[i][1]);
    }
    for (int i = 0; i < piped->num_cmds; i++) {
        waitpid(piped->pid[i], &status, 0);
    }
    dup2(piped->stdout_cpy, 0);
    dup2(piped->stdin_cpy, 1);
    close(piped->stdin_cpy);
    close(piped->stdout_cpy);
    return WEXITSTATUS(status);
}

int main_pipe(int ac, char **av, t_envb *env)
{
    t_piped piped;
    if (!creat_pipe(&piped, env->env, av, ac)) {
        printf("Pipe error\n");
        return 1;
    }

    for (int i = 0; i < ac; i++) {
        piped.pid[i] = fork();
        if (piped.pid[i] == 0) {
            execute_command(&piped, i, env);
        }
    }

    return end_process(&piped);
}
