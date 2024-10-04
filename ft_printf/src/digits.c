/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:19:46 by hle-hena          #+#    #+#             */
/*   Updated: 2024/10/04 19:52:41 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_digits(t_param args, t_nb nb)
{
	t_count	c;

	c.len = 0;
	c.temp = 0;
	if (nb.sign)
		c.temp += ft_putchar_fd('-', 1);
	else if (!nb.sign && args.flags & 2)
		c.temp += ft_putchar_fd('+', 1);
	else if (!nb.sign && args.flags & 4)
		c.temp += ft_putchar_fd(' ', 1);
	else if ((args.flags & 1 && args.placeholder == 'x')
		|| args.placeholder == 'p')
		c.temp += ft_putstr_fd("0x", 1);
	else if (args.flags & 1 && args.placeholder == 'X')
		c.temp += ft_putstr_fd("0X", 1);
	while (c.len < args.precision - nb.nblen)
		c.len += ft_putchar_fd('0', 1);
	if ((nb.nb == 0 && args.precision == 0)
		&& ft_strchr("uid", args.placeholder))
		return (c.len + c.temp);
	c.len += ft_putnbr_base(nb.nb, nb.base);
	return (c.len + c.temp);
}

t_nb	create_nb(t_param args, va_list ap)
{
	t_nb	nb;
	long	nb_i;

	nb.sign = 0;
	if (ft_strchr("upxX", args.placeholder))
		nb.nb = va_arg(ap, unsigned long);
	else
	{
		nb_i = va_arg(ap, int);
		nb.sign = nb_i < 0;
		nb.nb = ft_tern_int(nb_i < 0, -nb_i, nb_i);
	}
	nb.pad = ft_tern_int(args.flags & 8, '0', ' ');
	nb.base = "0123456789";
	if (ft_strchr("px", args.placeholder))
		nb.base = HEX_MIN;
	else if (args.placeholder == 'X')
		nb.base = HEX_MAJ;
	nb.nblen = ft_numlen_base(nb.nb, nb.base) + (args.placeholder == 'p') * 2;
	nb.print = ft_tern_int(nb.nblen > args.precision, nb.nblen, args.precision);
	if (ft_strchr("xX", args.placeholder))
		nb.print += (args.flags) & 1 * 2;
	else if (ft_strchr("id", args.placeholder))
		nb.print += nb.sign + (!nb.sign && (args.flags & 2 || args.flags & 4));
	return (nb);
}

int	handle_digits(t_param args, va_list ap)
{
	int		len;
	t_nb	nb;

	if ((args.flags & 1 || (args.placeholder == 'u' && args.flags & 6))
		&& ft_strchr("uid", args.placeholder))
		return (-1);
	if ((args.flags & 6 || (args.placeholder == 'p' && (args.flags & 1
					|| args.precision != -2)))
		&& ft_strchr("pxX", args.placeholder))
		return (-1);
	len = 0;
	nb = create_nb(args, ap);
	if (nb.nb == 0 && args.placeholder == 'p')
		return (print_null(args, "(nil)"));
	if (args.flags & 16)
		len += print_digits(args, nb);
	while (len < args.width - (nb.print * (!(args.flags & 16))))
		len += ft_putchar_fd(nb.pad, 1);
	if (!(args.flags & 16))
		len += print_digits(args, nb);
	return (len);
}
