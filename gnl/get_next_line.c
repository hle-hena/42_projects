/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:14:50 by marvin            #+#    #+#             */
/*   Updated: 2024/09/04 19:38:40 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_trim(char **res, char **mem, int rv)
{
	int		sep_pos;
	int		str_len;
	char	*temp;

	str_len = -1;
	while ((*res)[++str_len]);
	if (rv == 0 && (*res)[0] == 0 && str_len == 0)
		return (freeing(res), free(*mem));
	sep_pos = ft_strchr(*res, '\n');
	if (sep_pos == -1)
	{
		temp = ft_strdup_se(*res, 0, str_len - 1);
		free(*res);
		*res = temp;
		return (freeing(mem));
	}
	temp = ft_strdup_se(*res, 0, sep_pos - 1);
	free(*mem);
	*mem = ft_strdup_se(*res, sep_pos + 1, str_len -1);
	free(*res);
	*res = temp;
	if (!*res)
		*res = ft_calloc(1, sizeof(char));
}

void	read_next_line(int fd, char **res, char **mem)
{
	int		rv;
	char	buffer[BUFFER_SIZE + 1];

	while (1)
	{
		rv = read(fd, buffer, BUFFER_SIZE);
		buffer[rv] = 0;
		*res = ft_recat(*res, buffer);
		if (ft_strchr(*res, '\n') != -1 || rv != BUFFER_SIZE)
			break ;
	}
	ft_trim(res, mem, rv);
}

char	*get_next_line(int fd)
{
	static char	*mem;
	char		*res;

	if (fd < 0)
		return (NULL);
	res = ft_calloc(1, sizeof(char));
	if (!mem)
		mem = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!res || !mem)
		return (NULL);
	res = ft_recat(res, mem);
	read_next_line(fd, &res, &mem);
	return (res);
}

int main()
{
	char	*test;
	int		i;

	i = 0;
	while (1)
	{
		test = get_next_line(0);
		if (!test)
			break ;
		printf("result of line %d is : '%s'\n", i, test);
		i ++;
		free(test);
	}
	return (0);
}