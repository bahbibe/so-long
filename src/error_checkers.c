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
	size_t	len;

	len = ft_strlen(str);
	if (len <= 4 || ft_strncmp(str + len - 4, ".ber", 4))
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
	return (check_path(game));
}

void	exit_error(t_game *game)
{
	ft_putstr_fd("Error:\n", 2);
	if (game->error)
		ft_putstr_fd(game->error, 2);
	ft_putstr_fd("\n", 2);
	to_free(game->map);
	free_ghosts(game);
	exit (1);
}

int	set_error(t_game *game, char *msg)
{
	game->error = msg;
	return (1);
}
