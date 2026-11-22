/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghosts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 20:00:00 by bahbibe           #+#    #+#             */
/*   Updated: 2026/11/22 20:00:00 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_ghosts(t_game *game)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (++j < game->len)
			if (game->map[i][j] == 'G')
				count++;
	}
	return (count);
}

static void	fill_ghosts(t_game *game)
{
	int	i;
	int	j;
	int	n;

	n = 0;
	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (++j < game->len)
		{
			if (game->map[i][j] != 'G')
				continue ;
			game->ghosts[n].x = i;
			game->ghosts[n].y = j;
			game->ghosts[n].fx = i;
			game->ghosts[n++].fy = j;
			game->map[i][j] = '0';
		}
	}
}

int	init_ghosts(t_game *game)
{
	int	cells;

	game->ghost_count = count_ghosts(game);
	if (game->ghost_count == 0)
		return (0);
	cells = game->lines * game->len;
	game->ghosts = ft_calloc(game->ghost_count, sizeof(t_ghost));
	game->dist = ft_calloc(cells, sizeof(int));
	game->queue = ft_calloc(cells, sizeof(int));
	if (!game->ghosts || !game->dist || !game->queue)
		return (set_error(game, "Out of memory"));
	fill_ghosts(game);
	return (0);
}

void	free_ghosts(t_game *game)
{
	free(game->ghosts);
	free(game->dist);
	free(game->queue);
	game->ghosts = NULL;
	game->dist = NULL;
	game->queue = NULL;
	game->ghost_count = 0;
}

int	ghost_at(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (game->ghosts && i < game->ghost_count)
	{
		if (game->ghosts[i].x == x && game->ghosts[i].y == y)
			return (1);
		i++;
	}
	return (0);
}
