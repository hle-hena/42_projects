/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:48:04 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/29 13:13:39 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../includes/libft.h"
# include <stdarg.h>

# define HEX_MAJ "0123456789ABCDEF"
# define HEX_MIN "0123456789abcdef"

typedef struct s_param
{
	int		flags;
	int		width;
	int		precision;
	char	placeholder;
}	t_param;

typedef struct s_count
{
	int	i;
	int	j;
	int	k;
	int	len;
	int	temp;
}	t_count;

typedef struct s_nb
{
	unsigned long	nb;
	int				sign;
	int				nblen;
	int				print;
	int				pad;
	char			*base;
}	t_nb;

typedef struct s_str
{
	char	*str;
	char	let;
	int		print;
}	t_str;

int				ft_printf(const char *str, ...);
int				handle_args(t_param args, va_list ap);
int				handle_str(t_param args, va_list ap);
int				handle_percent(void);
char			*ft_tern_str(int cnd, char *ret1, char *ret2);
int				handle_digits(t_param, va_list ap);
int				print_null(t_param args, char *str);
long long int	ft_tern_int(int cnd, long long int val1, long long int val2);

#endif