/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost_anim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 20:00:00 by bahbibe           #+#    #+#             */
/*   Updated: 2026/11/22 20:00:00 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_ghosts(t_game *game, t_image *img)
{
	int	i;

	i = 0;
	while (game->ghosts && i < game->ghost_count)
	{
		put_img(game, img->ghost, game->ghosts[i].x, game->ghosts[i].y);
		i++;
	}
}

static void	next_sprite(t_image *img, int step)
{
	if (step % 4 == 0)
		img->ghost = img->ghost2;
	else if (step % 4 == 1)
		img->ghost = img->ghost3;
	else if (step % 4 == 2)
		img->ghost = img->ghost2;
	else
		img->ghost = img->ghost1;
}

/* Called on every loop iteration. Every GHOST_DELAY iterations the ghosts
   take one step toward the player. */
int	animate(t_image *img)
{
	t_game	*game;

	game = img->game;
	if (game->end || game->ghost_count == 0 || ++game->frame < GHOST_DELAY)
		return (0);
	game->frame = 0;
	if (move_ghosts(game))
		game->end = 2;
	next_sprite(img, game->steps++);
	if (game->end)
		show_end(img);
	else
		render_assets(img);
	return (0);
}
