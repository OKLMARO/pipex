/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:21:41 by oamairi           #+#    #+#             */
/*   Updated: 2025/07/16 15:55:37 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **env)
{
	int		i;
	char	**path;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			path = ft_split(env[i] + 5, ':');
			if (!path)
				return (NULL);
			break ;
		}
		i++;
	}
	return (path);
}

char	*valid_command(char *cmd, char **path)
{
	char	*valid_cmd;
	char	*temp;
	int		i;

	i = 0;
	valid_cmd = ft_strjoin("/", cmd);
	free(cmd);
	while (path[i])
	{
		temp = ft_strjoin(path[i], valid_cmd);
		if (!temp)
			return (0);
		if (access(temp, X_OK) == 0)
			return (temp);
		free(temp);
		i++;
	}
	return (NULL);
}

void	first(int file_in, int pip[2], char *all_cmd, char **cmd)
{
	dup2(file_in, 0);
	dup2(pip[1], 1);
	close(file_in);
	close(pip[1]);
	execve(all_cmd, cmd, NULL);
}

void	second(int file_out, int pip[2], char *all_cmd, char **cmd)
{
	dup2(file_out, 1);
	dup2(pip[0], 0);
	close(file_out);
	close(pip[0]);
	execve(all_cmd, cmd, NULL);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	fils;
	int		pip[2];
	int		file_in;
	int		file_out;
	char	**cmd;
	char	*all_cmd;
	char	**path;

	if (argc != 5)
	{
		perror("Incorrect number of arguments !");
		exit(2);
	}
	path = get_path(env);
	pipe(pip);
	file_in = open(argv[1], O_RDONLY);
	if (!file_in)
		return (perror("Premier fichier non ouvrable"), 1);
	cmd = ft_split(argv[2], ' ');
	all_cmd = valid_command(cmd[0], path);
	if (!all_cmd)
	{
		ft_printf("all cmd : %s\n", all_cmd);
		return (perror("Commande introuvable ou non executable"), 1);
	}
	file_out = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (!file_out)
		perror("Error open file_out");
	fils = fork();
	if (fils == 0)
	{
		first(file_in, pip, all_cmd, cmd);
		return (perror("Erreur d'execution 1er fonction"), 1);
	}
	waitpid(fils, NULL, 0);
	// peut free cmd et all_cmd
	cmd = ft_split(argv[3], ' ');
	all_cmd = valid_command(cmd[0], path);
	if (!all_cmd)
		return (perror("Commande introuvable ou non executable"), 1);
	fils = fork();
	if (fils == 0)
		second(file_out, pip, all_cmd, cmd);
	ft_printf("jrv ici ?");
	return (waitpid(fils, NULL, 0), 0);
}
