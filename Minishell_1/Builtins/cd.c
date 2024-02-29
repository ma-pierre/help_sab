/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouhsan <saouhsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 04:19:38 by saouhsan          #+#    #+#             */
/*   Updated: 2024/02/20 04:22:32 by saouhsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ch_dir_home(t_minishell *ms, t_cmd_table *cmd, char *cwd)
{
	t_cmd_table	*current;

	current = cmd;
	if (!current->args)
	{
		if (find_env_var(ms->env, "HOME") != NULL)
		{
			if (chdir(getenv("HOME")) != 0)
				end_program(ms, ER_CHDIR);
			ms->exit_status = EXIT_SUCCESS;
			update_env(ms, cwd, getenv("HOME"));
			return ;
		}
		printf("%s cd: HOME %s", MS, NOT_SET);
		ms->exit_status = EXIT_FAILURE;
		return ;
	}
	else if (!ft_strcmp(current->args[0], "~"))
	{
		if (chdir(getenv("HOME")) != 0)
			end_program(ms, ER_CHDIR);
	}
	ms->exit_status = EXIT_SUCCESS;
	update_env(ms, cwd, getenv("HOME"));
	return ;
}

void	ch_dir_oldpwd(t_minishell *ms, t_cmd_table *cmd, char *cwd)
{
	t_cmd_table	*current;

	current = cmd;
	if (find_env_var(ms->env, "OLDPWD") != NULL)
	{
		if (chdir(getenv("OLDPWD")) != 0)
			end_program(ms, ER_CHDIR);
		ms->exit_status = EXIT_SUCCESS;
		update_env(ms, cwd, getenv("OLDPWD"));
		return ;
	}
	printf("%s cd: OLDPWD %s", MS, NOT_SET);
	ms->exit_status = EXIT_FAILURE;
	return ;
}

int	ch_directory(t_minishell *ms, t_cmd_table *cmd, char *cwd)
{
	t_cmd_table	*current;
	int			i;

	current = cmd;
	current->args[0] = get_absolut_path(current->args[0], cwd);
	i = chdir(current->args[0]);
	if (i == 0)
		update_env(ms, cwd, current->args[0]);
	return (i);
}

void	built_in_cd(t_minishell *ms, t_cmd_table *cmd)
{
	t_cmd_table	*current;
	char		*cwd;

	current = cmd;
	cwd = get_current_dir_path(ms);
	if (current->nb_args > 1)
		return (error_handler("cd", ARG));
	else if (!current->args || !ft_strcmp(current->args[0], "~"))
		return (ch_dir_home(ms, current, cwd));
	else if (!ft_strcmp(current->args[0], "-"))
		return (ch_dir_oldpwd(ms, current, cwd));
	if (ch_directory(ms, current, cwd))
	{
		error_handler("cd", NO_F_OR_D);
		return ;
	}
	ms->exit_status = EXIT_SUCCESS;
	return ;
}
