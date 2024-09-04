/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:15:32 by marvin            #+#    #+#             */
/*   Updated: 2024/09/04 19:04:02 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

#include <stdio.h>

void	freeing(char **pt);
char	*ft_recat(char *s1, char *s2);
void	*ft_calloc(size_t n, size_t size);
int		ft_strchr(const char *str, int c);
char	*ft_strdup_se(const char *src, int s, int e);

#endif