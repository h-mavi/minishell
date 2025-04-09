/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:02:05 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/09 09:24:11 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* gestisce i segnali con SIGINT (^c) */
void	routine(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/* Compila la lista con i nodi-token */
void	compile_inator(char **str, char **env, t_token **head)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	while (str[++i] != NULL)
	{
		str[i] = refine(str[i], env);
		if (check == 0 && find_char(str[i], 0) == 0)
		{
			set_data(head, &str[i], COMMAND, i);
			check = 1;
		}
		else if (find_char(str[i], 0) != 3 && find_char(str[i], 0) != 0)
			set_data(head, &str[i], find_char(str[i], 0), i);
		else if (find_char(str[i], 0) == PIPE)
		{
			set_data(head, &str[i], PIPE, i);
			check = 0;
		}
		else
			set_data(head, &str[i], FLAG, i);
	}
}

/* Chiama custom_split e il compile_inator e poi returno la lista
liberando anche l'array*/
t_token	*token_inator(char *cmd, char **env, t_token *head)
{
	int		i;
	int		check;
	char	**str;

	i = -1;
	check = 0;
	str = custom_split(cmd);
	if (!str)
		return (NULL);
	compile_inator(str, env, &head);
	if (check_error_lst(head) == 0)
		return (free_arr(str), NULL);
	set_prev(&head);
	return (free_arr(str), head);
}

/* Registra l'history, gestisce ^D e chiama token_inator*/
int	parsing(char *pwd, char **env)
{
	char	*cmd;
	t_token	*head;

	cmd = readline(pwd);
	head = NULL;
	add_history(cmd);
	if (!cmd)
	{
		printf("exit\n");
		free(cmd);
		return (0);
	}
	head = token_inator(cmd, env, head);
	print_lists(head);
	if (head != NULL)
		free_lst(head);
	return (1);
}

int	main(int argc, char *argv[], char **env)
{
	char	*temp;
	char	*pwd;

	(void)argc;
	(void)argv;
	signal(SIGINT, routine);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		temp = getcwd(NULL, 0);
		pwd = ft_strjoin(temp, "$ ");
		free(temp);
		if (parsing(pwd, env) == 0)
			break ;
		free(pwd);
	}
	free(pwd);
	return (0);
}
