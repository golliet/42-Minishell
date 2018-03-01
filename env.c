/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 11:16:56 by golliet           #+#    #+#             */
/*   Updated: 2018/02/13 15:52:48 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define SIZE ft_strlen

/*
** This function check if the args are correct
*/

static char			**ft_parse(char **t)
{
	char	**pars;
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (t[1][++i])
		if (t[1][i] == '=')
			count++;
	if (count > 1 || t[1][0] == '=')
	{
		ft_putendl_fd("setenv: invalid assignment", 2);
		return (NULL);
	}
	if (count == 0)
	{
		ft_putendl_fd("usage: setenv [NAME]=[VALUE]", 2);
		return (NULL);
	}
	if (!(pars = (char**)malloc(sizeof(char*) * 3)))
		return (NULL);
	pars[0] = ft_strsub(t[1], 0, SIZE(t[1]) - SIZE(ft_strchr(t[1], '=')));
	pars[1] = ft_strdup(ft_strchr(t[1], '='));
	pars[2] = NULL;
	return (pars);
}

/*
** This function realloc tab +1
*/

void				ft_realloc_setenv(char ***env, char *str)
{
	char	**new;
	char	**tmp;
	int		i;

	i = 0;
	if (!(new = (char**)malloc(sizeof(char*) * (ft_tab2dlen(*env) + 1 + 1))))
		return ;
	while ((*env)[i])
	{
		new[i] = (*env)[i];
		i++;
	}
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	free(*env);
	*env = new;
}

/*
** This function check if the var is already set.
** set : change the value
** not set : realloc tab to set the value
*/

void				ft_setenv(char ***env, char **t)
{
	char	**pars;
	char	*tmp;
	int		i;

	i = 0;
	if (!t[1])
		return (ft_putendl_fd("usage: setenv [NAME]=[VALUE]", 2));
	if (t[2])
		return (ft_putendl_fd("setenv: too many arguments", 2));
	if (!(pars = ft_parse(t)))
		return ;
	while ((*env)[i])
	{
		if (ft_strncmp(pars[0], (*env)[i], ft_strlen(pars[0])) == 0)
		{
			tmp = (*env)[i];
			(*env)[i] = ft_strdup(t[1]);
			free(tmp);
			ft_freetab2d(pars);
			return ;
		}
		i++;
	}
	ft_realloc_setenv(env, t[1]);
	ft_freetab2d(pars);
}

/*
** This function realloc tab +1
*/

static void			ft_realloc_unsetenv(char ***env, char *str)
{
	char	**new;
	char	*nstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	nstr = ft_strjoin(str, "=");
	if (!(new = (char**)malloc(sizeof(char*) * (ft_tab2dlen(*env) + 1))))
		return ;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], nstr, ft_strlen(nstr)) == 0)
		{
			free((*env)[i]);
			j++;
		}
		new[i] = (*env)[i + j];
		i++;
	}
	new[i] = NULL;
	free(*env);
	*env = new;
	free(nstr);
}

/*
**This function unset a var if it exist else return NULL and display an error
*/

void				ft_unsetenv(char ***env, char **t)
{
	int		size;
	char	**new;
	int		i;

	i = -1;
	if (!t[1])
		return (ft_putendl_fd("usage: unsetenv [NAME]", 2));
	while (t[1][++i])
		if (t[1][i] == '=')
			return (ft_putendl_fd("unsetenv: var is without '='", 2));
	if (t[2])
		return (ft_putendl_fd("unsetenv: too many arguments", 2));
	i = -1;
	while ((*env)[++i])
		if (ft_strncmp(t[1], (*env)[i], ft_strlen(t[1])) == 0)
			return (ft_realloc_unsetenv(env, t[1]));
	ft_putendl_fd("unsetenv: var does not exist", 2);
}
