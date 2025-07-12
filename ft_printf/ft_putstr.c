/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:32:17 by oamairi           #+#    #+#             */
/*   Updated: 2025/05/07 14:18:05 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(const char *s)
{
	if (!s)
		return (ft_putstr("(null)"));
	write(1, s, ft_strlen(s));
	return (ft_strlen(s));
}
