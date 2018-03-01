/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 15:29:12 by golliet           #+#    #+#             */
/*   Updated: 2018/02/16 09:11:22 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "myterm.h"

int		ft_sizeof_pwd(void)
{
	char	*path;
	char	*tmp;
	int		a;

	if (!(path = getcwd(NULL, 2000)))
		path = ft_strdup("/????");
	tmp = ft_strrchr(path, '/') + 1;
	a = ft_strlen(tmp);
	free(path);
	if (a == 0)
		return (1);
	return (a);
}

void	ft_path(void)
{
	char *buf;
	char *str;

	if (!(buf = getcwd(NULL, MAXPATHLEN)))
		buf = ft_strdup("/????");
	str = ft_strrchr(buf, '/');
	if (ft_strcmp(buf, "/") != 0)
		str++;
	ft_putstr("-> ");
	write(1, "\033[36m", 5);
	ft_putstr(str);
	write(1, "\033[0m", 5);
	ft_putstr(" $> ");
	free(buf);
}

int		ft_realloc_env(int n, char ***newenv, char **env)
{
	*newenv = ft_newtab2d(env);
	if (!(n & 1))
		ft_realloc_setenv(newenv, "PWD=/");
	if (!(n & 2))
		ft_realloc_setenv(newenv, "OLDPWD=/");
	if (!(n & 4))
		ft_realloc_setenv(newenv, "TERM=xterm-256color");
	if (!(n & 8))
		ft_realloc_setenv(newenv, "PATH=/bin:/usr/bin:/usr/sbin");
	return (0);
}

void	ft_chdir(char **newenv)
{
	int i;

	i = 0;
	while (ft_strncmp(newenv[i], "PWD=", 4) != 0)
		i++;
	chdir(newenv[i] + 4);
}
