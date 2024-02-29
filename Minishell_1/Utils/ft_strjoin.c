/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouhsan <saouhsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:00:32 by saouhsan          #+#    #+#             */
/*   Updated: 2024/02/28 22:00:34 by saouhsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s1_s2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s1_s2 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s1_s2)
		return (NULL);
	while (s1[i])
	{
		s1_s2[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s1_s2[i + j] = s2[j];
		j++;
	}
	s1_s2[i + j] = '\0';
	//free(s1);
	//free(s2);
	return (s1_s2);
}
