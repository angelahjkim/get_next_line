/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:32:55 by angkim            #+#    #+#             */
/*   Updated: 2019/03/30 14:18:21 by angkim           ###   ########.fr       */
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

/*
** Check if there is a newline in stack. If there is no newline return (0).
** If there is a newline, copy up to the newline into line, and any remaining
** characters back into stack.
*/

static int	find_nl(char **stack, char **line)
{
	char *cpy_stack;
	char *chr_stack;
	int i;

	chr_stack = *stack;
	i = 0;
	while (chr_stack[i] != '\n')
	{
		if (!chr_stack[i])
			return (0);
		i++;
	}
	cpy_stack = &chr_stack[i];
	*cpy_stack = '\0';
	*line = ft_strdup(*stack);
	*stack = ft_strdup(cpy_stack + 1);
	return (1);
}

/*
** read from file into heap, copy contents into stack, check if there is a
** newline (find_nl), if find_nl returns (1), return (1). If not, continue
** reading from file into heap, adding to what is in stack, checking for NL
*/

static int	read_file(int fd, char *heap, char **stack, char **line)
{
	int bytes_read;
	char *cpy_stack;

	while ((bytes_read = read(fd, heap, BUFF_SIZE)) > 0)
	{
		if (bytes_read != BUFF_SIZE)
			ft_strclr((heap + bytes_read));
		if (*stack)
		{
			if (bytes_read != BUFF_SIZE)
				ft_strclr(heap + bytes_read);
			cpy_stack = *stack;
			*stack = ft_strjoin(cpy_stack, heap);
			free(cpy_stack);
			cpy_stack = NULL;
		}
		else
		{
			*stack = ft_strdup(heap);
		}
		if (find_nl(stack, line))
			break;
	}
	return (bytes_read);
}

/*
** First checks for any errors (if either fd or line are not valid).
** If there was something in stack from a previous read, check for NL.
** If there is nothing in the stack, allocate memory for the heap and read
** the file. Check for conditions in which *line should be null.
** Once the line is read, copy what is left in stack into *line, reset stack to NULL.
*/

int		get_next_line(int fd, char **line)
{
	char 		*heap;
	static char	*stack[FD_MAX];
	int			bytes_read;

	/*
	** If invalid fd, return -1
	*/
	if ((fd < 0 || fd >= FD_MAX) || !line || (read(fd, stack[fd], 0) < 0))
		return (-1);

	/*
	** allocate heap and initialize to null
	*/
	heap = (char *)malloc(sizeof(char) * BUFF_SIZE + 1);
	if (!heap)
		return (-1);
	ft_bzero(heap, BUFF_SIZE + 1);

	/* if there is something in stack from a pvs read, check for NL */
	if (*stack)
	{
		if (find_nl(&stack[fd], line) == 1)
			return (1);
	}

	/* 
	** if there is nothing in stack, allocate memory for the heap and
	** read the file.
	*/
	bytes_read = read_file(fd, heap, &stack[fd], line);
	free(heap);
	
	/* check for conditions when *line should be NULL */
	if (bytes_read != 0 || stack[fd] == NULL || stack[fd][0] == '\0')
	{
		if (!bytes_read && *line)
			*line = NULL;
		return (bytes_read);
	}

	/* once line is read, copy stack into *line, set stack to NULL */
	*line = stack[fd];
	stack[fd] = NULL;
	return (1);
}
