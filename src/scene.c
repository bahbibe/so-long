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

void	draw_items(t_game *game, long now)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (++j < game->len)
		{
			if (game->map[i][j] == 'C')
				draw_coin(&game->fb, tile_origin(i, j), (i + j + now / ANIM_MS));
			else if (game->map[i][j] == 'E')
				draw_door(&game->fb, tile_origin(i, j), game->colct == 0);
		}
	}
}

static int	sign(int n)
{
	return ((n > 0) - (n < 0));
}

void	draw_ghosts(t_game *game, long now)
{
	t_ghost	*g;
	t_pt	to;
	t_pt	at;
	t_pt	me;
	int		i;

	me = player_px(game, now);
	i = -1;
	while (game->ghosts && ++i < game->ghost_count)
	{
		g = &game->ghosts[i];
		to = tile_origin(g->x, g->y);
		at = tile_origin(g->fx, g->fy);
		at.x = lerp(at.x, to.x, now - game->ghost_t0, GHOST_GLIDE);
		at.y = lerp(at.y, to.y, now - game->ghost_t0, GHOST_GLIDE);
		draw_ghost(&game->fb, at, (t_pt){sign(me.x - at.x), sign(me.y - at.y)},
			now / ANIM_MS + i);
	}
}

void	draw_end(t_game *game)
{
	t_rect	panel;
	int		color;

	color = C_WIN;
	if (game->end == 2)
		color = C_LOSE;
	panel.w = game->fb.w - 20;
	if (panel.w > 300)
		panel.w = 300;
	panel.h = 100;
	panel.x = (game->fb.w - panel.w) / 2;
	panel.y = (game->fb.h - panel.h) / 2;
	dim_rect(&game->fb, (t_rect){0, 0, game->fb.w, game->fb.h}, 1);
	dim_rect(&game->fb, panel, 2);
	fill_rect(&game->fb, (t_rect){panel.x - 3, panel.y - 3, panel.w + 6, 3},
		color);
	fill_rect(&game->fb, (t_rect){panel.x - 3, panel.y + panel.h, panel.w + 6,
		3}, color);
	fill_rect(&game->fb, (t_rect){panel.x - 3, panel.y, 3, panel.h}, color);
	fill_rect(&game->fb, (t_rect){panel.x + panel.w, panel.y, 3, panel.h},
		color);
}

static void	put_centered(t_game *game, int y, int color, char *str)
{
	mlx_string_put(game->mlx, game->mlx_win,
		game->fb.w / 2 - (int)ft_strlen(str) * 3, y, color, str);
}

void	put_end_text(t_game *game)
{
	char	*moves;
	char	*str;
	int		top;

	top = (game->fb.h - 100) / 2;
	if (game->end == 2)
		put_centered(game, top + 28, C_LOSE, "GAME OVER");
	else
		put_centered(game, top + 28, C_WIN, "YOU WIN !");
	moves = ft_itoa(game->moves);
	str = NULL;
	if (moves)
		str = ft_strjoin("MOVES : ", moves);
	free(moves);
	if (str)
		put_centered(game, top + 54, C_WHITE, str);
	free(str);
	put_centered(game, top + 82, C_WHITE, "PRESS ESC OR Q TO EXIT");
}
