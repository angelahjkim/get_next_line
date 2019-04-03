/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:32:52 by angkim            #+#    #+#             */
/*   Updated: 2019/04/03 13:05:00 by angkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** This function searches the string pointed to by queue for a '\n'.
** If found, chr_queue points to the memory location of '\n' and replaces it
** with '\0'. Then, sets the address of line to queue and sets the address of
** queue to the memory location right after '\0'.
*/

static int	find_nl(char **queue, char **line)
{
	char	*cpy_queue;
	char	*nl_queue;
	int		i;

	nl_queue = *queue;
	i = 0;
	while (nl_queue[i] != '\n')
	{
		if (!nl_queue[i])
			return (0);
		i++;
	}
	nl_queue[i] = '\0';
	*line = (char *)malloc(sizeof(char) * i + 1);
	*line = ft_strcpy(*line, nl_queue);
	cpy_queue = ft_strdup(&(nl_queue[i + 1]));
	free(*queue);
	*queue = ft_strdup(cpy_queue);
	free(cpy_queue);
	return (1);
}

/*
** This function takes the fd, addresses to buffer, queue, and line, and reads
** from fd to buffer. If the bytes read is not equal to BUFF_SIZE, I initialize
** the memory after the bytes read to '\0'. If there is something in queue
** I use ft_strjoin to append what was read into buffer to what is already in
** queue. Then I pass the memory location of queue to my find_nl function
** which will return a 1 if a newline is found, and 0 otherwise.
*/

static int	read_file(int fd, char *buffer, char **queue, char **line)
{
	int		bytes_read;
	char	*cpy_queue;

	while ((bytes_read = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		if (bytes_read != BUFF_SIZE)
			ft_strclr((buffer + bytes_read));
		if (*queue)
		{
			cpy_queue = *queue;
			*queue = ft_strjoin(cpy_queue, buffer);
			free(cpy_queue);
			cpy_queue = NULL;
		}
		else
			*queue = ft_strdup(buffer);
		if (find_nl(queue, line))
			break ;
	}
	if (bytes_read > 0)
		return (1);
	return (bytes_read);
}

/*
** First, I check for invalid file descriptors, line, or file contents and
** return (-1) in any of those cases. If fds and line are valid, I allocate
** memory for my pointer buffer to BUFF_SIZE + 1 and initialize the memory to
** NULL. If my static pointer "queue" is already allocated. I pass the
** addresses of queue and line to my find_nl function. If *queue is not
** pointing to any valid memory, I begin my read from the fd using my
** read_file function.
*/

int			get_next_line(int fd, char **line)
{
	char		*buffer;
	static char	*queue[FD_MAX];
	int			bytes_read;

	if ((fd < 0 || fd >= FD_MAX) || !line)
		return (-1);
	if (!(buffer = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	ft_bzero(buffer, BUFF_SIZE + 1);
	if (queue[fd])
	{
		if (find_nl(&queue[fd], line) == 1)
		{
			return (1);
		}
	}
	bytes_read = read_file(fd, buffer, &queue[fd], line);
	free(buffer);
	if (bytes_read != 0 || queue[fd] == NULL || queue[fd][0] == '\0')
	{
		if (!bytes_read && *line)
			*line = NULL;
		return (bytes_read);
	}
	*line = queue[fd];
	free(queue[fd]);
	return (1);
}
