/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:28:14 by oamairi           #+#    #+#             */
/*   Updated: 2025/08/30 18:40:00 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct pipex_utils
{
	int		pip[2];
	char	**cmd;
	char	*all_cmd;
	char	**path;
	int		file_in;
	int		file_out;
	char	**env;
}					t_pipex_content;

void	free_double(char **tab_str);
int		make_storage(char ***cmd, char *argv, char **all_cmd, char **path);
char	*valid_command(char *cmd, char **path);

#endif