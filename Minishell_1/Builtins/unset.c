#include "../minishell.h"

/*
Export environment variables, create new ones and replace old ones
Use unset to remove some of them
Check the result with env

Check whether the environment variables entered as arguments are valid
Must start with a letter/number/_
Check if an environment variable already exists
If it is behind a pipe, delete the environment variable because it is
an unset of the child process
*/

t_env	*node_to_delete(t_env *env, char *target_key)
{
	t_env	*current;
	t_env	*target_node;

	current = env;
	target_node = NULL;
	while (current)
	{
		if(!ft_strcmp(current->key, target_key))
		{
			target_node = current;
			return (target_node);
		}
		current = current->next;
	}
	return (NULL);
}

void	built_in_unset(t_minishell *ms)
{
	t_cmd_table	*current;
	t_env		*target_node;
	char		**target_keys;
	int			i;

	current = ms->cmd_table;
	i = 0;
	if (!current || current->next == NULL)
		return ;
	target_keys = current->args;
	while(target_keys[i])
	{
		target_node = node_to_delete(ms->env, target_keys[i]);
		if (target_node != NULL)
		{
			while (current->next != target_node)
				current = current->next;
			target_node = current->next;
			current->next = target_node->next->next;
			free(target_node->key);
			free(target_node->value);
			free(target_node);
		}
		i++;
	}
	return ;
}
