/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:24:05 by ocartier          #+#    #+#             */
/*   Updated: 2022/09/12 10:26:31 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	pass_spaces(char *line, size_t cur)
{
	while (line[cur] == ' ')
		cur++;
	return (cur);
}

int	line_value_size(char *line, size_t cur)
{
	size_t	size;

	size = 0;
	while (line[cur + size] != '\n')
	{
		size++;
		if (ft_is_only(line + cur + size, ' ') && line[cur + size + 1] != '\n')
			return (size);
	}
	return (size);
}

char	*get_line_value(int prefix_len, char *line)
{
	size_t	cur;

	cur = pass_spaces(line, prefix_len);
	return (ft_substr(line, cur, line_value_size(line, cur)));
}
