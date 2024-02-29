/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouhsan <saouhsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 04:48:20 by saouhsan          #+#    #+#             */
/*   Updated: 2024/02/28 22:28:29 by saouhsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built_in_echo(t_minishell *ms)
{
	t_cmd_table	*cmd;
	int			flag_nl;
	int			i;

	cmd = ms->cmd_table;
	flag_nl = 0;
	if (!cmd->args)
		printf("\n");
	if (!ft_strcmp(cmd->args[0], "-n"))
	{
		flag_nl = 1;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!flag_nl)
		printf("\n");
	ms->exit_status = EXIT_SUCCESS;
	return ;
}
