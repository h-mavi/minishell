/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:02:05 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/02 12:58:09 by mfanelli         ###   ########.fr       */
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

/* Crea i token */
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
		str[i] = refine(str[i], env);
		if (!str[i])
		{
			printf("Syntax error type one\n");
			return ;
		}
		if (check_if_cmd(str[i], env) == COMMAND && check == 0)
		{
			set_data(&head, str[i], COMMAND);
			check = 1;
		}
		else if (find_char(str[i], 0) != 3 && find_char(str[i], 0) != 0)
			set_data(&head, str[i], find_char(str[i], 0));
		else if (find_char(str[i], 0) == PIPE && check == 1)
		{
			set_data(&head, str[i], PIPE);
			check = 0;
		}
		else if (check == 1)
			set_data(&head, str[i], FLAG);
	}
	print_lists(head);
	free_arr(str);
}

int	parsing(char *pwd, char **env)
{
	char    *cmd;

    cmd = readline(pwd);
    add_history(cmd);
    if (!cmd)
	{
		printf("exit\n");
        free(cmd);
		return (0);
	}
	token_inator(cmd, env);
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
		if(parsing(pwd, env) == 0)
			break;
		free(pwd);
	}
	free(pwd);
	return(0);
}