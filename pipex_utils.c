/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:22:49 by oamairi           #+#    #+#             */
/*   Updated: 2025/08/30 18:42:24 by oamairi          ###   ########.fr       */
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
