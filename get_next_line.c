/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 16:11:00 by angkim            #+#    #+#             */
/*   Updated: 2019/03/20 23:17:36 by angkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>      // delete after testing

/*
** Function returns a line read from a file descriptor. A line is defined as a
** succession of characters that end with '\n' or with EOF. The address of a
** pointer to a character that will be used to save the line is passed to the
** function. Returns 1 if the line has been read, 0 when the reading has been
** completed, and -1 if there is an error.
*/

#include "get_next_line.h"

static int  line_len(char *s, char c)
{
    int len;

    len = 0;
    while (*s && *s != c)
    {
        len++;
        s++;
    }
    return (len);
}

void	*gnl_strdup(char *s1)
{
	char	*s1_copy;

	if (!(s1_copy = (char *)malloc(sizeof(char) * line_len(s1, '\n'))))
		return (NULL);
	return (ft_strncpy(s1_copy, s1, line_len(s1, '\n')));
}

char	*gnl_strncat(char *dst, char *src, int n)
{
	int		i;
	int		j;
	char	*str;

	str = (char *)malloc(sizeof(char) * (ft_strlen(dst) + n + 1));
	i = ft_strlen(src);
	j = 0;
	while (j < n && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

void    get_line(char **line, char *buffer, char *rem)
{
     if (!line)
     {
        *line = gnl_strdup(buffer);
        printf("line: %s\n", *line);
     }
    else
    {
        *line = gnl_strncat(*line, buffer, BUFF_SIZE);
        printf("line strncat: %s\n", *line);
    }
}

int     get_next_line(int fd, char **line)
{
    char *buffer;
    static char *rem;
    int bytes_read;
    int i;
    int j;

    rem = NULL;
    buffer = (char *)malloc(sizeof(char) * BUFF_SIZE);
    /* read BUFF_SIZE from file into buffer */
    while ((bytes_read = read(fd, buffer, BUFF_SIZE)))
    {
        /* search for '\n' in buffer */
        i = 0;
        while ((buffer[i] != '\n') && i < BUFF_SIZE)
            i++;
        /* storing contents of buffer in line as appropriate */
        if (buffer[i] == '\n')
            get_line(line, buffer, rem);
        else
            *line = ft_strdup(buffer);
        /* storing any remaining characters for next line */
        if (i != BUFF_SIZE)
        {
            *rem = (char *)malloc(sizeof(char) * (BUFF_SIZE - i));
            *rem = ft_strsub(buffer, i, (BUFF_SIZE - i));
        }
        printf("line: %s\n", *line);
    }
    return (0);
}