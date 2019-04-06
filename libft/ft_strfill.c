/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_strarray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 17:01:54 by angkim            #+#    #+#             */
/*   Updated: 2019/03/04 17:05:18 by angkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** fills s1 with a substring from s2 specified from start and end positions
*/

char	*ft_strfill(char *s1, const char *s2, int start, int end)
{
	int i;

	i = 0;
	while (start < end)
	{
		s1[i] = s2[start];
		i++;
		start++;
	}
	s1[i] = '\0';
	return (s1);
}
