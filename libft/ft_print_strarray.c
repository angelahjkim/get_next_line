/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_strarray.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 17:39:41 by angkim            #+#    #+#             */
/*   Updated: 2019/03/08 16:27:39 by angkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** takes a string array and its length as arguments and prints each string
** followed by a newline character to stdout
*/

void	ft_print_strarray(char **array, int size)
{
	int i;

	i = 0;
	while (array && i < size)
	{
		ft_putstr((char const *)array[i]);
		ft_putchar('\n');
		i++;
	}
}
