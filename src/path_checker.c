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

static void	push_next(char **map, t_cell *queue, int *tail, t_cell c)
{
	if (map[c.x][c.y] != '0' && map[c.x][c.y] != 'C'
	&& map[c.x][c.y] != 'P' && map[c.x][c.y] != 'E')
		return ;
	if (map[c.x][c.y] == 'E')
	{
		map[c.x][c.y] = 'Y';
		return ;
	}
	map[c.x][c.y] = 'X';
	queue[(*tail)++] = c;
}

int	flood_fill(t_game *game, char **map)
{
	t_cell	*queue;
	t_cell	c;
	int		head;
	int		tail;

	queue = malloc(sizeof(t_cell) * game->lines * game->len);
	if (!queue)
		return (1);
	head = 0;
	tail = 0;
	map[game->pos_x][game->pos_y] = 'X';
	queue[tail++] = (t_cell){game->pos_x, game->pos_y};
	while (head < tail)
	{
		c = queue[head++];
		push_next(map, queue, &tail, (t_cell){c.x + 1, c.y});
		push_next(map, queue, &tail, (t_cell){c.x - 1, c.y});
		push_next(map, queue, &tail, (t_cell){c.x, c.y + 1});
		push_next(map, queue, &tail, (t_cell){c.x, c.y - 1});
	}
	free(queue);
	return (0);
}

static int	path_error(t_game *game, char **map, char *msg)
{
	to_free(map);
	return (set_error(game, msg));
}

int	check_path(t_game *game)
{
	char	**map;

	map = dup_map(game);
	if (!map)
		return (set_error(game, "Out of memory"));
	if (flood_fill(game, map))
		return (path_error(game, map, "Out of memory"));
	if (check_collect(map, 'C'))
		return (path_error(game, map, "Player Can't reach all collectibles"));
	if (check_collect(map, 'E'))
		return (path_error(game, map, "Player Can not exit"));
	to_free(map);
	return (0);
}
