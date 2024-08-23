/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:15:32 by marvin            #+#    #+#             */
/*   Updated: 2024/08/22 19:15:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

#include <stdio.h>

char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strchr(const char *str, int c);
char	*ft_trimend(const char *str);
char	*ft_trimstart(const char *str);
void	*ft_calloc(size_t n, size_t size);

#endif