/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 22:54:36 by asettar           #+#    #+#             */
/*   Updated: 2022/11/20 06:55:01 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_newline(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	static char	*dst;
	int			res;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	res = 1;
	while (res > 0 && ft_check_newline(dst) == 0)
	{
		res = read(fd, buff, BUFFER_SIZE);
		if (res < 0 || (res == 0 && !dst) || (res == 0 && dst[0] == 0))
		{
			free(dst);
			return (NULL);
		}
		buff[res] = '\0';
		dst = ft_strcat(buff, dst);
	}
	line = ft_read_line(dst);
	dst = ft_trim(dst);
	return (line);
}
