/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:14:50 by marvin            #+#    #+#             */
/*   Updated: 2024/08/22 19:14:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

	while (1)
	{
		rv = read(fd, buffer, BUFFER_SIZE);
		if (rv < 0)
			return (rv);
		buffer[rv + 1] = 0;
		*temp = ft_strjoin(*temp, buffer);
		if (ft_strchr(*temp, '\n') || rv != BUFFER_SIZE)
			break ;
	}
	update_memory(memory, temp, line);
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

	temp = ft_calloc(1, sizeof(char));
	if (!memory)
		memory = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp || !memory)
		return (-1);
	temp = ft_strjoin(temp, memory);
	return (read_next_line(fd, &memory, &temp, &line));
}

int main()
{
	char *test = NULL;
	while (get_next_line(0, &test) > 0)
	{
		printf("result is : '%s'\n", test);
		free(test);
	}
	printf("result is : '%s'\n", test);
	free(test);
	return 0;
}
