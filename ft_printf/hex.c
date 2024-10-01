/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:54:36 by hle-hena          #+#    #+#             */
/*   Updated: 2024/09/30 18:50:07 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//'#' : 1
//'+' : 2
//' ' : 4
//'0' : 8
//'-' : 16
#include "ft_printf.h"

int	print_hex(t_param args, int mode)
{
	if (mode == 1 && args.flags & 1)
	{
		if (args.placeholder == 'X')
			return (ft_putstr_fd("0X", 1));
		return (ft_putstr_fd("0x", 1));
	}
	return (0);
}

int	print_pt(t_param args, unsigned int nb, char *hex)
{
	int	len;
	int	nblen;

	len = 0;
	if (args.precision != 0 || args.flags & ~16)
		return (len);
	nblen = ft_numlen_base(nb, hex);
	if (!(args.flags & 16))
	{
		while (len < args.width - nblen - 2)
			len += ft_putchar_fd(' ', 1);
	}
	len += ft_putstr_fd("0x", 1);
	len += ft_putnbr_base(nb, hex);
	if (args.flags & 16)
	{
		while (len < args.width)
			len += ft_putchar_fd(' ', 1);
	}
	return (len);
}

int	handle_hex2(t_param args, unsigned int nb, char *base)
{
	t_count	count;
	int		nblen;
	int		pad;

	count.len = 0;
	count.i = 0;
	nblen = ft_numlen_base(nb, base);
	pad = ((args.flags & 8) / 8) * '0' + (!(args.flags & 8)) * ' ';
	if (!(args.flags & 8))
	{
		while (count.len < args.width - ((args.precision >= nblen) *
				args.precision + (args.precision < nblen) * nblen))
			count.len += ft_putchar_fd(pad, 1);
	}
	count.len += print_hex(args, 1);
	if (args.flags & 8)
	{
		while (count.len < args.width - ((args.precision >= nblen) *
				args.precision + (args.precision < nblen) * nblen))
			count.len += ft_putchar_fd(pad, 1);
	}
	while(count.i < args.precision - nblen)
		count.i += ft_putchar_fd('0', 1);
	count.len += ft_putnbr_base(nb, base) + count.i;
	return (count.len);
}

int	handle_hex(t_param args, unsigned int nb)
{
	char	*hex;
	t_count	count;

	if (args.flags & 4 || args.flags & 2 || (args.flags & 16 && args.flags & 8))
		return (0);
	hex = ft_tern_str(args.placeholder == 'X', HEX_MAJ, HEX_MIN);
	if (args.placeholder == 'p')
		return (print_pt(args, nb, hex));
	count.j = ft_numlen_base(nb, hex);
	count.len = 0;
	if (args.flags & 16)
	{
		if (args.flags & 1)
			count.len += print_hex(args, 1);
		count.i = 0;
		while (count.i < args.precision - count.j)
			count.i += ft_putchar_fd('0', 1);
		count.len += ft_putnbr_base(nb, hex) + count.i;
		while (count.len < args.width)
			count.len += ft_putchar_fd(' ', 1);
		return (count.len);
	}
	return (handle_hex2(args, nb, hex));
}
