/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouhsan <saouhsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 07:48:46 by saouhsan          #+#    #+#             */
/*   Updated: 2024/02/21 06:28:41 by saouhsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
if arg error
if current->content == "env" and current->token == word 
error
*/

void	built_in_env(t_env *env)
{
	t_env	*head;
	char	*env_unset;

	head = env;
	env_unset = find_env_var(head, "_");
	if (!env_unset)
	{
		error_handler("env", NO_F_OR_D);
		return ;
	}
	while (head)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	return ;
}
