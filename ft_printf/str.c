/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:42:41 by hle-hena          #+#    #+#             */
/*   Updated: 2024/09/30 18:51:02 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_str_precision(t_param args, char *str)
{
	int	len;
	int	strlen;
	int	printlen;

	len = 0;
	printlen = ft_strlen(str);
	if (args.flags & 16)
	{
		while (len < (ft_tern_int(args.precision < printlen, args.precision,
				printlen)))
			len += ft_putchar_fd(*str++, 1);
		while (len < args.width)
			len += ft_putchar_fd(' ', 1);
		return (len);
	}
	while (len < args.width - (ft_tern_int(args.precision < printlen,
			args.precision, printlen)))
		len += ft_putchar_fd(' ', 1);
	strlen = 0;
	while (strlen < (ft_tern_int(args.precision < printlen, args.precision,
			printlen)))
		strlen += ft_putchar_fd(*str++, 1);
	return (strlen + len);
}

int	handle_str(t_param args, va_list ap)
{
	int		len;
	int		slen;
	char	*str;

	len = 0;
	str = va_arg(ap, char *);
	slen = ft_strlen(str);
	while (len < args.width - slen)
		len += ft_putchar_fd(' ', 1);
	len += ft_putstr_fd(str, 1);
	return (len);
}

int	handle_strs(t_param args, va_list ap)
{
	int		len;

	len = 0;
	if (args.precision != 0)
		return (handle_str_precision(args, va_arg(ap, char *)));
	if (args.flags == 16)
	{
		if (args.placeholder == 'c')
			len += ft_putchar_fd(va_arg(ap, int), 1);
		else if (args.placeholder == 's')
			len += ft_putstr_fd(va_arg(ap, char *), 1);
		while (len < args.width)
		{
			len += ft_putchar_fd(' ', 1);
		}
	}
	else if (args.placeholder == 'c')
	{
		while (len < args.width - 1)
			len += ft_putchar_fd(' ', 1);
		len += ft_putchar_fd(va_arg(ap, int), 1);
	}
	else if (args.placeholder == 's')
		len = handle_str(args, ap);
	return (len);
}

int	handle_percent(t_param args)
{
	if (args.precision != 0 || args.width != 0 || args.flags != 0)
		return (0);
	return (ft_putchar_fd('%', 1));
}