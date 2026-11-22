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

	if (!map)
		return ;
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

	map2 = (char **)ft_calloc(game->lines + 1, sizeof(char *));
	if (!map2)
		return (NULL);
	i = 0;
	while (game->map[i])
	{
		map2[i] = ft_strdup(game->map[i]);
		if (!map2[i])
		{
			to_free(map2);
			return (NULL);
		}
		i++;
	}
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

static int	count_lines(char *filename)
{
	char	*line;
	int		fd;
	int		lines;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

int	read_map(t_game *game, char *filename)
{
	int	fd;
	int	i;

	game->lines = count_lines(filename);
	if (!game->lines)
		return (1);
	game->map = (char **)ft_calloc(game->lines + 1, sizeof(char *));
	fd = open(filename, O_RDONLY);
	if (!game->map || fd == -1)
		return (1);
	i = 0;
	while (i < game->lines)
	{
		game->map[i] = get_next_line(fd);
		if (!game->map[i++])
		{
			close(fd);
			return (1);
		}
	}
	close(fd);
	return (0);
}
