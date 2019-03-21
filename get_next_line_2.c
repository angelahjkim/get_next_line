/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 21:45:46 by angkim            #+#    #+#             */
/*   Updated: 2019/03/20 23:27:02 by angkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Function that returns a line read from a file descriptor.
** The file descriptor and address of the pointer to a character that will be
** used to save the line are passed as paramaters.
** Returns 1 if a line has been read, 0 when the reading is complete, and
** -1 if an error has occured.
*/

int     get_next_line(int fd, char **line)
{
    char *buffer;
    static char *rem;
    int bytes_read;
    int i;
    int j;

    buffer = (char *)malloc(sizeof(char) * BUFF_SIZE);
    while ((bytes_read = read(fd, buffer, BUFF_SIZE)))
    {
        /* if not near the end of the file */
        if (bytes_read == BUFF_SIZE)
        {
            i = 0;
            /* search buffer for '\n' */
            while (buffer[i] != '\n' && i < BUFF_SIZE)
                i++;
            /* if '\n' found & line empty, allocate and store into *line */
            if (!(*line))
            {
                line = (char **)malloc(sizeof(char *) * 1);
                if (i == (BUFF_SIZE - 1) && buffer[i] == '\n')
                {
                    *line = (char *)malloc(sizeof(char) * BUFF_SIZE);
                    while (i < (BUFF_SIZE - 1))
                        line[i++] = buffer[i++];
                    line[i] = '\0';
                    return (1);
                }
                /* store any remaining characters after '\n' */
                if (i < (BUFF_SIZE - 1) && buffer[i] == '\n')
                {
                    *line = (char *)malloc(sizeof(char) * (i + 1));
                    j = 0;
                    while (j < i)
                        line[j++] = buffer[i++];
                    line[j++] = '\0';
                    *rem = (char *)malloc(sizeof(char) * (BUFF_SIZE - i));
                    while (j < BUFF_SIZE)
                        rem[k++] = buffer[j++];
                    rem[k] = '\0';
                    return (1);
                }
            }
            /* if '\n' found & line not empty, reallocate *line, store, and free pvs */
            if (*line)
            {
                
            }
            /* if *rem is not empty, reallocate *line, store *rem first, then repeat buffer search,
                reallocating *line, and freeing pvs memory areas... should be first check ? */
            
        }
        /* if near the end of file, and bytes read is less than BUFF_SIZE */
        
    }
}