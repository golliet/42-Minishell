/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 13:56:36 by golliet           #+#    #+#             */
/*   Updated: 2018/02/14 15:46:02 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_error_cd(char **t)
{
	struct stat stat;

	if (t[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (0);
	}
	if ((chdir(t[1]) == -1))
	{
		if (lstat(t[1], &stat) == -1)
			ft_putstr_fd("cd: no such file or directory: ", 2);
		else
			ft_putstr_fd("cd: permission denied: ", 2);
		ft_putendl_fd(t[1], 2);
		return (0);
	}
	return (1);
}

static char		**ft_error_cd2(char **env, int j)
{
	struct stat stat;

	if (lstat(env[j] + 7, &stat) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(env[j] + 7, 2);
	}
	else
	{
		ft_putstr_fd("cd: permission denied: ", 2);
		ft_putendl_fd(env[j] + 7, 2);
	}
	return (env);
}

static char		**cd_minus(char **env)
{
	int				i;
	int				j;
	char			*tmp;
	char			*tmp2;

	if ((j = ft_find_in_env(env, "OLDPWD=")) == ft_tab2dlen(env)
			|| (ft_strcmp(env[j], "OLDPWD=") == 0))
		return (ft_put("OLDPWD not set", env));
	if (chdir(env[j] + 7) == -1)
		return (ft_error_cd2(env, j));
	ft_putendl(env[j] + 7);
	tmp2 = env[j];
	if ((i = ft_find_in_env(env, "PWD=")) == ft_tab2dlen(env))
		tmp = ft_strdup("");
	else
	{
		tmp = env[i];
		env[i] = ft_strjoin("PWD=", env[j] + 7);
	}
	env[j] = ft_strjoin("OLDPWD=", tmp + 4);
	free(tmp);
	free(tmp2);
	return (env);
}

static char		**cd_home(char **env)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;
	int		k;

	if ((j = ft_find_in_env(env, "OLDPWD=")) == ft_tab2dlen(env)
			|| (ft_strcmp(env[j], "OLDPWD=") == 0))
		return (ft_put("OLDPWD not set", env));
	if ((k = ft_find_in_env(env, "HOME=")) == ft_tab2dlen(env))
		return (ft_put("cd: var HOME is missing", env));
	if (chdir(env[k] + 5) == -1)
		return (ft_error_home(env, env[k] + 5));
	if ((i = ft_find_in_env(env, "PWD=")) == ft_tab2dlen(env))
		tmp = ft_strdup("\0");
	else
	{
		tmp = env[i];
		env[i] = ft_strjoin("PWD=", env[k] + 5);
	}
	tmp2 = env[j];
	env[j] = ft_strjoin("OLDPWD=", tmp + 4);
	free(tmp);
	free(tmp2);
	return (env);
}

char			**cd(char **env, char **t)
{
	char	*path;
	char	*path2;
	int		i;
	char	*curr;
	char	*after;

	if (!t[1])
		return (cd_home(env));
	if (ft_strcmp(t[1], "-") == 0 && !t[2])
		return (cd_minus(env));
	curr = getcwd(NULL, MAXPATHLEN);
	if (ft_error_cd(t) == 0)
		return (env);
	after = getcwd(NULL, MAXPATHLEN);
	path = ft_strjoin("OLDPWD=", curr);
	if ((i = ft_find_in_env(env, "PWD=")) == ft_tab2dlen(env))
		;
	else
	{
		free(env[i]);
		env[i] = ft_strjoin("PWD=", after);
	}
	ft_if(&env, path, curr, after);
	return (env);
}
