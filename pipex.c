/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:21:41 by oamairi           #+#    #+#             */
/*   Updated: 2025/07/15 22:40:07 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	pid_t	fils;
	int		pip[2];
	int		file_in;
	int		file_out;
	char	**cmd;
	char	*all_cmd;
	char	**path;
	int		i;

	if (argc != 5)
	{
		perror("Incorrect number of arguments !");
		exit(2);
	}
	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			path = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	pipe(pip);
	file_in = open(argv[1], O_RDONLY);
	if (!file_in)
		perror("Error open file_in");
	// il faut gerer le fait que la commande soit dans le path ou non
	cmd = ft_split(argv[2], ' ');
	all_cmd = ft_strjoin("/bin/", cmd[0]);
	i = 0;
	int flag = 0;
	while (path[i])
	{
		char *temp = ft_strjoin(path[i], cmd[0]);
		if (access(temp, F_OK) == 0)
		{
			flag = 1;
			break ;
		}
		i++;
		free(temp);
	}
	if (flag == 0)
	{
		perror("Commande introuvable ou non executable");
		return (1);
	}
	file_out = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (!file_out)
		perror("Error open file_out");
	fils = fork();
	if (fils == 0)
	{
		dup2(file_in, 0);
		dup2(pip[1], 1);
		close(file_in);
		execve(all_cmd, cmd, NULL);
	}
	waitpid(fils, NULL, 0);
	// free les cmd et all_cmd
	close(pip[1]);
	cmd = ft_split(argv[3], ' ');
	all_cmd = ft_strjoin("/bin/", cmd[0]);
	dup2(file_out, 1);
	dup2(pip[0], 0);
	execve(all_cmd, cmd, NULL);
	return (0);
}
