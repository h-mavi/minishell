/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:02:05 by mfanelli          #+#    #+#             */
/*   Updated: 2025/03/24 14:00:05 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// gestisce i segnali con SIGINT (^c)
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