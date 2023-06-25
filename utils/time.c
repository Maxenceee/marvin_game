/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:38:49 by mgama             #+#    #+#             */
/*   Updated: 2023/06/22 04:50:10 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/marvin_game.h"

unsigned long	ft_abs_time(void)
{
	struct timeval	tv;
	unsigned long	s;
	unsigned long	u;

	if (gettimeofday(&tv, NULL) == -1)
		dprintf(2, "Error: GETTIMEOFDAY(2)\n");
	s = tv.tv_sec * 1000;
	u = tv.tv_usec / 1000;
	return (s + u);
}

unsigned long	ft_current_time(unsigned long begin)
{
	unsigned long	abs_time;

	abs_time = ft_abs_time();
	return (abs_time - begin);
}
