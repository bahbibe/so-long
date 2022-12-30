/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 17:48:47 by bahbibe           #+#    #+#             */
/*   Updated: 2022/12/30 23:20:47 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_extention(char *str)
{
	int	pos;

	pos = ft_strlen(str) - 4;
	if (ft_strncmp(str + pos, ".ber", 4))
		return (1);
	return (0);
}

int	check(t_game *game, char *filename)
{
	if (check_extention(filename))
		return (set_error(game, "Invalid file name"));
	else if (read_map(game, filename))
		return (set_error(game, "Can not read from file"));
	else if (is_rect(game))
		return (set_error(game, "Invalid Map"));
	else if (is_closed(game))
		return (set_error(game, "Map is not limited by walls"));
	else if (check_token_type(game))
		return (set_error(game, "Invalid token"));
	else if (check_token_count(game))
		return (set_error(game, "Duplicate or missing token"));
	game->map2 = dup_map(game);
	flood_fill_one(game->pos_x, game->pos_y, game->map2);
	if (check_collect(game, 'C'))
		return (set_error(game, "Player Can't reach all collectibles"));
	flood_fill_two(game->pos_x, game->pos_y, game->map2);
	if (check_collect(game, 'E'))
		return (set_error(game, "Player Can not exit"));
	to_free(game->map2);
	return (0);
}

void	exit_error(t_game *game)
{
	ft_putstr_fd("Error:\n", 2);
	ft_putstr_fd(game->error, 2);
	exit (1);
}

int	set_error(t_game *game, char *msg)
{
	game->error = msg;
	return (1);
}
