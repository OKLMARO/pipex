/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:28:59 by oamairi           #+#    #+#             */
/*   Updated: 2025/05/13 12:30:52 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	printf_pourcent(va_list list, char c)
{
	void	*temp;

	if (c == '%')
		return (ft_putchar('%'));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(list, int)));
	else if (c == 'c')
		return (ft_putchar(va_arg(list, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(list, char *)));
	else if (c == 'x')
		return (ft_putnbr_hex(va_arg(list, int)));
	else if (c == 'X')
		return (ft_putnbr_hex_upper(va_arg(list, int)));
	else if (c == 'u')
		return (ft_putnbr_unsigned(va_arg(list, unsigned int)));
	else if (c == 'p')
	{
		temp = va_arg(list, void *);
		if (!temp)
			return (ft_putpointer((unsigned long) temp));
		return (ft_putstr("0x") + ft_putpointer((unsigned long) temp));
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	list;
	int		i;
	int		count;

	count = 0;
	va_start(list, str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (!str[i + 1])
				return (-1);
			count += printf_pourcent(list, str[i + 1]);
			i += 2;
		}
		else
		{
			count += ft_putchar(str[i]);
			i++;
		}
	}
	va_end(list);
	return (count);
}
