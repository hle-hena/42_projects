/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ternary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:12:45 by hle-hena          #+#    #+#             */
/*   Updated: 2024/09/30 18:14:31 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tern_int(int cnd, int val1, int val2)
{
	if (cnd)
		return (val1);
	return (val2);
}
char	*ft_tern_str(int cnd, char *ret1, char *ret2)
{
	if (cnd)
		return (ret1);
	return (ret2);
}