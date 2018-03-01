/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myterm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 09:33:12 by golliet           #+#    #+#             */
/*   Updated: 2018/02/13 15:10:32 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYTERM_H
# define MYTERM_H

# include "minishell.h"

# define ARROW_U "\x1b[1A"
# define ARROW_D "\x1b[1B"
# define ARROW_R "\x1b[1C"
# define ARROW_L "\x1b[1D"

/*
** Struct of the cursor
*/

typedef struct	s_cursor
{
	int			len;
	int			pos;
	int			line;
	int			col_term;
	int			line_term;
	char		*str;
}				t_cursor;

void			ft_size_term(t_cursor *cursor);
void			ft_display_tcaps(char *caps, t_cursor *cursor);
void			ft_add_realloc(t_cursor *cursor, char c);
void			ft_delete_realloc(t_cursor *cursor);

#endif
