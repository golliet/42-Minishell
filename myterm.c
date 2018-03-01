/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myterm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 09:39:59 by golliet           #+#    #+#             */
/*   Updated: 2018/02/13 15:12:00 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "myterm.h"

/*
**Function who will calulate the size of term
*/

void	ft_size_term(t_cursor *cursor)
{
	struct winsize size;

	ioctl(0, TIOCGWINSZ, &size);
	cursor->col_term = size.ws_col;
	cursor->line_term = size.ws_row;
}

/*
** Function who will realloc the line, adding an element
*/

void	ft_add_realloc(t_cursor *cursor, char c)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * (cursor->len + 1 + 1))))
		return ;
	while (i < cursor->len)
	{
		if (i == cursor->pos)
			str[i + j++] = c;
		str[i + j] = cursor->str[i];
		i++;
	}
	str[i + j] = '\0';
	free(cursor->str);
	cursor->str = str;
}

/*
** Function who will realloc the line
*/

void	ft_delete_realloc(t_cursor *cursor)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(str = (char*)malloc(sizeof(char) * cursor->len)))
		return ;
	while (i < cursor->len)
	{
		if (i == cursor->pos - 1)
			j++;
		str[i] = cursor->str[i + j];
		i++;
	}
	free(cursor->str);
	cursor->str = str;
}
