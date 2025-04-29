/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:23:18 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/29 15:40:18 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* Fa la comparazione tra l'input dato dallo user e il limiter
dell'heredoc */
static int	control_str(char *str, char *argv)
{
	if (str == NULL)
		return (1);
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

	file = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		return ;
	write(1, "> ", 2);
	str = get_next_line(0);
	while (control_str(str, input) == 0)
	{
		ft_putstr_fd(str, file);
		free(str);
		write(1, "> ", 2);
		str = get_next_line(0);
	}
	free(str);
	get_next_line(file);
	close(file);
	unlink("here_doc");
}

/* Filtra la lista head fino al nodo 'where' 
per trovare gli heredoc da aprire */
void	ft_openhd_ls(t_token *head, int where)
{
	while (head->id < where)
	{
		if (head->type == HEREDOC)
			here_doc(head->str);
		head = head->next;
	}
}

/* Filtra la stringa str fino all'indice 'where'
per trovare gli heredoc da aprire */
void	ft_openhd_str(char *str, int where)
{
	int		i;
	int		x;
	char	*tmp;

	i = -1;
	tmp = NULL;
	if ((size_t)where == ft_strlen(str) - 1)
		if (find_char(str, where - 1) != 0 && where > 0)
			where -= 1;
	while (str[++i] && i < where)
	{
		if (find_char(str, i) == HEREDOC || find_char(str, i) == HEREDOC_2)
		{
			x = i + 2;
			while (str[x] != ' ' && find_char(str, x) == 0)
				x++;
			if (x > where)
				continue ;
			tmp = ft_substr(str, i, x - i);
			if (find_char(str, i) == HEREDOC_2)
				tmp = rm_app(tmp);
			here_doc(tmp);
			free(tmp);
		}
	}
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
