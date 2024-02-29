#include "minishell.h"

t_cmd_table	*reset_cmd_list(t_minishell *ms)
{
	t_cmd_table	*current;
	t_cmd_table	*tmp;

	current = ms->cmd_table;
	while (current)
	{
		free(current->content);
		free_array(current->args);
		free(current->cmd_path);
		//close fd??
		if(current->next != NULL)
		{
			tmp = current->next;
			free(current);
			current = tmp;
		}
		else
			break;
	}
	return (current);
}

void	reset_for_next_input(t_minishell *ms)
{
	if(ms->valid_input)
		free_array(ms->valid_input);
	ms->valid_input = NULL;
	ms->flag_pipe = 0;
	ms->flag_redir = 0;
	ms->flag_hd = 0;
	ms->cmd_table = reset_cmd_list(ms->cmd_table);
	ms->cmd_nb = 0;
	return ;
}

void	error_handler(t_minishell *ms, char *cmd_name, int *error_id)
{
	if (error_id == ER_INVALID_USE_BI)
		printf("%s %s: %s\n", MS, cmd_name, NO_F_OR_D);
	if (error_id == ER_GENERAL)
		printf("%s %s: %s\n", MS, cmd_name, ARG);
	if (error_id == ER_CMD_NOT_FOUND)
		printf("Command '%s' %s\n", cmd_name, NOT_FOUND);
	reset_for_next_input(ms);
	ms->exit_status = error_id;
	return;
}
//fd ???