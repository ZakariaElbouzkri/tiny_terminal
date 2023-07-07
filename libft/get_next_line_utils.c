/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 22:54:51 by asettar           #+#    #+#             */
/*   Updated: 2022/11/20 06:53:54 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcat_helper(char *ret, char *dst, char *buff)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dst[i])
	{
		ret[i] = dst[i];
		i++;
	}
	while (buff[j])
		ret[i++] = buff[j++];
	ret[i] = 0;
}

char	*ft_strcat(char *buff, char *dst)
{
	char	*ret;
	int		i;
	int		d;

	if (!dst)
		d = 0;
	else
		d = ft_strlen(dst);
	ret = (char *)malloc(ft_strlen(buff) + d + 1);
	if (!ret)
		return (NULL);
	i = -1;
	if (!dst)
	{
		while (buff[++i])
			ret[i] = buff[i];
		ret[i] = 0;
	}
	else
		ft_strcat_helper(ret, dst, buff);
	free(dst);
	return (ret);
}

char	*ft_read_line(char *dst)
{
	char	*line;
	int		i;
	int		j;

	if (!dst)
		return (NULL);
	i = 0;
	while (dst[i] && dst[i] != '\n')
		i++;
	if (dst[i] == '\n')
		i++;
	line = (char *)malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = dst[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_trim(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	j = 0;
	ret = (char *)malloc(ft_strlen(str) - i + 1);
	if (!ret)
		return (NULL);
	while (str[i])
		ret[j++] = str[i++];
	ret[j] = 0;
	free(str);
	return (ret);
}
