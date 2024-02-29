/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouhsan <saouhsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:58:29 by saouhsan          #+#    #+#             */
/*   Updated: 2024/02/28 21:58:46 by saouhsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_nb_cuts(char const *s, char c)
{
	size_t	i;
	size_t	nbcuts;

	i = 0;
	nbcuts = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			nbcuts++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (nbcuts);
}

static char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	free_tab(char ***tab, int k)
{
	while (k >= 0)
	{
		free(*tab[k]);
		k--;
	}	
	free(*tab);
}

static void	ft_str_cuts(char **tab, const char *s, char c, size_t cuts)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 1;
	k = 0;
	while (s[i] && k < cuts)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[(i + j)] && s[i + j] != c)
			j++;
		if (j > 0)
		{
			tab[k] = malloc(sizeof(char) * (j + 1));
			if (!tab[k])
				return (free_tab(&tab, k));
			ft_strncpy(tab[k], &((char *)s)[i], j);
			k++;
			i = i + j;
		}
		j = 1;
	}
	tab[k] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		nbcuts;

	if (!s)
		return (NULL);
	nbcuts = ft_nb_cuts(s, c);
	tab = (char **)malloc(sizeof(char *) * (nbcuts + 1));
	if (tab == NULL)
		return (NULL);
	ft_str_cuts(tab, s, c, nbcuts);
	return (tab);
}
