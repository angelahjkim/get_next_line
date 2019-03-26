/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:32:55 by angkim            #+#    #+#             */
/*   Updated: 2019/03/25 21:05:49 by angkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** get_next_line returns a line read from a file descriptor.
** The file descriptor and address of the pointer to a character that will be
** used to store the line are passed to the function as a parameter.
** The function returns (1) if a line has been read, (0) when the reading
** is complete, or (-1) if an error has occured.
*/

#include "get_next_line.h"

#include <stdio.h>	// delete after testing

void	find_nl(char **rem, char *buf, int br)
{
	int i;

	i = 0;
	while (i < br)
	{
		if (buf[i] == '\n')
		{
printf("found a new line\n");
			*rem = (char *)ft_strnew(br);
			*rem = (char *)ft_memccpy(*rem, buf, '\n', br);
printf("find_nl rem: %s\n", *rem);
		}
		i++;
	}
}

int		get_next_line(int fd, char **line)
{
	char *buffer;
	char *tmp;
	static char *rem;
	int	bytes_read;

	buffer = (char *)malloc(sizeof(char) * BUFF_SIZE);
	if (buffer)
	{
		while ((bytes_read = read(fd, buffer, BUFF_SIZE)))
		{
printf("buffer: %s\tbytes_read: %d\n", buffer, bytes_read);
			find_nl(&rem, buffer, bytes_read);
printf("rem: %s\n", rem);
			if (rem)
				bytes_read -= (ft_strlen(rem) - 1);
			if (!*line)
			{
				*line = ft_strnew(bytes_read - 1);
				ft_strncpy(*line, buffer, bytes_read);
				if (rem)
					return (1);
			}
			else
			{
				tmp = ft_strnew(bytes_read);
				ft_strncpy(tmp, *line, ft_strlen(*line));
				free(*line);
				*line = ft_strnew(ft_strlen(tmp) + bytes_read);
				ft_strncpy(*line, tmp, ft_strlen(tmp));
				free(tmp);
				ft_strncat(*line, buffer, bytes_read);
				if (rem)
					return (1);
			}
printf("buffer: %s\tline: %s\tbytes read: %d\n", buffer, *line, bytes_read);
		}
	}
	return (0);
}
