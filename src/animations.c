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

void	move_player(t_game *game, t_image *img, int x, int y)
{
	char	next;

	next = game->map[game->pos_x + x][game->pos_y + y];
	if (game->end || next == '1' || (next == 'E' && game->colct != 0))
		return ;
	game->moves++;
	move(game, next, x, y);
	if (game->end == 0)
	{
		mlx_clear_window(game->mlx, game->mlx_win);
		render_assets(img);
	}
	else
		show_end(img);
}

int	move_keys(int key, t_image *img)
{
	if (key == K_ESC || key == K_Q)
		quit(img->game);
	else if (key == K_W || key == A_W)
	{
		img->play = img->play_u;
		move_player(img->game, img, -1, 0);
	}
	else if (key == K_S || key == A_S)
	{
		img->play = img->play_d;
		move_player(img->game, img, 1, 0);
	}
	else if (key == K_A || key == A_A)
	{
		img->play = img->play_l;
		move_player(img->game, img, 0, -1);
	}
	else if (key == K_D || key == A_D)
	{
		img->play = img->play_r;
		move_player(img->game, img, 0, 1);
	}
	return (0);
}

int	quit(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	to_free(game->map);
	free_ghosts(game);
	exit(0);
}

void	show_end(t_image *img)
{
	t_game	*game;

	game = img->game;
	mlx_clear_window(game->mlx, game->mlx_win);
	if (game->end == 2)
		mlx_put_image_to_window(game->mlx, game->mlx_win, img->ko,
			(game->len * SCALE - 600) / 2, (game->lines * SCALE - 400) / 2);
	else
		mlx_put_image_to_window(game->mlx, game->mlx_win, img->ok,
			(game->len * SCALE - 700) / 2, (game->lines * SCALE - 400) / 2);
	put_banner(game, "PRESS ESC OR Q TO EXIT ...");
}
