/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:02:39 by bahbibe           #+#    #+#             */
/*   Updated: 2022/11/15 04:57:49 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *str)
{
	char	*buff;
	int		rd_len;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	rd_len = 1;
	while (rd_len && !f_strchr(str, '\n'))
	{
		rd_len = read(fd, buff, BUFFER_SIZE);
		if (rd_len == -1)
		{
			free(buff);
			if (str)
				free (str);
			return (NULL);
		}
		buff[rd_len] = '\0';
		str = f_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*true_line(char *str)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i += 1;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		line[j++] = str[i++];
	if (str[i] == '\n')
		line[j++] = str[i++];
	line[i] = '\0';
	return (line);
}

char	*rest_of_str(char *str)
{
	int		i;
	int		j;
	char	*backup;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	backup = (char *)malloc(sizeof(char) * (f_strlen(str) - i));
	if (!backup)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		backup[j++] = str[i++];
	backup[j] = '\0';
	free(str);
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	str = read_line(fd, str);
	if (!str)
		return (NULL);
	line = true_line(str);
	str = rest_of_str(str);
	return (line);
}
