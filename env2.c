/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 10:16:14 by golliet           #+#    #+#             */
/*   Updated: 2018/02/16 09:18:31 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define MAX_PARAM 100

void	ft_addenv(char ***env, char *t)
{
	int		i;
	char	*str;
	int		size;

	str = ft_strchr(t, '=');
	size = ft_strlen(t) - ft_strlen(str);
	str = ft_strsub(t, 0, size);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp(str, (*env)[i], ft_strlen(str)) == 0)
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(t);
			free(str);
			return ;
		}
		i++;
	}
	ft_realloc_setenv(env, t);
	free(str);
}

int		ft_is_var(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return ((str[0] == '=') ? 0 : 1);
		i++;
	}
	return (0);
}

void	ft_error_env(char **t)
{
	ft_putstr_fd("env: illegal option -- ", 2);
	ft_putchar_fd(t[1][1], 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("env [-i] [name=value...] [utility [arguments...]]", 2);
}

void	ft_exec(char **t, int i, char **env, char **newenv)
{
	char	*state;
	pid_t	father;

	if ((access(t[i], X_OK) == 0))
	{
		father = fork();
		(father == 0) ? execve(t[i], t + i, newenv) : wait(0);
	}
	else if ((state = ft_check_execve(t + i, env, i, newenv)) != NULL)
		;
	else
	{
		ft_putstr_fd(t[i], 2);
		ft_putstr_fd("Permission denied.", 2);
	}
}

void	ft_env(char **env, char **t)
{
	char	**newenv;
	int		i;

	i = 0;
	if (t[1] && t[1][0] == '-' && t[1][1] != 'i')
		return (ft_error_env(t));
	if (t[1] && ft_strcmp(t[1], "-i") == 0)
	{
		if (!(newenv = (char**)malloc(sizeof(char*))))
			return ;
		newenv[0] = NULL;
		i = 1;
	}
	else
		newenv = ft_newtab2d(env);
	if (newenv)
	{
		while (t[++i] && ft_is_var(t[i]) == 1)
			ft_addenv(&newenv, t[i]);
		if (i < ft_tab2dlen(t))
			ft_exec(t, i, newenv, newenv);
		else
			ft_display_tab(newenv);
		ft_freetab2d(newenv);
	}
}
