#include "minishell.h"

void	free_array(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_env(t_env *env)
{
	t_env	*current;
	t_env	*next_node;

	current = env;
	while(current)
	{
		free(current->key);
		free(current->value);
		next_node = current->next;
		free(current);
		current = next_node;
	}
}

void	free_cmd_list(t_cmd_table *cmd)
{
	t_cmd_table	*current;
	t_cmd_table	*next_node;

	current = cmd;
	while (current)
	{
		if (current->content)
			free(current->content);
		if (current->args)
			free_array(current->args);
		if (current->filename)
			free(current->filename);
		if (current->cmd_path)
			free(current->cmd_path);
		if(current->next != NULL)
		{
			next_node = current->next;
			next_node->prev = NULL;
			free(current);
			current = next_node;
		}
		else
		{
			if (current->content)
				free(current);
			current = current->next;
		}
	}
	return;
}

//void	free_heredoc()
//{

//}

void	end_program(t_minishell *ms, char *err_description)
{
	if (ms->env_copy)
		free_array(ms->env_copy);
	if (ms->valid_input)
		free_array(ms->valid_input);
	if (ms->env)
		free_env(ms->env);
	if (ms->cmd_table)
		free_cmd_list(ms->cmd_table);
	free(ms->cmd_table);
	free(ms);
	rl_clear_history();
	printf("%s\n", err_description);
	//perror("exit");
	exit(EXIT_FAILURE);
}
