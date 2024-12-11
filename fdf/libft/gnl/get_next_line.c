/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:45:46 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/11 12:04:20 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	del_mem(char **content)
{
	if (*content)
	{
		free(*content);
		*content = NULL;
	}
}

static char	*format_output(char *res, char **mem, int rv)
{
	int		i;
	char	*line;

	if (ft_strchr(res, '\n'))
		*mem = ft_strdup(ft_strchr(res, '\n') + 1);
	if (ft_strchr(res, '\n') && !*mem)
		return (del_mem(&res), del_mem(mem), NULL);
	i = 0;
	while (res[i] && res[i] != '\n')
		i++;
	if (!res[i])
		i--;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (del_mem(&res), del_mem(mem), NULL);
	while (i >= 0)
	{
		line[i] = res[i];
		i--;
	}
	if (*res == 0 && rv == 0)
		return (del_mem(&res), del_mem(&line), del_mem(mem), NULL);
	return (del_mem(&res), line);
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
			return (del_mem(res), del_mem(buffer), -1);
		del_mem(res);
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
		return (del_mem(&res), del_mem(&buffer), del_mem(&mem[fd]), NULL);
	temp = ft_strjoin(mem[fd], res);
	if (!temp)
		return (del_mem(&res), del_mem(&buffer), del_mem(&mem[fd]), NULL);
	del_mem(&res);
	del_mem(&mem[fd]);
	res = temp;
	rv = read_next_line(fd, &res, &buffer);
	if (rv == -1)
		return (del_mem(&res), del_mem(&buffer), NULL);
	return (del_mem(&buffer), format_output(res, &mem[fd], rv));
}
