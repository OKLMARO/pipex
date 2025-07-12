/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:21:41 by oamairi           #+#    #+#             */
/*   Updated: 2025/07/12 17:23:44 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	pid_t	fils;
	int		pip[2];
	int		file_in;
	int		file_out;
	char	**cmd;
	char	*all_cmd;

	if (argc != 5)
	{
		perror("Incorrect number of arguments !");
		exit(2);
	}
	pipe(pip);
	file_in = open(argv[1], O_RDONLY);
	if (!file_in)
		perror("Error open file_in");
	file_out = open(argv[4], O_WRONLY);
	if (!file_out)
		perror("Error open file_out");
	cmd = ft_split(argv[2], ' ');
	all_cmd = ft_strjoin("/bin/", cmd[0]);
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
