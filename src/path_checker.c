/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:56:10 by bahbibe           #+#    #+#             */
/*   Updated: 2022/12/27 17:39:28 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill_one(int pos_x, int pos_y, char **map)
{
	if ((map[pos_x][pos_y] != '0' && map[pos_x][pos_y] != 'C'
	&& map[pos_x][pos_y] != 'P'))
		return ;
	map[pos_x][pos_y] = 'X';
	flood_fill_one(pos_x + 1, pos_y, map);
	flood_fill_one(pos_x, pos_y + 1, map);
	flood_fill_one(pos_x, pos_y - 1, map);
	flood_fill_one(pos_x - 1, pos_y, map);
	return ;
}

void	flood_fill_two(int pos_x, int pos_y, char **map)
{
	if ((map[pos_x][pos_y] != '0' && map[pos_x][pos_y] != 'E'
	&& map[pos_x][pos_y] != 'X'))
		return ;
	map[pos_x][pos_y] = 'Y';
	flood_fill_two(pos_x + 1, pos_y, map);
	flood_fill_two(pos_x, pos_y + 1, map);
	flood_fill_two(pos_x, pos_y - 1, map);
	flood_fill_two(pos_x - 1, pos_y, map);
	return ;
}

int	check_path(t_game *game)
{
	game->map2 = dup_map(game);
	if (!game->map2)
		return (set_error(game, "Out of memory"));
	flood_fill_one(game->pos_x, game->pos_y, game->map2);
	if (check_collect(game, 'C'))
		return (set_error(game, "Player Can't reach all collectibles"));
	flood_fill_two(game->pos_x, game->pos_y, game->map2);
	if (check_collect(game, 'E'))
		return (set_error(game, "Player Can not exit"));
	to_free(game->map2);
	game->map2 = NULL;
	return (0);
}
