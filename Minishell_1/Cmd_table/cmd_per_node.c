/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_per_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouhsan <saouhsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 06:05:20 by saouhsan          #+#    #+#             */
/*   Updated: 2024/02/28 23:37:26 by saouhsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	args_tab_size(t_cmd_table *cmd)
{
	t_cmd_table	*current;
	int			i;

	current = cmd;
	i = 0;
	while (current && current->next->token != T_CONTROL_OP)
	{
		if (current->next->token == T_REDIRECTION)
			current = current->next->next;
		else
		{
			current = current->next;
			i++;
		}
	}
	return (i);
}

char	**create_cmd_args_array(t_cmd_table *cmd)
{
	t_cmd_table	*current;
	int			i;
	int			j;
	char		**args;

	current = cmd;
	j = 0;
	args = NULL;
	i = args_tab_size(current);
	current->nb_args = i;
	args = malloc(sizeof(char *) * i + 1);
	if (!args)
		return (NULL);
	while (current && current->next->token != T_CONTROL_OP)
	{
		if (current->next->token == T_REDIRECTION)
			current = current->next->next;
		else
		{
			args[j] = ft_strdup(current->next->content);
			current = current->next;
			j++;
		}
	}
	args[j] = NULL;
	return (args);
}

void	del_cmd_list_node(t_cmd_table *cmd)
{
	t_cmd_table	*current;

	current = cmd;
	while (current && current->token != T_CONTROL_OP)
	{
		if (current->next->token == T_REDIRECTION)
			current = current->next->next;
		else if (current->next->token == T_WORD)
		{
			current->next = current->next->next;
			current->next->next->prev = current;
			free(current->next->content);
			free(current->next);
		}
	}
	return ;
}

void	split_list_by_cmd(t_minishell *ms, t_cmd_table *cmd)
{
	t_cmd_table	*current;

	current = cmd;
	while (current)
	{
		if (current->next->token == T_CONTROL_OP)
			current = current->next;
		else if (current->token == T_REDIRECTION)
			current = current->next->next;
		else if (current->token == T_WORD)
		{
			current->args = create_cmd_args_array(current);
			if (!current->args)
				end_program(ms, ER_MALLOC);
			del_cmd_list_node(current);
			current = current->next;
		}
	}
	return ;
}
//count cmd stock in struc