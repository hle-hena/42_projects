/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:48:27 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/04 13:48:28 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	stop_everything(void)
{
	ft_printf("\n\n\nProgram has stopped due to wrong placeholder/flags\n");
	return (0);
}

void	init_args(t_param *args)
{
	args->flags = 0;
	args->width = 0;
	args->precision = -2;
	args->placeholder = 'q';
}

int	parse(t_param *args, char *str)
{
	int		i;
	int		flag_val;

	i = 1;
	while (str[i] && ft_strchr("#+ 0-", str[i]))
	{
		flag_val = (str[i] == '#') * 1 + (str[i] == '+') * 2 + (str[i] == ' '
				) * 4 + (str[i] == '0') * 8 + (str[i] == '-') * 16;
		if (args->flags & flag_val)
			return (i);
		args->flags += flag_val;
		i++;
	}
	(*args).width = ft_atoi(&str[i]);
	i += ft_numlen((*args).width) * ((*args).width != 0);
	if (str[i] == '.')
	{
		i ++;
		(*args).precision = ft_atoi(&str[i]) + (str[i] == '*') * (-1);
		i += ft_numlen((*args).precision) * ((*args).precision != -1)
			- !(str[i] >= '0' && str[i] <= '9');
		i += (str[i] == '*');
	}
	(*args).placeholder = str[i];
	return (i);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	t_param	args;
	int		i;
	int		written;
	int		temp;

	va_start(ap, str);
	init_args(&args);
	i = -1;
	written = 0;
	while (str[++i])
	{
		if (str[i] == '%')
		{
			i += parse(&args, (char *)(&str[i]));
			temp = handle_args(args, ap);
			if (temp == -1)
				return (stop_everything());
			written += temp;
			init_args(&args);
		}
		else
			written += ft_putchar_fd(str[i], 1);
	}
	return (va_end(ap), written);
}

//Should a .* with only one value after give out an output ?
/* args:      [" %-0s ", ""]
printf:    [  ] = 2
ft_printf: [ 


Program has stopped due to wrong placeholder/flags
] = 0 */
/* #include <limits.h>
int main()
{
	ft_printf(" %-9d %-10d %-11d %-12d %-13d %-14d %-15d\n", INT_MAX,
			INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
} */
