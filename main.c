/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:17:28 by golliet           #+#    #+#             */
/*   Updated: 2018/02/16 09:10:43 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "myterm.h"

void	ft_core(char **t, char ***newenv, char *str)
{
	char	*state;
	pid_t	father;

	if (ft_strcmp(t[0], "exit") == 0)
		exit_and_free(t, newenv, str);
	else if (ft_strcmp(t[0], "env") == 0)
		ft_env(*newenv, t);
	else if (ft_strcmp(t[0], "setenv") == 0)
		ft_setenv(newenv, t);
	else if (ft_strcmp(t[0], "unsetenv") == 0)
		ft_unsetenv(newenv, t);
	else if (ft_strcmp(t[0], "echo") == 0)
		ft_echo(t, str);
	else
	{
		if ((state = ft_check_execve(t, *newenv, 0, *newenv)) != NULL)
		{
			father = fork();
			if (father == 0)
				execve(state, t, *newenv);
			else
				wait(0);
		}
	}
}

void	minishell(char **newenv)
{
	int		rd;
	char	*str;
	char	**t;

	t = NULL;
	while (42)
	{
		ft_path();
		str = ft_read();
		t = ft_split_whitespaces(str);
		ft_putchar('\n');
		if (!t[0])
			;
		else if (ft_strcmp(t[0], "cd") == 0)
			newenv = cd(newenv, t);
		else
			ft_core(t, &newenv, str);
		ft_freetab2d(t);
		free(str);
	}
}

int		ft_toggle_raw(char **newenv)
{
	int				i;
	struct termios	term;

	i = 0;
	while (ft_strncmp(newenv[i], "TERM=", 5) != 0)
		i++;
	if (tgetent(NULL, newenv[i] + 5) == ERR)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (1);
}

int		ft_test(char **env)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0 && !(count & 1))
			count += 1;
		else if (ft_strncmp(env[i], "OLDPWD=", 7) == 0 && !(count & 2))
			count += 2;
		else if (ft_strncmp(env[i], "TERM=", 5) == 0 && !(count & 4))
			count += 4;
		else if (ft_strncmp(env[i], "PATH=", 5) == 0 && !(count & 8))
			count += 8;
		i++;
	}
	return (count);
}

int		main(int argc, char **argv, char **env)
{
	char			**newenv;
	int				i;

	i = 0;
	if (ft_tab2dlen(env) == 0)
	{
		if (!(newenv = (char**)malloc(sizeof(char*) * 5)))
			return (-1);
		newenv[0] = ft_strdup("PWD=/");
		newenv[1] = ft_strdup("OLDPWD=/");
		newenv[2] = ft_strdup("TERM=xterm-256color");
		newenv[3] = ft_strdup("PATH=/bin:/usr/bin:/usr/sbin");
		newenv[4] = NULL;
		chdir("/");
	}
	else if (ft_realloc_env(ft_test(env), &newenv, env) != 15)
		;
	else
		newenv = ft_newtab2d(env);
	ft_chdir(newenv);
	if (ft_toggle_raw(newenv) == -1)
		return (-1);
	minishell(newenv);
	return (1);
}
