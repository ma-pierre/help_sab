/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouhsan <saouhsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 06:01:04 by saouhsan          #+#    #+#             */
/*   Updated: 2024/02/28 21:42:24 by saouhsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_env_var(t_env *env, char *target_key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (!ft_strcmp(current->key, target_key))
			retunt(current->value);
		current = current->next;
	}
	return (NULL);
}
