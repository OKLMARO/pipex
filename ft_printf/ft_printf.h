/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:59:50 by oamairi           #+#    #+#             */
/*   Updated: 2025/05/07 14:20:10 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

int		ft_putchar(char c);
int		ft_putnbr(int nb);
int		ft_putstr(const char *s);
size_t	ft_strlen(const char *s);
int		ft_putnbr_hex(unsigned int nb);
int		ft_putnbr_hex_upper(unsigned int nb);
int		ft_putnbr_unsigned(unsigned int nb);
char	*ft_strdup(const char *s);
int		ft_putpointer(unsigned long nb);
int		ft_printf(const char *str, ...);

#endif