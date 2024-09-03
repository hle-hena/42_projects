/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:14:50 by marvin            #+#    #+#             */
/*   Updated: 2024/09/03 20:31:18 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	i;
	size_t	len;

	len = -1;
	while (src[++len]);
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest)
		return (0);
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i ++;
	}
	dest[i] = 0;
	return (dest);
}

void	update_memory(char **memory, char **temp, char ***line)
{
	free(*memory);
	**line = ft_trimend(*temp);
	*memory = ft_trimstart(*temp);
	free(*temp);
}

int	read_next_line(int fd, char **memory, char **temp, char ***line)
{
	int		rv;
	char	buffer[BUFFER_SIZE + 1];
	char	*res;

	while (1)
	{
		rv = read(fd, buffer, BUFFER_SIZE);
		if (rv < 0)
			return (rv);
		buffer[rv] = 0;
		res = ft_strjoin(*temp, buffer);
		free(*temp);
		*temp = ft_strdup(res);
		if (ft_strchr(*temp, '\n') || rv != BUFFER_SIZE)
			break ;
	}
	update_memory(memory, temp, line);
	free(res);
	if (rv == 0 && *memory[0] == '\0')
	{
		free(*memory);
		return (0);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*memory;
	char		*temp;
	char		*res;

	temp = ft_calloc(1, sizeof(char));
	if (!memory)
		memory = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp || !memory)
		return (-1);
	res = ft_strjoin(temp, memory);
	free(temp);
	temp = ft_strdup(res);
	free(res);
	return (read_next_line(fd, &memory, &temp, &line));
}

int main()
{
	char *test = NULL;
	while (get_next_line(0, &test) > 0)
	{
		//printf("result is : '%s'\n", test);
		free(test);
	}
	//printf("result is : '%s'\n", test);
	free(test);
	return 0;
}
