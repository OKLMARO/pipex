/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:22:49 by oamairi           #+#    #+#             */
/*   Updated: 2025/09/11 13:14:36 by oamairi          ###   ########.fr       */
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

int	make_storage(char ***cmd, char *argv, char **all_cmd, char **path)
{
	*cmd = ft_split(argv, ' ');
	if (!*cmd)
		return (perror("Malloc crash"), 0);
	*all_cmd = valid_command(*cmd[0], path);
	if (!*all_cmd)
		return (free_double(*cmd),
			perror("Commande introuvable ou non executable"), 0);
	return (1);
}

int	init_var(t_pipex_content *content, char **env)
{
	content->env = env;
	pipe(content->pip);
	content->cmd = NULL;
	content->all_cmd = NULL;
	return (1);
}

void	finish(t_pipex_content *content, pid_t fils[2])
{
	close(content->pip[0]);
	close(content->pip[1]);
	waitpid(fils[0], NULL, 0);
	waitpid(fils[1], NULL, 0);
}
