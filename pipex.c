/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:21:41 by oamairi           #+#    #+#             */
/*   Updated: 2025/07/24 15:58:27 by oamairi          ###   ########.fr       */
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
	if (!valid_cmd)
		return (NULL);
	while (path[i])
	{
		temp = ft_strjoin(path[i], valid_cmd);
		if (!temp)
			return (free(valid_cmd), NULL);
		if (access(temp, X_OK) == 0)
			return (free(valid_cmd), temp);
		free(temp);
		i++;
	}
	return (free(valid_cmd), NULL);
}

int	first(char *file_in, int pip[2], char *all_cmd, char **cmd)
{
	pid_t	fils;
	int		file;

	file = open(file_in, O_RDONLY);
	if (file < 0)
		return (perror("Fichier de lecture manquant"), 2);
	fils = fork();
	if (fils == 0)
	{
		if (dup2(file, 0) == -1 || dup2(pip[1], 1) == -1)
			return (perror("Erreur dans le dup2"), 2);
		execve(all_cmd, cmd, NULL);
		perror("Erreur dans l'execution");
        close(file);
        close(pip[1]);
        free(all_cmd);
        free_double(cmd);
        exit(2);
	}
	waitpid(fils, NULL, 0);
	close(file);
	close(pip[1]);
	return (1);
}

int	second(char *file_out, int pip[2], char *all_cmd, char **cmd)
{
	pid_t	fils;
	int		file;

	file = open(file_out, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (!file)
		return (perror("Probleme lors de l'ouverture du fichier de sortie"), 2);
	fils = fork();
	if (fils == 0)
	{
		if (dup2(file, 1) == -1 || dup2(pip[0], 0) == -1)
			return (perror("Erreur dans le dup2"), 2);
		execve(all_cmd, cmd, NULL);
		perror("Erreur dans l'execution");
        close(file);
        close(pip[1]);
        free(all_cmd);
        free_double(cmd);
        exit(2);
	}
	waitpid(fils, NULL, 0);
	close(file);
	close(pip[0]);
	return (1);
}

/*int	make_storage(char **cmd, char *argv, char *all_cmd, char **path)
{
	cmd = ft_split(argv, ' ');
	if (!cmd)
		return (perror("Malloc crash"), 0);
	all_cmd = valid_command(cmd[0], path);
	if (!all_cmd)
		return (free_double(cmd), perror("Commande introuvable ou non executable"), 0);
	return (1);
}*/

int	main(int argc, char **argv, char **env)
{
	int		pip[2];
	char	**cmd;
	char	*all_cmd;
	char	**path;

	if (argc != 5)
		return (perror("Nombre d'argument incorrect !"), 2);
	path = get_path(env);
	if (!path)
		return (perror("Erreur path"), 2);
	pipe(pip);
	cmd = NULL;
	all_cmd = NULL;
	/*if (make_storage(cmd, argv[2], all_cmd, path) == 0)
		return (free_double(path), 2);*/
	cmd = ft_split(argv[2], ' ');
	if (!cmd)
		return (perror("Malloc crash"), 0);
	all_cmd = valid_command(cmd[0], path);
	if (!all_cmd)
		return (free_double(cmd), perror("Commande introuvable ou non executable"), 0);
	if (first(argv[1], pip, all_cmd, cmd) == 2)
		return (free_double(path), free_double(cmd), free(all_cmd), 2);
	(free_double(cmd), free(all_cmd));
	cmd = NULL;
	all_cmd = NULL;
	/*if (make_storage(cmd, argv[3], all_cmd, path) == 0)
		return (free_double(path), 2);*/
	cmd = ft_split(argv[3], ' ');
	if (!cmd)
		return (perror("Malloc crash"), 0);
	all_cmd = valid_command(cmd[0], path);
	if (!all_cmd)
		return (free_double(cmd), perror("Commande introuvable ou non executable"), 0);
	if (second(argv[4], pip, all_cmd, cmd) == 2)
		return (free_double(path), free_double(cmd), free(all_cmd), 2);
	return (free_double(cmd), free_double(path), free(all_cmd), 0);
}
