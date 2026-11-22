/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 20:00:00 by bahbibe           #+#    #+#             */
/*   Updated: 2026/11/22 20:00:00 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static const int	g_dx[4] = {-1, 1, 0, 0};
static const int	g_dy[4] = {0, 0, -1, 1};

/* Cell index next to `cur` in direction `dir`, or -1 for a wall / outside. */
static int	nbr(t_game *game, int cur, int dir)
{
	int	x;
	int	y;

	x = cur / game->len + g_dx[dir];
	y = cur % game->len + g_dy[dir];
	if (x < 0 || y < 0 || x >= game->lines || y >= game->len
		|| game->map[x][y] == '1')
		return (-1);
	return (x * game->len + y);
}

/* Breadth first search from the player: dist[cell] is the number of steps
   to the player, or -1 when the player can not be reached from that cell. */
static void	ghost_dist(t_game *game)
{
	int	head;
	int	tail;
	int	dir;
	int	next;

	ft_memset(game->dist, -1, sizeof(int) * game->lines * game->len);
	head = 0;
	tail = 1;
	game->queue[0] = game->pos_x * game->len + game->pos_y;
	game->dist[game->queue[0]] = 0;
	while (head < tail)
	{
		dir = -1;
		while (++dir < 4)
		{
			next = nbr(game, game->queue[head], dir);
			if (next < 0 || game->dist[next] != -1)
				continue ;
			game->dist[next] = game->dist[game->queue[head]] + 1;
			game->queue[tail++] = next;
		}
		head++;
	}
}

/* One tile toward the player. Returns 1 if the ghost reached the player. */
static int	step_ghost(t_game *game, t_ghost *ghost)
{
	int	cur;
	int	dir;
	int	next;

	cur = ghost->x * game->len + ghost->y;
	dir = -1;
	while (game->dist[cur] > 0 && ++dir < 4)
	{
		next = nbr(game, cur, dir);
		if (next < 0 || game->dist[next] != game->dist[cur] - 1
			|| ghost_at(game, next / game->len, next % game->len))
			continue ;
		ghost->x = next / game->len;
		ghost->y = next % game->len;
		break ;
	}
	return (ghost->x == game->pos_x && ghost->y == game->pos_y);
}

int	move_ghosts(t_game *game)
{
	int	i;

	if (game->ghost_count == 0 || !game->ghosts || !game->dist
		|| !game->queue)
		return (0);
	ghost_dist(game);
	i = -1;
	while (++i < game->ghost_count)
		if (step_ghost(game, &game->ghosts[i]))
			return (1);
	return (0);
}
