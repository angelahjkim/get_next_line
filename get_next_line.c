/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 16:11:00 by angkim            #+#    #+#             */
/*   Updated: 2019/03/20 14:48:26 by angkim           ###   ########.fr       */
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

static char *gnl_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (s);
}

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

char	*gnl_strdup(char *s1)
{
	char	*s1_copy;

	if (!(s1_copy = (char *)malloc(sizeof(char) * line_len(s1, '\n'))))
		return (NULL);
	return (ft_strncpy(s1_copy, s1, line_len(s1, '\n')));
}

int     get_next_line(int fd, char **line)
{
    char *buffer;
    char *line_end;
    //char *rem;
    int bytes_read;

    buffer = (char *)malloc(sizeof(char) * BUFF_SIZE);
    if ((bytes_read = read(fd, buffer, BUFF_SIZE)))
    {
        line_end = gnl_strchr(buffer, '\n');
        if (!(line_len(line_end, '\n')))
            line_end -= 1;
        printf("line_end: %s\n", line_end);
        *line = gnl_strdup(line_end);
        printf("line: %s\n", *line);
        
    }
    return (1);
}





/*
    char        *str;
    char        *buffer;
    static char *p;
    int         br;

    str = NULL;
    buffer = (char *)malloc(sizeof(char) * BUFF_SIZE);
    if (buffer)
    {
        while ((br = read(fd, buffer, BUFF_SIZE)))
        {
            p = ft_strchr(buffer, 10);
            *line = ft_strdup(buffer);
        }
printf("br: %d\nBUFF_SIZE: %d\nbuffer: %s\nline: %s\n", br, BUFF_SIZE, buffer, *line);
    }
//    while (ft_strchr(p, 10))
    return (1);
}

get_next_line(fd, &str);
"aaaaaa\naaaa\naaa"
"aaa"

*/