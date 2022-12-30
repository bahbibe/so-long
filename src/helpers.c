/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:52:21 by bahbibe           #+#    #+#             */
/*   Updated: 2022/12/31 00:26:07 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	to_free(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char	**dup_map(t_game *game)
{
	int		i;
	char	**map2;

	i = 0;
	map2 = (char **)malloc(sizeof(char *) * (game->lines + 1));
	while (game->map[i])
	{
		map2[i] = ft_strdup(game->map[i]);
		i ++;
	}
	map2[i] = NULL;
	return (map2);
}

int	ft_line_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	return (i);
}

int	read_map(t_game *game, char *filename)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		game->lines++;
		free(line);
		line = get_next_line(fd);
	}
	if (!game->lines)
		return (1);
	close(fd);
	game->map = (char **)malloc(sizeof(char *) * (game->lines + 1));
	fd = open(filename, O_RDONLY);
	i = 0;
	while (i < game->lines)
		game->map[i++] = get_next_line(fd);
	game->map[i] = NULL;
	return (0);
}
