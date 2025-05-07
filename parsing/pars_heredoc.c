/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:23:18 by mfanelli          #+#    #+#             */
/*   Updated: 2025/05/07 10:22:49 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* Fa la comparazione tra l'input dato dallo user e il limiter
dell'heredoc */
static int	control_str(char *str, char *argv)
{
	if (str == NULL)
		return (write(0, "\n", 2), 1);
	if (argv[0] == '<')
		argv = argv + 2;
	if ((ft_strncmp(str, argv, ft_strlen(argv)) == 0) && \
	str[ft_strlen(argv)] == '\n')
		return (1);
	return (0);
}

/* Apre l'heredoc usando input come limiter */
void	here_doc(char *input)
{
	char	*str;
	int		file;
	int		std;

	std = dup(0);
	file = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		return ;
	write(1, "> ", 2);
	signal(SIGINT, test);
	str = get_next_line(0);
	if (g_sigal == 1)
		dup2(std, 0);
	while (control_str(str, input) == 0)
	{
		ft_putstr_fd(str, file);
		free(str);
		write(1, "> ", 2);
		str = get_next_line(0);
		if (g_sigal == 1)
			dup2(std, 0);
	}
	close(std);
	free(str);
	get_next_line(file);
	close(file);
	unlink("here_doc");
}

int	is_all_whitespace(char *cmd)
{
	int		i;
	size_t	x;

	i = 0;
	x = 0;
	while (cmd[i] != '\0' && cmd[i] != '\n')
	{
		if (cmd[i] > 0 && cmd[i] < 33)
			x++;
		i++;
	}
	if (x == ft_strlen(cmd))
		return (0);
	return (1);
}

int	smol(char *s, int i)
{
	if (s[i] == '$' && ((ft_isalpha(s[i + 1]) != 0) || (s[i + 1] == '_')))
		return (1);
	return (0);
}
