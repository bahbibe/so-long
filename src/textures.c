/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 00:06:42 by bahbibe           #+#    #+#             */
/*   Updated: 2022/12/31 00:26:18 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_floor(t_game *game, t_image *img)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			put_img(game, img->floor, i, j);
			if (game->map[i][j] == '1')
				put_img(game, img->wall, i, j);
		}
	}
}

void	render_map(t_game *game, t_image *img)
{
	int	i;
	int	j;

	i = -1 ;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == 'C')
				put_img(game, img->coll, i, j);
			else if (game->map[i][j] == 'P')
				put_img(game, img->play, i, j);
			else if (game->map[i][j] == 'E' && game->colct == 0)
			{
				put_img(game, img->stair, i, j);
				put_img(game, img->door_o, i, j);
			}
			else if (game->map[i][j] == 'E')
				put_img(game, img->door_c, i, j);
			else if (game->map[i][j] == 'G')
				put_img(game, img->ghost, i, j);
		}
	}
}

int	put_banner(t_game *game, char *msg)
{
	char	*moves;
	char	*str;

	if (game->end)
		return (mlx_string_put(game->mlx, game->mlx_win, 2, 0, RED, msg));
	moves = ft_itoa(game->moves);
	if (!moves)
		return (1);
	str = ft_strjoin(msg, moves);
	free(moves);
	if (!str)
		return (1);
	mlx_string_put(game->mlx, game->mlx_win, 2, 0, RED, str);
	free(str);
	return (0);
}

void	put_img(t_game *game, void *img, int i, int j)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win, img,
		j * SCALE, (i + 1) * SCALE);
}

void	render_assets(t_image *img)
{
	render_floor(img->game, img);
	render_map(img->game, img);
	put_banner(img->game, "NUMBER OF MOVES : ");
}
