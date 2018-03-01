/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 14:11:37 by golliet           #+#    #+#             */
/*   Updated: 2018/02/13 14:21:17 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_tab(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}

char	**ft_newtab2d(char **env)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (*env == NULL)
		return (NULL);
	while (env[j])
		j++;
	if (!(new = (char**)malloc(sizeof(char*) * (j + 1))))
		return (NULL);
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	ft_freetab2d(char **t)
{
	int i;

	i = 0;
	while (t[i])
	{
		free(t[i]);
		i++;
	}
	if (t)
		free(t);
}

int		ft_tab2dlen(char **t)
{
	int i;

	i = 0;
	while (t[i])
		i++;
	return (i);
}
