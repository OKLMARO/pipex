/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:28:14 by oamairi           #+#    #+#             */
/*   Updated: 2025/07/26 17:27:32 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include	"ft_printf/ft_printf.h"
# include	"libft/libft.h"
# include	<sys/wait.h>
# include	<unistd.h>
# include	<stdlib.h>
# include	<string.h>
# include	<stdio.h>
# include	<fcntl.h>

void	free_double(char **tab_str);
int		make_storage(char ***cmd, char *argv, char **all_cmd, char **path);

#endif