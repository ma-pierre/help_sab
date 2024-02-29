#include "../minishell.h"

//in parsing when struct cmd_table init strcmp

int	check_built_in(t_minishell *ms)
{
	t_cmd_table	*cmd;

	cmd = ms->cmd_table;
	if (cmd->cmd == CMD_CD)
		return (built_in_cd(cmd), 0);
	else if (cmd->cmd == CMD_ECHO)
		return (built_in_echo(cmd), 0);
	else if (cmd->cmd == CMD_ENV)
		return (built_in_env(ms->env), 0);
	else if (cmd->cmd == CMD_EXIT)
		return (built_in_exit(cmd), 0);
	else if (cmd->cmd == CMD_EXPORT)
	{
		return (built_in_export(), 0);
		//reset_get_env
	}
	else if (cmd->cmd == CMD_PWD)
		return (built_in_pwd(), 0);
	else if (cmd->cmd == CMD_UNSET)
		return (built_in_unset(), 0);
	return (1);
}
