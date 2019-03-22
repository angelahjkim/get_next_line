/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 21:45:46 by angkim            #+#    #+#             */
/*   Updated: 2019/03/22 00:02:12 by angkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

/*
** Function that returns a line read from a file descriptor.
** The file descriptor and address of the pointer to a character that will be
** used to save the line are passed as paramaters.
** Returns 1 if a line has been read, 0 when the reading is complete, and
** -1 if an error has occured.
*/

#include <stdio.h>		// delete after testing

int     get_next_line(int fd, char **line)
{
	char		*buffer;
	char		*tmp;
	static char	*rem;
	int			bytes_read;
	int			rem_pos;
	int			i;
	int			j;
	int			k;
	int			line_read;
	int			new_size;

	buffer = (char *)malloc(sizeof(char) * BUFF_SIZE);
	rem = NULL;
	/*
	if ((bytes_read = read(fd, buffer, BUFF_SIZE)) == 0)
	{

	}
	*/
	line_read = 0;
	while ((bytes_read = read(fd, buffer, BUFF_SIZE)))
	{
		/* check for '\n' in *buffer */
		i = 0;
		while(i < (bytes_read - 1) && buffer[i] != '\n')
			i++;
printf("buffer: %s\n", buffer);
		if (buffer[i] == '\n')
		{
			rem_pos = i + 1;
			line_read = 1;
		}
		/* allocate line and copy buffer contents */
		if (!(*line))
		{
			*line = (char *)malloc(sizeof(char) * (bytes_read + 1));
			i = 0;
			while (buffer[i] != '\n' && i < (bytes_read))
			{
				line[0][i] = buffer[i];
				i++;
			}
			line[0][i] = '\0';
		}
printf("line[0]: %s\n", line[0]);

		/* if line still being read and buffer does not read '\n', append to existing line */
		if (*line)
		{
			
		}

		/* if *rem holds characters from pvs buffer read, reallocate line with rem and line contents */
		if (rem)
		{

			new_size = (int)ft_strlen(*line) + (int)ft_strlen(rem);
			tmp = (char *)malloc(sizeof(char) * (new_size + 1));
printf("rem: %s\nnew_size: %d\n", rem, new_size);
			j = 0;
			while (j < (int)ft_strlen((rem)))
			{
				tmp[j] = rem[j];
				j++;
			}
printf("tmp: %s\n", tmp);
			
			k = 0;
			while (j < new_size)
			{
				tmp[j] = *line[k];
				j++;
				k++;
			}
			free(rem);
			free(line[0]);
			line[0] = (char *)malloc(sizeof(char) * (new_size + 1));
			line[0] = ft_strcpy(line[0], tmp);
		}
printf("i: %d\n", i);

		/* if there are remaining characters in buffer after a '\n', store in *rem */
		if (line_read && rem_pos < bytes_read)
		{
printf("HERE!!!\n");
return (1);
			if (!(rem))
			{
				rem = (char *)malloc(sizeof(char) * (bytes_read - i));
				j = 0;
				i++;
				while (i < bytes_read)
					rem[j++] = buffer[i++];
printf("!! rem: %s\n", rem);
				rem[j] = '\0';
			}
		}

		/* if buffer contained a '\n', the line has been read and copied, return 1 */
		if (line_read)
			return (1);
	}
	return (-1);
}
