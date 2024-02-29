/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouhsan <saouhsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 04:19:21 by saouhsan          #+#    #+#             */
/*   Updated: 2024/02/20 04:19:27 by saouhsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_current_dir_path(t_minishell *ms)
{
	char	cwd[PATH_MAX];
	char	*current_dir;

	current_dir = getcwd(cwd, sizeof(cwd));
	if (!current_dir)
		end_program(ms, ER_GETCWD);
	return (current_dir);
}

char	*get_absolut_path(char *relative_path, char *cwd)
{
	char	*absolut_path;
	char	*tmp;

	tmp = ft_strjoin(cwd, "/");
	absolut_path = ft_strjoin(tmp, relative_path);
	free(tmp);
	free(relative_path);
	return (absolut_path);
}

void	update_env(t_minishell *ms, char *cwd, char *dest_wd )
{
	t_env	*env;

	env = ms->env;
	while (env)
	{
		if (!ft_strcmp(env->key, "PWD"))
		{
			free(env->value);
			env->value = ft_strdup(dest_wd);
		}
		else if (!ft_strcmp(env->key, "OLDPWD"))
		{
			free(env->value);
			env->value = ft_strdup(cwd);
		}
		env = env->next;
	}
	return ;
}
