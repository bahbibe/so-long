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
	if (map[c.x][c.y] == '1' || map[c.x][c.y] == 'X'
	|| map[c.x][c.y] == 'Y')
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

int	check_path(t_game *game)
{
	game->map2 = dup_map(game);
	if (!game->map2)
		return (set_error(game, "Out of memory"));
	if (flood_fill(game, game->map2))
		return (set_error(game, "Out of memory"));
	if (check_collect(game, 'C'))
		return (set_error(game, "Player Can't reach all collectibles"));
	if (check_collect(game, 'E'))
		return (set_error(game, "Player Can not exit"));
	to_free(game->map2);
	game->map2 = NULL;
	return (0);
}
