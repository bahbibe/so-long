/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 09:13:35 by bahbibe           #+#    #+#             */
/*   Updated: 2022/12/30 23:53:06 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move(t_game *game, char next, int x, int y)
{
	if (ghost_at(game, game->pos_x + x, game->pos_y + y))
		game->end = 2;
	else if (next == 'E' && game->colct == 0)
		game->end = 1;
	else if (next == 'C')
	{
		game->map[game->pos_x][game->pos_y] = '0';
		game->map[game->pos_x + x][game->pos_y + y] = 'P';
		game->pos_y += y;
		game->pos_x += x;
		game->colct--;
	}
	else if (next == '0')
	{
		game->map[game->pos_x][game->pos_y] = '0';
		game->map[game->pos_x + x][game->pos_y + y] = 'P';
		game->pos_y += y;
		game->pos_x += x;
	}
}

void	move_player(t_game *game, int x, int y)
{
	char	next;
	long	now;

	next = game->map[game->pos_x + x][game->pos_y + y];
	if (game->end || next == '1' || (next == 'E' && game->colct != 0))
		return ;
	now = now_ms();
	game->moves++;
	game->from = player_px(game, now);
	game->move_t0 = now;
	move(game, next, x, y);
	game->dirty = 1;
}

int	key_press(int key, t_game *game)
{
	if (key == K_ESC || key == K_Q)
		quit(game);
	else if (key == K_W || key == A_W)
		game->dir = 0;
	else if (key == K_S || key == A_S)
		game->dir = 1;
	else if (key == K_A || key == A_A)
		game->dir = 2;
	else if (key == K_D || key == A_D)
		game->dir = 3;
	else
		return (0);
	if (game->dir == 0)
		move_player(game, -1, 0);
	else if (game->dir == 1)
		move_player(game, 1, 0);
	else if (game->dir == 2)
		move_player(game, 0, -1);
	else
		move_player(game, 0, 1);
	return (0);
}

int	quit(t_game *game)
{
	destroy_gfx(game);
	to_free(game->map);
	free_ghosts(game);
	exit(0);
}
