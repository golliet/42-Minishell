/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 15:01:46 by golliet           #+#    #+#             */
/*   Updated: 2018/02/14 15:46:38 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_put(char *str, char **env)
{
	write(2, str, ft_strlen(str));
	ft_putchar_fd('\n', 2);
	return (env);
}

int		ft_find_in_env(char **env, char *str)
{
	int i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], str, ft_strlen(str)) != 0)
		i++;
	return (i);
}

void	exit_and_free(char **t, char ***newenv, char *str)
{
	ft_freetab2d(t);
	ft_freetab2d(*newenv);
	free(str);
	exit(0);
}

void	ft_if(char ***env, char *path, char *curr, char *after)
{
	int i;

	if ((i = ft_find_in_env(*env, "OLDPWD=")) == ft_tab2dlen(*env))
	{
		ft_realloc_setenv(env, path);
		free(path);
	}
	else
	{
		free((*env)[i]);
		(*env)[i] = path;
	}
	free(curr);
	free(after);
}

char	**ft_error_home(char **env, char *str)
{
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putendl_fd(str, 2);
	return (env);
}
