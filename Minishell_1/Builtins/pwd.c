/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouhsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 07:22:24 by saouhsan          #+#    #+#             */
/*   Updated: 2024/02/19 07:22:26 by saouhsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built_in_pwd(t_minishell *ms)
{
	char	cwd[PATH_MAX];
	char	*dir;

	dir = getcwd(cwd, sizeof(cwd));
	if (!dir)
		end_program(ms, ER_GETCWD);
	printf("%s\n", dir);
	free(dir);
	return ;
}
