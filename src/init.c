/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:05:49 by bahbibe           #+#    #+#             */
/*   Updated: 2022/12/31 00:27:23 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_game *game)
{
	ft_bzero(game, sizeof(*game));
	game->dist_x = -1;
	game->dist_y = -1;
	game->dirty = 1;
	game->dir = 3;
}

static int	gfx_error(t_game *game, char *msg)
{
	destroy_gfx(game);
	return (set_error(game, msg));
}

int	init_window(t_game *game)
{
	int	w;
	int	h;

	w = game->len * TILE;
	h = game->lines * TILE + HUD_H;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (set_error(game, "Can not initialize MiniLibX"));
	game->mlx_win = mlx_new_window(game->mlx, w, h, "so_long");
	if (!game->mlx_win)
		return (gfx_error(game, "Can not create window"));
	if (init_frame(game, &game->fb, w, h) || init_frame(game, &game->bg, w, h))
		return (gfx_error(game, "Can not create frame buffer"));
	build_bg(game);
	game->from = tile_origin(game->pos_x, game->pos_y);
	game->ghost_t0 = now_ms();
	return (0);
}
