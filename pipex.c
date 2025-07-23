/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:21:41 by oamairi           #+#    #+#             */
/*   Updated: 2025/07/22 18:11:13 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_double(char **tab_str)
{
	int	i;

	i = 0;
	while (tab_str[i])
	{
		free(tab_str[i]);
		i++;
	}
	free(tab_str);
}

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

void	first(char *file_in, int pip[2], char *all_cmd, char **cmd, char **env)
{
	pid_t	fils;
	int		file;

	file = open(file_in, O_RDONLY);
	if (!file)
		return (free(all_cmd), free_double(cmd), perror("Fichier de lecture manquant"));
	fils = fork();
	if (fils == 0)
	{
		if(dup2(file, 0) == -1)
			return (free(all_cmd), free_double(cmd), perror("Erreur dans le dup2"), exit(2));
		if(dup2(pip[1], 1) == -1)
			return (free(all_cmd), free_double(cmd), perror("Erreur dans le dup2"), exit(2));
		execve(all_cmd, cmd, env);
	}
	waitpid(fils, NULL, 0);
	close(file);
	close(pip[1]);
	free(all_cmd);
	free_double(cmd);
}

void	second(char *file_out, int pip[2], char *all_cmd, char **cmd, char **env)
{
	pid_t	fils;
	int		file;

	file = open(file_out, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (!file)
		return (free(all_cmd), free_double(cmd), perror("Probleme lors de l'ouverture du fichier de sortie"), exit(2));
	fils = fork();
	if (fils == 0)
	{
		if(dup2(file, 1) == -1)
			return (free(all_cmd), free_double(cmd), perror("Erreur dans le dup2"), exit(2));
		if(dup2(pip[0], 0) == -1)
			return (free(all_cmd), free_double(cmd), perror("Erreur dans le dup2"), exit(2));
		execve(all_cmd, cmd, env);
	}
	waitpid(fils, NULL, 0);
	close(file);
	close(pip[0]);
	free(all_cmd);
	free_double(cmd);
}

int	main(int argc, char **argv, char **env)
{
	int		pip[2];
	char	**cmd;
	char	*all_cmd;
	char	**path;

	if (argc != 5)
		return	(perror("Incorrect number of arguments !"), exit(2), 0);
	path = get_path(env);
	pipe(pip);
	cmd = ft_split(argv[2], ' ');
	if (!cmd)
		return (perror("Malloc crash"), exit(2), 0);
	all_cmd = valid_command(cmd[0], path);
	if (!all_cmd)
		return (free_double(cmd), perror("Commande introuvable ou non executable"), exit(2), 0);
	first(argv[1], pip, all_cmd, cmd, env);
	cmd = ft_split(argv[3], ' ');
	if (!cmd)
		return (perror("Malloc crash"), 1);
	all_cmd = valid_command(cmd[0], path);
	if (!all_cmd)
		return (free_double(cmd), perror("Commande introuvable ou non executable"), exit(2), 0);
	return (second(argv[4], pip, all_cmd, cmd, env), 0);
}
