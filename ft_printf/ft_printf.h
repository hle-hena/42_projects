/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:44:50 by hle-hena          #+#    #+#             */
/*   Updated: 2024/09/30 18:15:25 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "includes/libft.h"
# include <stdarg.h>
# include <stdio.h>

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
}	t_count;

int	ft_numlen(int num);
int	ft_printf(const char *str, ...);
int	handle_args(t_param args, va_list ap);
int	handle_strs(t_param args, va_list ap);
int	handle_percent(t_param args);
int	handle_int(t_param args, va_list ap);
int	handle_hex(t_param args, unsigned int nb);
int	ft_tern_int(int cnd, int val1, int val2);
char	*ft_tern_str(int cnd, char *ret1, char *ret2);

#endif