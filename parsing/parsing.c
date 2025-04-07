/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:52:21 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/07 17:56:43 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	find_dollar(char *s, int i)
{
	int	x;

	x = i;
	while (s[x])
	{
		if (s[x] == '$')
			return (x);
		x++;
	}
	return (-1);
}

char *reassemble(char *first, char *espan, char *after, int len_cmd)
{
	char	*end;
	int		i;
	int		x;

	end = (char *)ft_calloc((ft_strlen(first) - len_cmd + ft_strlen(espan)) + 1, sizeof(char));
	i = 0;
	x = -1;
	while (first[++x] != '$')
		end[i++] = first[x];
	x = -1;
	while (espan[++x] != '\0')
		end[i++] = espan[x];
	x = -1;
	while (after[++x] != '\0')
		end[i++] = after[x];
	end[i] = '\0';
	free(first);
	return (end);
}

char *esp_special_case(char *s, char **env)
{
	char	*tmp;
	int		start;
	int		end;

	start = find_dollar(s, 0);
	end = start + 1;
	while (s[end] == '_' || ft_isalpha(s[end]) != 0 || ft_isdigit(s[end]) != 0)
		end++;
	tmp = (char *)ft_calloc(end - start + 1, sizeof(char));
	ft_strlcpy(tmp, s + start + 1, end - start);
	tmp = espand(tmp, env);
	s = reassemble(s, tmp, s + end, end - start);
	free(tmp);
	return (s);
}

/* Controlla se ci sono variabili da espandere e, nel caso sia necessario, toglie apici e virgolette. */
char *refine(char *s, char **env)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '$' && werami(s, i) == -1 && werami(s, i + 1) == -1 && \
			((ft_isalpha(s[i + 1]) != 0) || (s[i + 1] == '_')))
			s = espand(s, env);
		else if(((s[i] == '"' && find_dollar(s, i) != -1) || (s[i] == '$' && werami(s, i) == 1 && s[0] == '"')) && \
			((ft_isalpha(s[find_dollar(s, i) + 1]) != 0) || (s[find_dollar(s, i) + 1] == '_')))
			s = esp_special_case(s, env);
		else if (s[i] == '$' && werami(s, i + 1) == 0 && werami(s, i) == -1)
			s = rm_dollar(s);
		if (s[0] == '\0')
			return (s);
	}
	s = rm_app(s);
	return (s);
}

/* Controlla se la stringa datagli corrisponde ad un comando */
// int	check_if_cmd(char *orig, char **env)
// {
// 	int		i;
// 	char	*cmd;
// 	char	*tmp;
// 	char	**path;

// 	i = -1;
// 	path = NULL;
// 	while (env[++i])
// 	{
// 		if (ft_strncmp(env[i], "PATH=", 5) == 0)
// 		{
// 			path = ft_split(env[i] + 5, ':');
// 			break ;
// 		}
// 	}
// 	if (!path)
// 		return (-1); //ERROR
// 	i = -1;
// 	while (path[++i])
// 	{
// 		tmp = ft_strjoin(path[i], "/");
// 		cmd = ft_strjoin(tmp, orig);
// 		free(tmp);
// 		if (access(cmd, F_OK) == 0)
// 			return (free(cmd), free_arr(path), COMMAND);
// 		free(cmd);
// 	}
// 	return (free_arr(path), 0);
// }

int	check_error_lst(t_token *head)
{
	t_token *dopo;

	dopo = head->next;
	if (head->type == PIPE || head->str[0] == ';')
		return (error_exit(head, 0, 0, "Syntax Error, unexpected token at the start of input\n", NULL), 0); //no here_doc
	while (dopo != NULL)
	{
		if (dopo->type == PIPE && head->type == PIPE)
			return (error_exit(head, 1, head->ID, "Syntax Error, unexpected token '|'\n", NULL), 0); //si here_doc
		head = dopo;
		dopo = head->next;
	}
	if (head->type == PIPE)
		return (error_exit(head, 0, 0, "Syntax Error, unexpected token '|' at the end of input\n", NULL), 0); //no here doc
	return (1);
}

void	free_lst(t_token *head)
{
	t_token	*tmp;

	while (head->next != NULL)
	{
		
		free((char *)(*head).str);
		tmp = head;
		head = head->next;
		free(tmp);
	}
	free((char *)(*head).str);
	free(head);
}

int	control_str(char *str, char *argv)
{
	if (str == NULL)
		return (1);
	if ((ft_strncmp(str, argv, ft_strlen(argv)) == 0) && \
	str[ft_strlen(argv)] == '\n')
		return (1);
	return (0);
}

void	here_doc(char *input)
{
	char	*str;

	write(1, "> ", 2);
	str = get_next_line(0);
	while (control_str(str, input + 2) == 0)
	{
		free(str);
		write(1, "> ", 2);
		str = get_next_line(0);	
	}
	free(str);
}

void	ft_openhd_ls(t_token *head, int where)
{
	while (head->ID < where)
	{
		if (head->type == HEREDOC)
			here_doc(head->str);
		head = head->next;
	}
}

void	ft_openhd_str(char *str, int where)
{
	int		i;
	int		x;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] && i < where)
	{
		if (find_char(str, i) == HEREDOC)
		{
			x = i;
			while (str[x] != ' ')
				x++;
			tmp = ft_substr(str, i, x - i); //devo prendere singolarmente <<a, penso che guardare come ho fatto le espansioni copiando e incollando sia una buona idea
			here_doc(tmp);
			free(tmp);
		}
		i++;
	}
}

char *error_exit(t_token *head, int syn, int where, char *str, char *input)
{
	if (syn == 1 && head != NULL && input == NULL)
		ft_openhd_ls(head, where);
	else if (syn == 1 && head == NULL && input != NULL)
		ft_openhd_str(input, where);
	if (input != NULL)
		free(input);
	if (head != NULL)
		free_lst(head);
	printf("%s", str);
	return (NULL);
}
