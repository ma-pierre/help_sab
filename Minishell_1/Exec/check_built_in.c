/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouhsan <saouhsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:14:14 by saouhsan          #+#    #+#             */
/*   Updated: 2024/02/28 22:15:15 by saouhsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*grab_value(t_env *env, char *key)
{
	t_env	*current;
	char	*value;

	current = env;
	value = NULL;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			value = ft_strdup(current->value);
			if (!value)
				return (NULL);
			return (value);
		}
		current = current->next;
	}
	return (NULL);
}

char	**find_cmd_path(t_env *env, char *key)
{
	char	**path;
	char	*value;

	value = grab_value(env, key);
	if (!value)
		return (NULL);
	path = ft_split(value, ":");
	if (!path)
		return (NULL);
	return (path);
}

int	check_access(t_cmd_table *cmd, char **path)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	cmd_path = cmd->content;
	tmp = NULL;
	i = 0;
	if (!access(cmd_path, F_OK | X_OK))
	{
		cmd->cmd_path = ft_strdup(cmd_path);
		return (1);
	}
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(tmp, cmd_path);
		free(tmp);
		if (!access(cmd_path, F_OK | X_OK))
		{
			cmd->cmd_path = ft_strdup(cmd_path);
			return (1);
		}
		i++;
		error_handler(cmd->content, ER_CMD_NOT_FOUND); // or permission
	}
	return (0);
}

void	launch_bash_builtin(t_minishell	*ms, t_cmd_table *cmd)
{
	char	*path;

	path = find_cmd_path(ms->env, "PATH");
	if (check_access(cmd, path))
		if (execve(cmd->cmd_path, cmd->args, ms->env_copy) == -1)
			ms->exit_status = errno;
	else
		//back to prompt 
	return ;
}

void	check_built_in(t_minishell *ms, t_cmd_table *cmd)
{
	if (cmd->cmd == CMD_CD)
		built_in_cd(ms,cmd);
	else if (cmd->cmd == CMD_ECHO)
		built_in_echo(ms,cmd);
	else if (cmd->cmd == CMD_ENV)
		built_in_env(ms->env);
	else if (cmd->cmd == CMD_EXIT)
		built_in_exit();
	else if (cmd->cmd == CMD_EXPORT)
	{
		built_in_export();
		//reset_get_env
	}
	else if (cmd->cmd == CMD_PWD)
		built_in_pwd(ms);
	else if (cmd->cmd == CMD_UNSET)
		built_in_unset();
	else if (cmd->cmd == CMD_OTHER)
		launch_bash_builtin(ms,cmd);
	return ;
}
