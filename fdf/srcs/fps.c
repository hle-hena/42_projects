/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:21:15 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/12 17:44:13 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	get_current_time(void)
{
	t_time	current_time;

	clock_gettime(CLOCK_MONOTONIC, &current_time);
	return (current_time.tv_sec + (current_time.tv_nsec / 1e9f));
}

void	limit_frame_rate(float frame_start_time)
{
	float	frame_end_time;
	float	elapsed_time;
	float	remaining_time;
	t_time	sleep_time;

	frame_end_time = get_current_time();
	elapsed_time = frame_end_time - frame_start_time;
	remaining_time = (1.0 / TARGET_FPS) - elapsed_time;
	if (remaining_time > 0)
	{
		sleep_time.tv_sec = (int)remaining_time;
		sleep_time.tv_nsec = (remaining_time - sleep_time.tv_sec) * 1e9f;
		nanosleep(&sleep_time, NULL);
	}
}

int	calculate_fps(void)
{
	static float	start_time;
	static int		init = 1;
	static int		frame_count = 0;
	float			current_time;

	if (init)
	{
		init = 0;
		start_time = get_current_time();
	}
	current_time = get_current_time();
	frame_count++;
	if (current_time - start_time >= 1)
	{
		ft_putstr_fd("\033[0;36mFPS : ", 1);
		ft_putnbr_fd(frame_count, 1);
		ft_putstr_fd("\n\033[0;0m", 1);
		frame_count = 0;
		start_time = get_current_time();
	}
	if (current_time == start_time)
		return (TARGET_FPS);
	return ((frame_count / (current_time - start_time)) + 0.5);
}
