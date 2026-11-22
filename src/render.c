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

t_pt	tile_origin(int i, int j)
{
	return ((t_pt){j * TILE, HUD_H + i * TILE});
}

t_pt	player_px(t_game *game, long now)
{
	t_pt	to;

	to = tile_origin(game->pos_x, game->pos_y);
	return ((t_pt){lerp(game->from.x, to.x, now - game->move_t0, MOVE_MS),
		lerp(game->from.y, to.y, now - game->move_t0, MOVE_MS)});
}

void	build_bg(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (++j < game->len)
		{
			if (game->map[i][j] == '1')
				draw_wall(&game->bg, tile_origin(i, j), i * 31 + j * 17);
			else
				draw_floor(&game->bg, tile_origin(i, j), i + j);
		}
	}
}

static void	draw_hero(t_game *game, long now)
{
	long	t;
	int		bob;

	t = now - game->move_t0;
	bob = 0;
	if (t >= 0 && t < MOVE_MS)
		bob = -(int)((t < MOVE_MS - t ? t : MOVE_MS - t) * 8 / MOVE_MS);
	draw_player(&game->fb, player_px(game, now), game->dir, bob);
}

void	render(t_game *game)
{
	long	now;

	if (!game || !game->mlx || !game->mlx_win || !game->fb.addr
		|| !game->bg.addr)
		return ;
	now = now_ms();
	ft_memcpy(game->fb.addr, game->bg.addr, game->bg.line * game->bg.h);
	draw_items(game, now);
	draw_ghosts(game, now);
	draw_hero(game, now);
	draw_hud(game);
	if (game->end)
		draw_end(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->fb.img, 0, 0);
	if (game->end)
		put_end_text(game);
	game->dirty = 0;
}
