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

static void	draw_eyes(t_frame *f, t_pt c, t_pt look, int spread)
{
	int	side;

	side = -2;
	while ((side += 2) <= 2)
	{
		fill_circle(f, (t_pt){c.x + (side - 1) * spread, c.y}, 5, C_WHITE);
		fill_circle(f, (t_pt){c.x + (side - 1) * spread + look.x * 2,
			c.y + look.y * 2}, 2, C_PUPIL);
	}
}

void	draw_player(t_frame *f, t_pt o, int dir, int bob)
{
	static const t_pt	look[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
	t_pt				c;

	c = (t_pt){o.x + TILE / 2, o.y + TILE / 2 + 1 + bob};
	fill_rect(f, (t_rect){c.x - 12, o.y + TILE - 8, 24, 3},
		shade(C_FLOOR, -14));
	fill_circle(f, c, 18, shade(C_PLAYER, -50));
	fill_circle(f, (t_pt){c.x, c.y - 1}, 17, C_PLAYER);
	fill_circle(f, (t_pt){c.x - 7, c.y - 9}, 4, shade(C_PLAYER, 60));
	draw_eyes(f, (t_pt){c.x + look[dir % 4].x * 3, c.y - 2 + look[dir % 4].y * 2},
		look[dir % 4], 6);
}

void	draw_ghost(t_frame *f, t_pt o, t_pt look, int phase)
{
	t_pt	c;

	c = (t_pt){o.x + TILE / 2, o.y + 21 + (phase % 2)};
	fill_circle(f, c, 19, C_GHOST);
	fill_skirt(f, (t_rect){c.x - 19, c.y, 39, 20}, phase * 3, C_GHOST);
	fill_circle(f, (t_pt){c.x - 8, c.y - 9}, 3, shade(C_GHOST, 55));
	draw_eyes(f, (t_pt){c.x, c.y - 1}, look, 7);
}
