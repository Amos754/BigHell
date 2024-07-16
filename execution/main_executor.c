#include "../minishell.h"

// t_tree	*tree_pointer(t_tree *tree, int param)
// {
// 	if (!tree)
// 		return (NULL);
// 	printf("test in : %s\n", (char *)tree->data);
// 	if (tree->type == param)
// 	{
// 		printf("test in  good : %s\n", (char *)tree->data);
// 		printf("GOOD!\n");
// 		return (tree);
// 	}
// 	if (tree->type != param )
// 	{
// 		tree_pointer(tree->left, param);
// 		tree_pointer(tree->right, param);
// 	}
// 	return (tree);
// }

int	tree_finder(t_tree *tree, int param, int nb)
{

	if (!tree)
		return (nb);
	if (tree->type == param)
		nb++;
	nb = tree_finder(tree->left, param, nb);
	nb = tree_finder(tree->right, param, nb);
	return (nb);
}

int	ast_executor(t_tree *tree, t_envb *env)
{
	int	return_value;
	int	fd[2];
	int	bad_event;
	int	pipe_counter;
	int	*hd_pipes;

	return_value = 0;
	pipe_counter = tree_finder(tree, A_PIPE, 0);
	// printf("%s\n", (char *)tree->right->left->right->data);
	// printf("%d\n", tree->right->right->right->type);
	if (pipe_counter > 0)
		return (exec_simple_cmd(tree, env));
	if (!do_redirection(tree, 0))
		return (exec_simple_cmd(tree, env));
	return (0);
}