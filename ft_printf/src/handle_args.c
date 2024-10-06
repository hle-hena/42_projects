/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:50:37 by hle-hena          #+#    #+#             */
/*   Updated: 2024/10/06 16:33:59 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_null(t_param args, char *str)
{
	int	len;
	int	strlen;
	int	shouldprint;

	len = 0;
	strlen = ft_strlen(str);
	shouldprint = (args.placeholder == 's' && (args.precision >= strlen
				|| args.precision == -2)) || args.placeholder == 'p';
	if (args.flags & 16 && shouldprint)
		len += ft_putstr_fd(str, 1);
	while (len < args.width - strlen * (!(args.flags & 16)) * shouldprint)
		len += ft_putchar_fd(' ', 1);
	if (!(args.flags & 16) && shouldprint)
		len += ft_putstr_fd(str, 1);
	return (len);
}

int	check_invalid_args(t_param args)
{
	if (args.precision != -2 && args.flags & 8)
		return (1);
	if (args.flags & 16 && args.flags & 8)
		return (1);
	if (args.flags & 4 && args.flags & 2)
		return (1);
	return (0);
}

int	handle_args(t_param args, va_list ap)
{
	if (args.precision == -1)
		args.precision = va_arg(ap, int);
	if (check_invalid_args(args))
		return (-1);
	if (args.placeholder == '%')
		return (handle_percent(args));
	else if (ft_strchr("cs", args.placeholder))
		return (handle_str(args, ap));
	else if (ft_strchr("uidpxX", args.placeholder))
		return (handle_digits(args, ap));
	return (-1);
}
