/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:21:41 by oamairi           #+#    #+#             */
/*   Updated: 2025/08/06 17:14:28 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **env)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
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

int	second(char *file_out, t_pipex_content content)
{
	content.file_out = open(file_out, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (!content.file_out)
		return (perror("Probleme lors de l'ouverture du fichier de sortie"), 2);
	if (dup2(content.file_out, 1) == -1 || dup2(content.pip[0], 0) == -1)
		return (perror("Erreur dans le dup2"), close(content.file_out),
			close(content.pip[0]), 2);
	execve(content.all_cmd, content.cmd, content.env);
	perror("Erreur dans l'execution");
	close(content.file_out);
	close(content.pip[0]);
	close(content.pip[1]);
	free(content.all_cmd);
	free_double(content.cmd);
	free_double(content.path);
	exit(2);
}

int	first(char *file_in, t_pipex_content content)
{
	content.file_in = open(file_in, O_RDONLY);
	if (content.file_in < 0)
		return (perror("Fichier de lecture manquant"), 2);
	if (dup2(content.file_in, 0) == -1 || dup2(content.pip[1], 1) == -1)
		return (perror("Erreur dans le dup2"), close(content.file_in),
			close(content.pip[0]), close(content.pip[1]), 2);
	execve(content.all_cmd, content.cmd, content.env);
	perror("Erreur dans l'execution");
	close(content.file_in);
	close(content.pip[1]);
	close(content.pip[0]);
	free(content.all_cmd);
	free_double(content.cmd);
	free_double(content.path);
	exit(2);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	fils[2];
	t_pipex_content	content;

	if (argc != 5)
		return (perror("Nombre d'argument incorrect ou env vide !"), 2);
	content.path = get_path(env);
	if (!content.path)
		return (perror("Erreur dans le path"), 2);
	content.env = env;
	(pipe(content.pip), content.cmd = NULL, content.all_cmd = NULL);
	if (make_storage(&content.cmd, argv[2],
			&content.all_cmd, content.path) == 0)
		return (free_double(content.path), 2);
	fils[0] = fork();
	if (fils[0] < 0)
		return (free_double(content.path), free_double(content.cmd), free(content.all_cmd), 2);
	if (fils[0] == 0)
	{
		if (first(argv[1], content) == 2)
			return (free_double(content.path), free_double(content.cmd), free(content.all_cmd), 2);
	}
	else
	{
		(free_double(content.cmd), free(content.all_cmd), content.cmd = NULL,
			content.all_cmd = NULL);
		if (make_storage(&content.cmd, argv[3], &content.all_cmd,
				content.path) == 0)
			return (free_double(content.path), 2);
		fils[1] = fork();
		if (fils[1] < 0)
			return (free_double(content.path), free_double(content.cmd), free(content.all_cmd), 2);
		if (fils[1] == 0)
		{
			if (second(argv[4], content) == 2)
				return (free_double(content.path), free_double(content.cmd),
					free(content.all_cmd), 2);
		}
		waitpid(fils[0], NULL, 0);
		waitpid(fils[1], NULL, 0);
	}
	
	return (free_double(content.cmd), free_double(content.path),
		free(content.all_cmd), 0);
}
