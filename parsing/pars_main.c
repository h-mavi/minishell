/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:02:05 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/23 15:32:31 by mfanelli         ###   ########.fr       */
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
	if (sig == -1)
	{
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
		if (str[i][0] == '\0')
			continue ;
		if (check == 0 && find_char(str[i], 0) == 0)
		{
			set_data(head, &str[i], COMMAND);
			check = 1;
		}
		else if (find_char(str[i], 0) != 3 && find_char(str[i], 0) != 0)
			set_data(head, &str[i], find_char(str[i], 0));
		else if (find_char(str[i], 0) == PIPE)
		{
			set_data(head, &str[i], PIPE);
			check = 0;
		}
		else
			set_data(head, &str[i], FLAG);
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
	set_data(NULL, NULL, 0);
	if (check_error_lst(head) == 0)
		return (free_arr(str), NULL);
	set_prev(&head);
	return (free_arr(str), head);
}

/* Registra l'history, gestisce ^D e chiama token_inator*/
int	parsing(char *pwd, char **env_cpy)
{
	char	*cmd;
	t_token	*head;

	cmd = readline(pwd);
	head = NULL;
	free(pwd);
	add_history(cmd);
	if (!cmd)
	{
		printf("exit\n");
		free(cmd);
		return (0);
	}
	else if (cmd[0] == '\0')
		return (free(cmd), routine(-1), 1);
	head = token_inator(cmd, env_cpy, head);
	if (head == NULL)
		return (1);
	// print_lists(head);
	execute(head, &env_cpy);
	if (head != NULL)
		free_lst(head);
	return (1);
}

int	main(int argc, char *argv[], char **env)
{
	char	*temp;
	char	*pwd;
	char	**env_cpy;

	(void)argc;
	(void)argv;
	signal(SIGINT, routine);
	signal(SIGQUIT, SIG_IGN);
	env_cpy = ft_env_cpy(env);
	while (1)
	{
		temp = getcwd(NULL, 0);
		pwd = ft_strjoin(temp, "$ ");
		free(temp);
		if (parsing(pwd, env_cpy) == 0)
			break ;
	}
	free_arr(env_cpy);
	return (0);
}
