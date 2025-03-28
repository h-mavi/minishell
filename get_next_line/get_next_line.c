/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:15:14 by mbiagi            #+#    #+#             */
/*   Updated: 2025/02/24 18:03:14 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdel(char *str, char *src)
{
	char	*new_str;
	int		len;
	int		len_str;
	int		x;

	x = 0;
	len_str = ft_strlen(str);
	while ((str[x] == src[x]) && str[x] && src[x])
		x++;
	if (x == (int)ft_strlen(str))
	{
		free(str);
		return ((char *) ft_calloc(1, 1));
	}
	len = ft_strlen(str) - x;
	new_str = ft_calloc(len + 1, 1);
	new_str[len] = str[len_str];
	while (--len >= 0)
		new_str[len] = str[--len_str];
	free(str);
	return (new_str);
}

char	*ft_read(char *buffer, int fd)
{
	char	*comp;
	int		x;

	comp = ft_calloc(1, 1);
	*comp = '\0';
	x = read(fd, buffer, BUFFER_SIZE);
	if (x == -1)
	{
		if (comp)
			free(comp);
		return (NULL);
	}
	while ((x > 0) && (ft_strchr2(buffer, '\n') == 0))
	{
		buffer[x] = '\0';
		comp = ft_strjoin3(comp, buffer);
		x = read(fd, buffer, BUFFER_SIZE);
	}
	if (x != 0)
	{
		buffer[x] = '\0';
		comp = ft_strjoin3(comp, buffer);
	}
	free(buffer);
	return (comp);
}

char	*ft_cpy(char *str, char **plus, char *buffer)
{
	int	i;

	i = 0;
	i = ft_strchr2(buffer, '\n');
	if (i == 0)
		i = ft_strlen(buffer);
	if (ft_strchr2(str, '\n') == 0)
	{
		str = ft_strjoin2(str, buffer);
		*plus = ft_strjoin3(*plus, &buffer[i]);
	}
	else
		*plus = ft_strjoin3(*plus, buffer);
	if (str[0] == '\0')
	{
		free(str);
		free(*plus);
		*plus = NULL;
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*plus;
	char		*str;
	char		*buffer;

	str = ft_calloc(1, 1);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (plus != NULL)
	{
		str = ft_strjoin2(str, plus);
		plus = ft_strdel(plus, str);
	}
	else
		plus = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	buffer = ft_read(buffer, fd);
	if (buffer == NULL)
		return (NULL);
	str = ft_cpy(str, &plus, buffer);
	return (str);
}
/* 
int	main()
{
	int		fd;
	char	*f;
	int		x;

	x = 1;
	fd = open("map.ber", O_RDONLY, 777);
	f = get_next_line(fd);
	while (f != NULL)
	{
		x++;
		printf("%s", f);
		free(f);
		f = get_next_line(fd);
	}
	printf("%s", f);
	free(f);
	close(fd);
	return (0);
} */
