/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:33:34 by hle-hena          #+#    #+#             */
/*   Updated: 2025/05/07 10:43:37 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_var_name(char *str)
{
	int		i;
	char	*dest;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	dest = ft_calloc(i + 1, sizeof(char));
	if (!dest)
		return (ft_perror(1, ft_strdup("mini: Internal error: malloc."),
			clean_data() + clean_icmds()), NULL);
	ft_strlcpy(dest, str, i + 1);
	return (dest);
}

char	*get_var_body(char *str)
{
	int		i;
	int		len;
	char	*temp;
	char	*dest;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	len = ft_strlen(&str[++i]);
	if (len == 0)
		return (ft_strdup(""));
	temp = ft_calloc(len + 1, sizeof(char));
	if (!temp)
		return (ft_perror(1, ft_strdup("mini: Internal error: malloc."),
			clean_data() + clean_icmds()), NULL);
	ft_strlcpy(temp, str + i, len + 1);
	dest = remove_quote(temp);
	ft_del((void **)&temp);
	return (dest);
}

char	*create_var(char *str)
{
	char	*content;
	char	*name;
	char	*body;

	name = get_var_name(str);
	body = get_var_body(str);
	if (!body)
		return (ft_perror(1, ft_strdup("mini: Internal error: malloc."),
			clean_data() + clean_icmds()), NULL);
	content = ft_strsjoin((char *[]){name, "=", body, NULL});
	ft_del((void **)&name);
	ft_del((void **)&body);
	if (!content)
		return (ft_perror(1, ft_strdup("mini: Internal error: malloc."),
			clean_data() + clean_icmds()), NULL);
	return (content);
}
