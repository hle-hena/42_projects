/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:54:01 by hle-hena          #+#    #+#             */
/*   Updated: 2024/10/01 11:47:17 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	change_args(t_param *args, int nb)
{
	if (nb < 0)
		args->width -= 1;
	else if (args->flags & 2 || args->flags & 4)
		args->width -= 1;
}

int	print_signed(t_param args, int nb, int mode)
{
	int len;

	len = 0;
	if (mode == 1)
	{
		if (nb < 0)
			len += ft_putchar_fd('-', 1);
		else if (args.flags & 2)
			len += ft_putchar_fd('+', 1);
		else if (args.flags & 4)
			len += ft_putchar_fd(' ', 1);
		return (len);
	}
	else if (mode == 2)
	{
		if (nb == -2147483648)
		{
			len += ft_putnbr_fd(214748364, 1);
			len += ft_putnbr_fd(8, 1);
			return (len);
		}
		return (ft_putnbr_fd((nb < 0) * -nb + (nb > 0) * nb, 1));
	}
	return (0);
}

int	handle_signed(t_param args, int nb)
{
	t_count	count;
	int		nblen;
	int		pad;

	count.len = 0;
	count.i = 0;
	nblen = ft_numlen(nb);
	pad = ((args.flags & 8) / 8) * '0' + (!(args.flags & 8)) * ' ';
	if (!(args.flags & 8))
	{
		while (count.len < args.width - ((args.precision >= nblen) *
				args.precision + (args.precision < nblen) * nblen))
			count.len += ft_putchar_fd(pad, 1);
	}
	count.len += print_signed(args, nb, 1);
	if (args.flags & 8)
	{
		while (count.len < args.width - ((args.precision >= nblen) *
				args.precision + (args.precision < nblen) * nblen))
			count.len += ft_putchar_fd(pad, 1);
	}
	while(count.i < args.precision - nblen)
		count.i += ft_putchar_fd('0', 1);
	count.len += print_signed(args, nb, 2) + count.i;
	return (count.len);
}

int	handle_unsigned(t_param args, unsigned int nb)
{
	int	len;
	int	nblen;
	int	pad;
	
	len = 0;
	nblen = ft_numlen(nb);
	if ((args.flags & 2) || (args.flags & 4))
		return (len);
	if (args.flags & 16)
	{
		while(len < args.precision - nblen)
			len += ft_putchar_fd('0', 1);
		len += ft_putnbr_base(nb, "0123456789");
		while (len < args.width)
			len += ft_putchar_fd(' ', 1);
		return (len);
	}
	pad = ((args.flags & 8) / 8) * '0' + (!(args.flags & 8)) * ' ';
	while (len < args.width - ((args.precision >= nblen) * args.precision +
			(args.precision < nblen) * nblen))
		len += ft_putchar_fd(pad, 1);
	while(len < args.precision - nblen)
		len += ft_putchar_fd('0', 1);
	len += ft_putnbr_base(nb, "0123456789");
	return (len);
}

int	handle_int(t_param args, va_list ap)
{
	int	len;
	int	nb;

	len = 0;
	if (((args.flags & 8) && (args.flags & 16)) || ((args.flags & 2) &&
			(args.flags & 4)) || ((args.flags & 8) && args.precision != 0))
		return (len);
	if (args.placeholder == 'u')
		return (handle_unsigned(args, va_arg(ap, unsigned int)));
	nb = va_arg(ap, int);
	if (args.flags & 16)
	{
		if (nb < 0)
			len += ft_putchar_fd('-', 1);
		else if (args.flags & 2)
			len += ft_putchar_fd('+', 1);
		else if (args.flags & 4)
			len += ft_putchar_fd(' ', 1);
		change_args(&args, nb);
		return (len + handle_unsigned(args, (nb < 0) * -nb + (nb > 0) * nb));
	}
	return (handle_signed(args, nb));
}
