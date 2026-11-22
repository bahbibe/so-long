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

/* Time based loop: ghosts take one step every GHOST_DELAY ms and the frame
   is redrawn only when something moved or changed. */
static void	ghost_step(t_game *game, long now)
{
	int	i;

	i = -1;
	while (++i < game->ghost_count)
	{
		game->ghosts[i].fx = game->ghosts[i].x;
		game->ghosts[i].fy = game->ghosts[i].y;
	}
	game->ghost_t0 = now;
	if (move_ghosts(game))
		game->end = 2;
	game->dirty = 1;
}

/* Something is in motion: the player slides, the ghosts glide. */
static int	moving(t_game *game, long now)
{
	return (now - game->move_t0 < MOVE_MS
		|| (game->ghost_count && now - game->ghost_t0 < GHOST_GLIDE));
}

int	tick(t_game *game)
{
	long	now;

	now = now_ms();
	if (now - game->last_frame < FRAME_MS)
	{
		usleep(5000);
		return (0);
	}
	game->last_frame = now;
	if (!game->end && game->ghost_count && now - game->ghost_t0 >= GHOST_DELAY)
		ghost_step(game, now);
	if (game->dirty || (!game->end && (moving(game, now)
				|| now / ANIM_MS != game->phase)))
	{
		game->phase = now / ANIM_MS;
		render(game);
	}
	return (0);
}

int	expose(t_game *game)
{
	game->dirty = 1;
	return (0);
}
