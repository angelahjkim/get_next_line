/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:32:52 by angkim            #+#    #+#             */
/*   Updated: 2019/04/03 10:24:43 by angkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** 
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
** 
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
			*stack = ft_strdup(heap);
		if (find_nl(stack, line))
			break;
	}
	return (bytes_read);
}

/*
**
*/

int		get_next_line(int fd, char **line)
{
	char 		*heap;
	static char	*stack[FD_MAX];
	int			bytes_read;

	
	if ((fd < 0 || fd >= FD_MAX) || !line || (read(fd, stack[fd], 0) < 0))
		return (-1);
	
	heap = (char *)malloc(sizeof(char) * BUFF_SIZE + 1);
	if (!heap)
		return (-1);
	ft_bzero(heap, BUFF_SIZE + 1);
	
	if (*stack)
	{
		if (find_nl(&stack[fd], line) == 1)
			return (1);
	}
	
	bytes_read = read_file(fd, heap, &stack[fd], line);
	free(heap);
	
	if (bytes_read != 0 || stack[fd] == NULL || stack[fd][0] == '\0')
	{
		if (!bytes_read && *line)
			*line = NULL;
		return (bytes_read);

	*line = stack[fd];
	stack[fd] = NULL;
	return (1);
}
