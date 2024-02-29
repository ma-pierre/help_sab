/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouhsan <saouhsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 05:57:00 by saouhsan          #+#    #+#             */
/*   Updated: 2024/02/28 21:42:22 by saouhsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_key_env(t_minishell *ms, char *env_slice, int i)
{
	char	*key;
	int		index;

	index = 0;
	key = malloc(sizeof(char) * i + 1);
	if (!key)
		end_program(ms, ER_MALLOC);
	while (index < i)
	{
		key[index] = env_slice[index];
		index++;
	}
	key[index] = '\0';
	return (key);
}

char	*find_value_env(t_minishell *ms, char *env_slice, int i)
{
	char	*value;
	int		index;
	int		index2;

	value = NULL;
	index = i + 1;
	index2 = 0;
	while (env_slice[i] != '\0')
		i++;
	value = malloc(sizeof(char) * (i - index + 1));
	if (!value)
		end_program(ms, ER_MALLOC);
	while (env_slice[index] != '\0')
	{
		value[index2] = env_slice[index];
		index++;
		index2++;
	}
	value[index2] = '\0';
	return (value);
}

void	collect_env_data(t_minishell *ms, t_env *env, int j)
{
	t_env	*current;
	int		i;

	current = env;
	i = 0;
	while (ms->env_copy[j][i] != '=')
		i++;
	current->key = find_key_env(ms, ms->env_copy[j], i);
	current->value = find_value_env(ms, ms->env_copy[j], i);
	return ;
}

void	create_env_data_node(t_minishell *ms, int i)
{
	t_env	*current;
	t_env	*new;
	int		j;

	current = ms->env;
	j = 0;
	while (j < i)
	{
		collect_env_data(ms, current, j);
		new = malloc(sizeof(*new));
		if (new == NULL)
			end_program(ms, ER_MALLOC);
		current->next = new;
		new->key = NULL;
		new->value = NULL;
		new->next = NULL;
		current = current->next;
		j++;
	}
	return ;
}

void	duplicate_env(t_minishell *ms, char **envp)
{
	int		i;
	int		j;

	i = 0;
	while (envp[i])
		i++;
	if (ms->env_copy != NULL)
		free_array(ms->env_copy);
	if (ms->env_copy == NULL)
		ms->env_copy = malloc(sizeof(char *) * (i + 1));
	if (!ms->env_copy)
		end_program(ms, ER_MALLOC);
	j = 0;
	while (j < i)
	{
		ms->env_copy[j] = ft_strdup(envp[j]);
		if (!ms->env_copy)
			end_program(ms, ER_MALLOC);
		j++;
	}
	create_env_data_node(ms, i);
	ms->env_copy[i] = NULL;
	return ;
}
