/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:19:55 by ocartier          #+#    #+#             */
/*   Updated: 2022/09/12 10:20:19 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*decimal_to_hexadecimal(int decimal)
{
	char	*hexadecimal;
	int		cur;

	if (decimal < 0 || decimal > 255)
		return (NULL);
	hexadecimal = ft_calloc(3, sizeof(char));
	ft_memset(hexadecimal, '0', 2);
	cur = 1;
	while (decimal > 0)
	{
		hexadecimal[cur--] =  "0123456789ABCDEF"[decimal % 16];
		decimal /= 16;
	}
	return (hexadecimal);
}

int	check_rgb_string_format(char *rgb_string)
{
	int	cur;
	int	comma_count;

	cur = 0;
	comma_count = 0;
	while (rgb_string[cur])
	{
		if (rgb_string[cur] == ',')
		{
			comma_count++;
			if (comma_count > 2)
				return (0);
		}
		else if (rgb_string[cur] == '+')
		{
			if (!ft_isdigit(rgb_string[cur + 1]))
				return (0);
		}
		else if (!ft_isdigit(rgb_string[cur]))
			return (0);
		cur++;
	}
	//ft_printf("string: %s, comma_count = %d\n", rgb_string, comma_count);
	return (1);
}
