#include "../minishell.h"

/*
Export environment variables, create new ones and replace old ones
Check them with env

export history

*/

void	built_in_export(t_minishell *ms, t_cmd_table *cmd)
{
	t_cmd_table	*current;
	int			i;

	current = cmd;
	i = 0;
	if (cmd->nb_args == 1)
	{
		ms->exit_status = EXIT_SUCCESS;
		return (print_export_history());
	}
	while (cmd->args[i])
	{
		if (export_var())
			ms->exit_status = EXIT_FAILURE; //see msg err
		i++;
	}
	return ;
}


