/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 09:08:12 by golliet           #+#    #+#             */
/*   Updated: 2018/02/13 10:23:31 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static char		*ft_doublejoin(char *s1, char *s2)
{
	char	*path;
	char	*tmp;
	int		i;

	i = ft_strlen(s1) - 1;
	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	free(tmp);
	return (path);
}

static char		*ft_display_error(char **t)
{
	ft_putstr_fd("sh: ", 2);
	ft_putstr_fd("command not found: ", 2);
	ft_putendl_fd(t[0], 2);
	return (NULL);
}

static void		ft_execve(pid_t father, char *pth, char **t, char **env)
{
	if (father == 0)
		execve(pth, t, env);
	else
		wait(0);
	free(pth);
}

static char		*ft_is_bin_here(char **p, char **t, char **env, char **newenv)
{
	int				i;
	char			*pth;
	struct dirent	*tmp;
	DIR				*dir;
	pid_t			father;

	i = -1;
	while (++i < ft_tab2dlen(p))
	{
		if (!(dir = opendir(p[i])))
			return (ft_display_error(t));
		while ((tmp = readdir(dir)) != NULL)
		{
			if (ft_strcmp(tmp->d_name, t[0]) == 0)
			{
				pth = ft_doublejoin(p[i], tmp->d_name);
				father = fork();
				ft_execve(father, pth, t, newenv);
				closedir(dir);
				return (NULL);
			}
		}
		closedir(dir);
	}
	return ("");
}

char			*ft_check_execve(char **t, char **env, int i, char **newenv)
{
	struct stat stat;
	char		**path;

	if (lstat(t[i], &stat) == -1)
		;
	else if ((access(t[i], X_OK) == 0) && stat.st_mode & S_IFREG)
		return (t[i]);
	i = 0;
	while (env[i] && ft_strncmp("PATH=", env[i], 5) != 0)
		i++;
	if (i == ft_tab2dlen(env))
	{
		ft_putendl_fd("PATH is missing.", 2);
		return (NULL);
	}
	path = ft_strsplit(env[i] + 5, ':');
	if (ft_is_bin_here(path, t, env, newenv) == NULL)
	{
		ft_freetab2d(path);
		return (NULL);
	}
	ft_freetab2d(path);
	return (ft_display_error(t));
}
