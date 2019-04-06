/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrtostr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 16:15:57 by angkim            #+#    #+#             */
/*   Updated: 2019/03/12 11:59:48 by angkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Takes a number and returns a string containing the ascii values for each
** digit of the number.
*/

char	*ft_nbrtostr(char *s, long n, int len)
{
	int i;

	i = 0;
	if (n == 0)
	{
		s[0] = '0';
		s[1] = '\0';
		return (s);
	}
	while (i < len)
	{
		if (n % 10 == 0 && n != 0)
			s[i] = '0';
		if (n % 10)
			s[i] = n % 10 + '0';
		n /= 10;
		i++;
		s[i] = '\0';
	}
	return (s);
}
