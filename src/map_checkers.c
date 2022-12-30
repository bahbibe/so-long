/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 17:35:49 by bahbibe           #+#    #+#             */
/*   Updated: 2022/12/30 20:38:18 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_rect(t_game *game)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (game->map[i])
	{
		if (ft_line_len(game->map[0]) == ft_line_len(game->map[i]))
			i++;
		else
			return (1);
	}
	j = game->lines - 1;
	k = ft_line_len(game->map[j]);
	if (game->map[j][k] == '\n')
		return (1);
	return (0);
}

int	is_closed(t_game *game)
{
	int	i;
	int	j;

	game->len = ft_line_len(game->map[0]);
	i = 0;
	while (i < game->lines)
	{
		j = 0;
		while (j < game->len)
		{
			if (i == 0 || i == game->lines - 1 || j == 0 || j == game->len - 1)
			{
				if (game->map[i][j] != '1')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_token_type( t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->lines)
	{
		j = 0;
		while (j < game->len)
		{
			if (game->map[i][j] != 'P' && game->map[i][j] != 'E' &&
				game->map[i][j] != 'C' && game->map[i][j] != '0' &&
				game->map[i][j] != '1' && game->map[i][j] != 'G')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_token_count(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{	
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == 'E')
				game->exit++;
			if (game->map[i][j] == 'P')
			{
				game->pos++;
				game->pos_x = i;
				game->pos_y = j;
			}
			if (game->map[i][j] == 'C')
				game->colct++;
		}
		i++;
	}
	if (game->exit != 1 || game->pos != 1 || game->colct == 0)
		return (1);
	return (0);
}

int	check_collect(t_game *game, char c)
{
	int	i;
	int	j;

	i = 0;
	while (game->map2[i])
	{
		j = 0;
		while (game->map2[i][j])
		{
			if (game->map2[i][j] == c)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
