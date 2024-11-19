/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:45:46 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/19 10:18:20 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	del(char **content)
{
	if (*content)
	{
		free(*content);
		*content = NULL;
	}
}

char	*format_output(char *res, char **mem, int rv)
{
	int		i;
	char	*line;

	if (ft_strchr(res, '\n'))
		*mem = ft_strdup(ft_strchr(res, '\n') + 1);
	if (ft_strchr(res, '\n') && !*mem)
		return (del(&res), del(mem), NULL);
	i = 0;
	while (res[i] && res[i] != '\n')
		i++;
	if (!res[i])
		i--;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (del(&res), del(mem), NULL);
	while (i >= 0)
	{
		line[i] = res[i];
		i--;
	}
	if (*res == 0 && rv == 0)
		return (del(&res), del(&line), del(mem), NULL);
	return (del(&res), line);
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
		if (!temp)
			return (del(res), del(buffer), -1);
		del(res);
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
	if (!mem[fd] || !buffer || !res || read(fd, buffer, 0) < 0
		|| BUFFER_SIZE <= 0)
		return (del(&res), del(&buffer), del(&mem[fd]), NULL);
	temp = ft_strjoin(mem[fd], res);
	if (!temp)
		return (del(&res), del(&buffer), del(&mem[fd]), NULL);
	del(&res);
	del(&mem[fd]);
	res = temp;
	rv = read_next_line(fd, &res, &buffer);
	if (rv == -1)
		return (del(&res), del(&buffer), NULL);
	return (del(&buffer), format_output(res, &mem[fd], rv));
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