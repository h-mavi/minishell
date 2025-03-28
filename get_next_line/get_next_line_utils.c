/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:15:40 by mbiagi            #+#    #+#             */
/*   Updated: 2025/03/28 12:18:00 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// void	*ft_calloc(size_t nmemb, size_t size)
// {
// 	size_t	i;
// 	size_t	max;
// 	void	*ptr;
// 	char	*str;

// 	i = 0;
// 	max = nmemb * size;
// 	if ((nmemb == 0) || (size == 0) || (max / nmemb != size))
// 		return (malloc(0));
// 	ptr = malloc(max);
// 	if (ptr == NULL)
// 		return (NULL);
// 	str = (char *)ptr;
// 	while (i < max)
// 	{
// 		str[i] = 0;
// 		i++;
// 	}
// 	return (ptr);
// }

char	*ft_strjoin3(char *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*str;

	len_s2 = 0;
	if (!s1 || !s2)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	if (len_s2 != 0)
		str[len_s1 + len_s2] = s2[len_s2];
	while (--len_s2 >= 0)
		str[len_s1 + len_s2] = s2[len_s2];
	while (--len_s1 >= 0)
		str[len_s1] = s1[len_s1];
	free(s1);
	return (str);
}

int	ft_strchr2(const char *s, int c)
{
	int				x;
	unsigned char	a;

	x = 0;
	a = (unsigned char) c;
	while ((s[x] != '\0') && (s[x] != a))
		x++;
	if ((s[x] == '\0') && (a != '\0'))
		return (0);
	return (x + 1);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len_s2 = 0;
	len_s1 = ft_strlen(s1);
	while (s2[len_s2] && s2[len_s2] != '\n')
		len_s2++;
	if (s2[len_s2] == '\n')
		len_s2++;
	str = ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	while (i < len_s1)
	{
		str[i] = s1[i];
		i++;
	}
	while (j < len_s2)
		str[i++] = s2[j++];
	free(s1);
	return (str);
}
