/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:45:46 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/13 12:26:37 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*error_output(char *res, char *buffer, char **mem)
{
	if (res)
	{
		free(res);
		res = NULL;
	}
	if (*mem)
	{
		free(*mem);
		*mem = NULL;
	}
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	return (NULL);
}

char	*format_output(char *res, char **mem, int rv)
{
	int		i;
	char	*line;

	free(*mem);
	*mem = NULL;
	if (ft_strchr(res, '\n'))
		*mem = ft_strdup(ft_strchr(res, '\n') + 1);
	i = 0;
	while (res[i] && res[i] != '\n')
		i++;
	if (!res[i])
		i--;
	line = ft_calloc(i + 2, sizeof(char));
	while (i >= 0)
	{
		line[i] = res[i];
		i--;
	}
	if (*res == 0 && rv == 0)
		return (free(res), free(line), NULL);
	return (free(res), line);
}

int	read_next_line(int fd, char **res, char **buffer)
{
	char	*temp;
	int		rv;

	while (1)
	{
		rv = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[rv] = 0;
		temp = ft_strjoin(*res, *buffer);
		free(*res);
		*res = temp;
		if (ft_strchr(*res, '\n') || rv != BUFFER_SIZE)
			break ;
	}
	return (rv);
}

char	*get_next_line(int fd)
{
	static char	*mem[1024];
	char		*res;
	char		*temp;
	int			rv;
	char		*buffer;

	if (fd < 0 || fd > 1024)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	res = ft_calloc(1, sizeof(char));
	if (!mem[fd])
		mem[fd] = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!mem[fd] || !res || read(fd, buffer, 0) < 0 || BUFFER_SIZE <= 0)
		return (error_output(res, buffer, &mem[fd]));
	temp = ft_strjoin(mem[fd], res);
	free(res);
	res = temp;
	rv = read_next_line(fd, &res, &buffer);
	free(buffer);
	return (format_output(res, &mem[fd], rv));
}

/* #include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	char	*test1;
	char	*test2;
	int		fd1;
	int		fd2;

	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	while (1)
	{
		test1 = get_next_line(fd1);
		test2 = get_next_line(fd2);
		if (!test1 && !test2)
			break ;
		if (test1)
		{
			printf("%s", test1);
			free(test1);
		}
		if (test2)
		{
			printf("%s", test2);
			free(test2);
		}
	}
	return (0);
} */