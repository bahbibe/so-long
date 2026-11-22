/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghosts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 20:00:00 by bahbibe           #+#    #+#             */
/*   Updated: 2026/11/22 20:00:00 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* 3x5 digit font, one bit per cell, row by row, top left bit first. */
static void	draw_digit(t_frame *f, t_pt p, int digit, int color)
{
	static const int	font[10] = {0x7B6F, 0x2C97, 0x73E7, 0x73CF, 0x5BC9,
		0x79CF, 0x79EF, 0x7249, 0x7BEF, 0x7BCF};
	int					bit;

	bit = -1;
	while (++bit < 15)
		if (font[digit] >> (14 - bit) & 1)
			fill_rect(f, (t_rect){p.x + bit % 3 * 3, p.y + bit / 3 * 3, 3, 3},
				color);
}

void	draw_number(t_frame *f, t_pt p, int n, int color)
{
	int	digits;
	int	tmp;

	if (n < 0)
		return ;
	digits = 1;
	tmp = n;
	while (tmp > 9 && ++digits)
		tmp /= 10;
	while (digits--)
	{
		draw_digit(f, (t_pt){p.x + digits * 12, p.y}, n % 10, color);
		n /= 10;
	}
}

void	draw_hud(t_game *game)
{
	t_frame	*f;
	int		i;

	f = &game->fb;
	fill_rect(f, (t_rect){0, 0, f->w, HUD_H}, C_HUD);
	fill_rect(f, (t_rect){0, HUD_H - 2, f->w, 2}, shade(C_HUD, 24));
	fill_circle(f, (t_pt){18, 15}, 8, shade(C_COIN, -40));
	fill_circle(f, (t_pt){18, 15}, 6, C_COIN);
	draw_number(f, (t_pt){36, 8}, game->colct, C_COIN);
	i = -1;
	while (++i < 6)
		fill_rect(f, (t_rect){120 + i, 8 + i, 1, 14 - i * 2}, C_PLAYER);
	draw_number(f, (t_pt){138, 8}, game->moves, C_WHITE);
}
