/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:14:01 by bahbibe           #+#    #+#             */
/*   Updated: 2022/12/23 14:24:34 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

char	*read_line(int fd, char *str);
char	*true_line(char *str);
char	*rest_of_str(char *str);
char	*get_next_line(int fd);
char	*f_strjoin(char *s1, char *s2);
int		f_strlen(char *s);
char	*f_strchr( char *s, char c);
#endif 
