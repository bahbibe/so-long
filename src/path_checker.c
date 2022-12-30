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
