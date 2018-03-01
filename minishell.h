/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 14:03:54 by golliet           #+#    #+#             */
/*   Updated: 2018/02/16 09:10:58 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/get_next_line.h"
# include "libft/libft.h"
# include <signal.h>
# include "unistd.h"
# include <sys/param.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/stat.h>
# include <signal.h>

/*
** TAB
*/
void			ft_display_tab(char **env);
char			**ft_newtab2d(char **env);
void			ft_freetab2d(char **ta);
int				ft_tab2dlen(char **ta);
void			ft_realloc_setenv(char ***env, char *str);

/*
** BUILTINS
*/
void			pwd(char **env, char **ta);
char			**cd(char **env, char **ta);
void			ft_setenv(char ***env, char **ta);
void			ft_unsetenv(char ***env, char **ta);
void			ft_echo(char **t, char *str);
void			ft_env(char **env, char **t);

/*
** ALL BIN
*/
char			*ft_check_execve(char **ta, char **env, int i, char **newenv);

/*
** Misc
*/

void			ft_path(void);
int				ft_sizeof_pwd(void);
int				ft_find_in_env(char **env, char *str);
char			**ft_put(char *str, char **env);
int				ft_realloc_env(int n, char ***newenv, char **env);
void			ft_chdir(char **newenv);
void			exit_and_free(char **t, char ***newenv, char *str);
void			ft_if(char ***env, char *path, char *curr, char *after);
char			**ft_error_home(char **env, char *str);

/*
** Main loop
*/

char			*ft_read(void);

typedef struct	s_char
{
	char		*tmp;
	char		*tmp2;
	char		*curr;
	char		*path;
	char		*path2;
}				t_char;

#endif
