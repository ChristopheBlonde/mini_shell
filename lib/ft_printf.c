/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 08:35:05 by cblonde           #+#    #+#             */
/*   Updated: 2023/12/11 11:02:42 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_pointer(va_list ptr, size_t *len)
{
	va_list	cpy;

	va_copy(cpy, ptr);
	if (va_arg(cpy, unsigned long int) != 0)
	{
		*len += ft_putlstr("0x");
		*len += ft_putlhex(va_arg(ptr, unsigned long int), "0123456789abcdef");
	}
	else
		*len += ft_putlstr("(nil)");
	va_end(cpy);
}

static void	ft_checkformat(char c, va_list ptr, size_t *len)
{
	if (c == '%')
		*len += ft_putlchar('%');
	else if (c == 'd' || c == 'i')
		*len += ft_putlnbr_base(va_arg(ptr, int), "0123456789");
	else if (c == 'c')
		*len += ft_putlchar(va_arg(ptr, int));
	else if (c == 's')
		*len += ft_putlstr(va_arg(ptr, char *));
	else if (c == 'u')
		*len += ft_putlnbr_base(va_arg(ptr, unsigned int), "0123456789");
	else if (c == 'x')
		*len += ft_putlhex(va_arg(ptr, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		*len += ft_putlhex(va_arg(ptr, unsigned int), "0123456789ABCDEF");
	else if (c == 'p')
		ft_pointer(ptr, len);
	else
	{
		*len += ft_putlchar('%');
		*len += ft_putlchar(c);
	}
}

int	ft_printf(const char *format, ...)
{
	size_t	i;
	size_t	len;
	va_list	ptr;

	i = 0;
	len = 0;
	va_start(ptr, format);
	if (!format)
		return (-1);
	while (i < ft_strlen((char *)format) && format[i])
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '\0')
				return (-1);
			ft_checkformat(format[i + 1], ptr, &len);
			i += 2;
		}
		else
			len += ft_putlchar(format[i++]);
	}
	va_end(ptr);
	return (len);
}
