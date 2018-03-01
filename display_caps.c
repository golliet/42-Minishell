/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_caps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 15:05:06 by golliet           #+#    #+#             */
/*   Updated: 2018/02/13 15:29:17 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "myterm.h"

/*
** Function who select the right termcaps
*/

static void		ft_erase(t_cursor *cursor)
{
	int j;

	j = 1;
	while (j < cursor->line)
	{
		ft_putstr("\x1b[0K");
		ft_putstr("\x1b[1B");
		ft_putstr("\x1b[0K");
		ft_putstr("\x1b[1A");
		ft_putstr("\x1b[1A");
		j++;
	}
	ft_putstr("\x1b[1B");
	ft_putstr("\x1b[0K");
	ft_putstr("\x1b[1A");
}

static void		ft_delete(t_cursor *cursor)
{
	int i;
	int j;

	i = -1;
	ft_delete_realloc(cursor);
	ft_putstr("\r\x1b[0K");
	if (cursor->len + ft_sizeof_pwd() + 7 > cursor->col_term)
		ft_erase(cursor);
	ft_path();
	ft_putstr(cursor->str);
	if (cursor->pos != cursor->len)
		while (++i < (cursor->len - cursor->pos))
			ft_putstr(ARROW_L);
	else
		while (++i < (cursor->pos - cursor->len))
			ft_putstr(ARROW_L);
	cursor->len--;
	cursor->pos--;
}

void			ft_display_tcaps(char *caps, t_cursor *cursor)
{
	if (caps[1] == '[')
	{
		if (caps[2] == 'D')
		{
			if (cursor->pos > 0)
			{
				cursor->pos--;
				ft_putstr(caps);
			}
		}
		if (caps[2] == 'C')
		{
			if (cursor->pos < cursor->len)
			{
				cursor->pos++;
				ft_putstr(caps);
			}
		}
	}
	cursor->line = (cursor->pos + ft_sizeof_pwd() + 7) / cursor->col_term + 1;
	if (caps[0] == 0x7f && cursor->pos > 0 && cursor->len > 0)
		ft_delete(cursor);
}
