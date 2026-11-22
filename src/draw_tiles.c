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

void	draw_floor(t_frame *f, t_pt o, int seed)
{
	fill_rect(f, (t_rect){o.x, o.y, TILE, TILE},
		shade(C_FLOOR, (seed % 2) * 7));
	fill_rect(f, (t_rect){o.x, o.y, TILE, 1}, shade(C_FLOOR, -6));
	fill_rect(f, (t_rect){o.x, o.y, 1, TILE}, shade(C_FLOOR, -6));
}

static void	draw_brick(t_frame *f, t_rect r, int color)
{
	fill_rect(f, r, color);
	fill_rect(f, (t_rect){r.x, r.y, r.w, 2}, shade(color, 18));
	fill_rect(f, (t_rect){r.x, r.y + r.h - 2, r.w, 2}, shade(color, -18));
}

void	draw_wall(t_frame *f, t_pt o, int seed)
{
	int	row;
	int	col;
	int	x0;
	int	x1;

	fill_rect(f, (t_rect){o.x, o.y, TILE, TILE}, C_MORTAR);
	row = -1;
	while (++row < 4)
	{
		col = -1;
		while (++col < 4)
		{
			x0 = col * 16 - (row % 2) * 8;
			x1 = x0 + 15;
			if (x0 < 0)
				x0 = 0;
			if (x1 > TILE)
				x1 = TILE;
			if (x1 > x0)
				draw_brick(f, (t_rect){o.x + x0, o.y + row * 12 + 1, x1 - x0,
					10}, shade(C_BRICK, (seed + row * 7 + col * 13) % 5 * 6));
		}
	}
}

void	draw_coin(t_frame *f, t_pt o, int phase)
{
	t_pt	c;
	int		p;

	p = phase % 4;
	c = (t_pt){o.x + TILE / 2, o.y + TILE / 2 - (p == 2 ? 2 : p % 2)};
	fill_rect(f, (t_rect){c.x - 9, o.y + TILE - 9, 18, 3}, shade(C_FLOOR, -14));
	fill_circle(f, c, 12, shade(C_COIN, -40));
	fill_circle(f, c, 10, C_COIN);
	fill_circle(f, (t_pt){c.x, c.y}, 6, shade(C_COIN, 25));
	fill_circle(f, (t_pt){c.x - 4, c.y - 4}, 2, C_WHITE);
}

void	draw_door(t_frame *f, t_pt o, int open)
{
	int	i;

	fill_rect(f, (t_rect){o.x + 7, o.y + 3, 34, TILE - 3}, shade(C_BRICK, -30));
	if (!open)
	{
		fill_rect(f, (t_rect){o.x + 10, o.y + 6, 28, TILE - 6}, 0x8B5A2B);
		fill_rect(f, (t_rect){o.x + 23, o.y + 6, 2, TILE - 6}, 0x5C3A1A);
		fill_circle(f, (t_pt){o.x + 31, o.y + 28}, 3, C_COIN);
		return ;
	}
	fill_rect(f, (t_rect){o.x + 10, o.y + 6, 28, TILE - 6}, 0x07070C);
	i = -1;
	while (++i < 4)
		fill_rect(f, (t_rect){o.x + 12 + i * 2, o.y + 14 + i * 8, 24 - i * 4,
			6}, C_WIN - i * 0x0A1408);
}
