/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:52:21 by mbiagi            #+#    #+#             */
/*   Updated: 2025/03/31 17:33:04 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//Controlla se la stringa datagli corrisponde ad un comando
int	check_if_cmd(char *orig, char **env)
{
	int		i;
	char	*cmd;
	char	*tmp;
	char	**path;

	i = -1;
	path = NULL;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_split(env[i] + 5, ':');
			break ;
		}
	}
	if (!path)
		return (-1); //ERROR
	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(tmp, orig);
		free(tmp);
		if (access(cmd, F_OK) == 0)
			return (free(cmd), free_arr(path), COMMAND);
		free(cmd);
	}
	return (free_arr(path), 0);
}

//Crea i token
void	token_inator(char *cmd, char **env)
{
	int		i;
	int		check;
	t_token *head;
	char	**str;

	i = -1;
	check = 0;
	head = NULL;
	str = custom_split(cmd);
	if (!str)
	{
		printf("Syntax error type one\n");
		return ;
	}
	while (str[++i] != NULL)
	{
		str[i] = refine(str[i]);
		if (!str[i])
		{
			printf("Syntax error type one\n");
			return ;
		}
		if (check_if_cmd(str[i], env) == COMMAND && check == 0)
		{
			printf("'%s' e' un comando :D\n", str[i]);
			// set_cmd_data(head, str[i]);
			// check = 1;
		}
		else
			printf("'%s' non e' un comando :(\n", str[i]);
		// else if (check_if_redir(str[i], env) == 1)
		// 	set_redir_data(head, str[i]);
		// else if (check_if_pipe(str[i], env) == PIPE && check == 1)
		// {
		// 	set_pipe_data(head, str[i]);
		// 	check = 0;
		// }
		// else if (check == 1)
		// 	set_option_data(head, str[i]);
		// else
		// 	return ;
	}
	// print_lists(head);
	free_arr(str);
}

/* Controlla se ci sono variabili da espandere e, nel caso sia necessario, toglie apici e virgolette. */
char *refine(char *s)
{
	int	i;

	i = -1;
	s = rm_app(s);
	while (s[++i])
	{
		// if (s[i + 1] > '$' &&  s[i + 2] > 64 && s[i + 2] < 91 && ((s[i] == '"') || (werami(s, i) == -1)))
		// 	espand(s);//funzione da fare
	}
	return (s);
}

/* Funzione chiamata da rm_spaces che serve per riscrivere la stringa senza gli spazi in mezzo ai
redir e il loro limiter. */
char *rewrite(char *orig, int i, int x)
{
	int	y;
	char *dest;

	y = -1;
	dest = (char *)ft_calloc(sizeof(char), (ft_strlen(orig) - x) + 1);
	while (orig[++y])
	{
		dest[y] = orig[y];
		if (i == y)
		{
			while (orig[++y + x])
				dest[y] = orig[y + x];
			y++;
			dest[y] = '\0';
			break ;
		}
	}
	free(orig);
	return (dest);
}

/* Serve a togliere gli apici, le virgolette e i back-slash inutili */
char	*rm_app(char *s)
{
	int		i;
	int		x;
	int 	len;
	char	*new;

	i = -1;
	len = 0;
	while (s[++i])
		if ((werami(s, i) != 0 && s[i] != 92) || ((werami(s, i) == 0 || \
		s[i] == 92) && werami(s, i - 1) == 1 && werami(s, i + 1) == 1))
			len++;
	i = -1;
	x = 0;
	new = (char *)ft_calloc(sizeof(char), len + 1);
	while (s[++i])
		if ((werami(s, i) != 0 && s[i] != 92) || ((werami(s, i) == 0 || \
		s[i] == 92) && werami(s, i - 1) == 1 && werami(s, i + 1) == 1))
			new[x++] = s[i];
	new[x] = '\0';
	return (free(s), new);
}

/* Controlla i seguenti errori: 
|||, <>>a, ><a, >>>a, <<<<a,
<|<a, <;<a, <#<a, >|>a, >;>a, >#>a,
>>|a, >>;a, >>#a, <<|a, <<;a, <<#a,
>;a, >#a, <|a, <;a, <#a, */
int	check_error(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '|' && s[i + 1] == '|' && werami(s, i) == -1)
			return (0);
		if (s[i] == '<' && werami(s, i) == -1 && \
			((s[i + 1] == '|') || (s[i + 1] == ';') || (s[i + 1] == '#') \
			|| (s[i + 1] == '<' && s[i + 2] == '<' && s[i + 3] == '<') || \
			(s[i + 1] == '>' && s[i + 2] == '>')))
			return (0);
		if (s[i] == '>' && werami(s, i) == -1 && \
			((s[i + 1] == '|') || (s[i + 1] == ';') || (s[i + 1] == '#') \
			|| (s[i + 1] == '<') || (s[i + 1] == '>' && s[i + 2] == '>')))
			return (0);
	}
	return (1);
}
