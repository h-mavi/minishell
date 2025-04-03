/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:14:58 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/03 15:10:03 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//funzione che serve a gestire gli exit code
void	exit_code(int n)
{
	static int	exit_code;

	if (n == 1000)
		printf("%d", exit_code);
	else
		exit_code = n;
}

// gestisce i segnali con SIGINT (^c) e SIGQUIT (^\)
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

//un primo tentativo mooootlo basico di parsing, gestisce ^D e ls
int	parsing(char *cmd)
{
	DIR				*dir;
	struct dirent	*entry;
	
	if (!cmd)
	{
		printf("exit\n");
		return (0);
	}
	if (cmd[0] == 'l' && cmd[1] == 's' && cmd[2] == '\0')
	{
		dir = opendir(".");
		while ((entry = readdir(dir)) != NULL)
			if (entry->d_name[0] != '.')
				printf("%s ", entry->d_name);
		closedir(dir);
		printf("\n");
		rl_on_new_line();
	}
	free(cmd);
	return (1);
}

int	main(void)
{
	char	*temp;
	char	*pwd;
	
	signal(SIGINT, routine);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		temp = getcwd(NULL, 0);
		pwd = ft_strjoin(temp, "$ ");
		free(temp);
		if(parsing(readline(pwd)) == 0)
			break;
		free(pwd);
	}
	free(pwd);
	return(0);
}
