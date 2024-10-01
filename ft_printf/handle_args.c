/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:50:37 by hle-hena          #+#    #+#             */
/*   Updated: 2024/09/29 15:27:54 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_args(t_param args, va_list ap)
{
	if (ft_strchr("cs", args.placeholder))
		return (handle_strs(args, ap));
	else if (args.placeholder == '%')
		return (handle_percent(args));
	else if (args.placeholder == 'p')
		return (handle_hex(args, va_arg(ap, unsigned int)));
	if (args.precision == -1)
		args.precision = va_arg(ap, int);
	if (args.precision != 0 && args.flags & 8)
		return (0);
	if (ft_strchr("iud", args.placeholder))
		return (handle_int(args, ap));
	else if (ft_strchr("xX", args.placeholder))
		return (handle_hex(args, va_arg(ap, unsigned int)));
	return (0);
}
