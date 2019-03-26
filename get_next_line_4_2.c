/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_4_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:32:55 by angkim            #+#    #+#             */
/*   Updated: 2019/03/25 22:16:42 by angkim           ###   ########.fr       */
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

int		find_nl(char *buf, int br)
{
	int i;

	i = 0;
	while (i < br)
	{
		if (buf[i] == '\n')
		{
printf("found a new line\n");
			return (br - i - 1);
		}
		i++;
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	char *buffer;
	static char *tmp;
	int rem;
	int	bytes_read;

	buffer = (char *)malloc(sizeof(char) * BUFF_SIZE);
	if (buffer)
	{
		while ((bytes_read = read(fd, buffer, BUFF_SIZE)))
		{
printf("buffer: %s\tbytes_read: %d\ttmp: %s\n", buffer, bytes_read, tmp);
			rem = find_nl(buffer, bytes_read);
printf("rem: %d\n", rem);
			if (!*line)
			{
				*line = ft_strnew(bytes_read);
				ft_strncpy(*line, buffer, (bytes_read -= rem));
printf("*line: %s\n", *line);
				if (rem)
				{
					tmp = ft_strnew(rem);
					tmp = ft_strncpy(tmp, &*(buffer + bytes_read), rem);
printf("tmp: %s\tbytes_read: %d\n", tmp, bytes_read);
					return (1);
				}
				return (1);
			}
			else
			{
				/*
				if (!tmp)
				{
					tmp = ft_strnew(bytes_read);
					ft_strncpy(tmp, *line, ft_strlen(*line));
printf("(!tmp)\t*line: %s\ttmp: %s\n", *line, tmp);
					free(*line);
				}
				*/

				*line = ft_strnew(rem);
				ft_strncpy(*line, tmp, rem);
				free(tmp);
				ft_strncat(tmp, buffer, bytes_read);
printf("(tmp)\t*line: %s\ttmp: %s\n", *line, tmp);
				
				/*
				if (rem)
				{
					tmp = ft_strnew(rem);
					tmp = ft_strrchr(buffer, '\n');
				}
				*/

				return (1);
			}
		}
		if (tmp)
		{
			printf("once buffer has read all (no more bytes to be read)\nkeep reading from tmp\n");
			printf("tmp: %s\n", tmp);
		}
	}
	return (0);
}
