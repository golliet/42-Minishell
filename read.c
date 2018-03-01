/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 15:28:44 by golliet           #+#    #+#             */
/*   Updated: 2018/02/15 14:55:46 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "myterm.h"

void	ft_move_cursor(int j, t_cursor *cursor)
{
	while (j < cursor->line)
	{
		ft_putstr("\x1b[1A");
		j++;
	}
}

void	ft_write_and_save(t_cursor *cursor, char buf[5], char *tmp)
{
	write(1, buf, ft_strlen(buf));
	tmp = cursor->str;
	cursor->str = ft_strjoin(cursor->str, buf);
	free(tmp);
	cursor->len++;
	cursor->pos++;
}

void	ft_is_normal(t_cursor *cursor, char buf[5], char *tmp)
{
	int i;
	int j;

	i = -1;
	if (cursor->pos != cursor->len)
	{
		ft_add_realloc(cursor, buf[0]);
		ft_putstr("\r\x1b[0K");
		cursor->line = (cursor->pos + ft_sizeof_pwd() + 7) /
			cursor->col_term + 1;
		if (cursor->len + ft_sizeof_pwd() + 7 > cursor->col_term)
		{
			j = 1;
			ft_move_cursor(j, cursor);
		}
		ft_path();
		ft_putstr(cursor->str);
		while (++i < (cursor->len - cursor->pos))
			ft_putstr(ARROW_L);
		cursor->len++;
		cursor->pos++;
	}
	else
		ft_write_and_save(cursor, buf, tmp);
}

char	*ft_read(void)
{
	char		buf[5];
	char		*tmp;
	int			rd;
	t_cursor	cursor;

	cursor.pos = 0;
	cursor.len = 0;
	cursor.str = ft_strnew(1);
	while (420)
	{
		ft_size_term(&cursor);
		rd = read(0, buf, 4);
		if (buf[0] == '\n')
			break ;
		buf[rd] = '\0';
		if (rd == 1 && buf[0] != 0x7f)
			ft_is_normal(&cursor, buf, tmp);
		else
			ft_display_tcaps(buf, &cursor);
	}
	return (cursor.str);
}
