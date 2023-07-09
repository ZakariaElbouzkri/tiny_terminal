/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 01:44:37 by asettar           #+#    #+#             */
/*   Updated: 2023/07/09 02:46:36 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	exist(const char *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && exist(set, s1[i]))
		i++;
	start = i;
	if (start == (int)ft_strlen(s1))
		return (free(s1), ft_strdup(""));
	end = ft_strlen(s1) - 1;
	while (end > 0 && exist(set, s1[end]))
		end--;
	str = (char *)malloc(end - start + 2);
	if (!str)
		return (free(s1), NULL);
	ft_strlcpy(str, s1 + start, end - start + 2);
	return (free(s1), str);
}
