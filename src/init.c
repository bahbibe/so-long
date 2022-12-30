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

void	init_game(t_game *game, t_image *img)
{
	game->frame = 0;
	game->moves = 0;
	game->len = 0;
	game->lines = 0;
	game->pos = 0;
	game->colct = 0;
	game->exit = 0;
	game->end = 0;
	init_player_img(game, img);
}

void	init_img(t_game *game, t_image *img)
{
	img->game = game;
	img->wall = mlx_xpm_file_to_image(game->mlx, "./img/wall.xpm",
			&img->img_width, &img->img_height);
	img->coll = mlx_xpm_file_to_image(game->mlx, "./img/coll.xpm",
			&img->img_width, &img->img_height);
	img->floor = mlx_xpm_file_to_image(game->mlx, "./img/floor.xpm",
			&img->img_width, &img->img_height);
	img->door_o = mlx_xpm_file_to_image(game->mlx, "./img/door_o.xpm",
			&img->img_width, &img->img_height);
	img->door_c = mlx_xpm_file_to_image(game->mlx, "./img/door_c.xpm",
			&img->img_width, &img->img_height);
	img->ghost1 = mlx_xpm_file_to_image(game->mlx, "./img/ghost1.xpm",
			&img->img_width, &img->img_height);
	img->ghost2 = mlx_xpm_file_to_image(game->mlx, "./img/ghost2.xpm",
			&img->img_width, &img->img_height);
	img->ghost3 = mlx_xpm_file_to_image(game->mlx, "./img/ghost3.xpm",
			&img->img_width, &img->img_height);
	img->stair = mlx_xpm_file_to_image(game->mlx, "./img/stair.xpm",
			&img->img_width, &img->img_height);
	img->ok = mlx_xpm_file_to_image(game->mlx, "./img/ok.xpm",
			&img->img_width, &img->img_height);
	img->ko = mlx_xpm_file_to_image(game->mlx, "./img/ko.xpm",
			&img->img_width, &img->img_height);
	img->ghost = img->ghost1;
	img->play = img->play_r;
}

void	init_player_img(t_game *game, t_image *img)
{
	img->play_r = mlx_xpm_file_to_image(game->mlx, "./img/play_r.xpm",
			&img->img_width, &img->img_height);
	img->play_l = mlx_xpm_file_to_image(game->mlx, "./img/play_l.xpm",
			&img->img_width, &img->img_height);
	img->play_u = mlx_xpm_file_to_image(game->mlx, "./img/play_u.xpm",
			&img->img_width, &img->img_height);
	img->play_d = mlx_xpm_file_to_image(game->mlx, "./img/play_d.xpm",
			&img->img_width, &img->img_height);
}
