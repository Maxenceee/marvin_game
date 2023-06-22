/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:20:14 by mgama             #+#    #+#             */
/*   Updated: 2023/06/22 02:15:51 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/marvin_game.h"

int	parse_args(int argc, char **argv, t_data *data)
{
	int		i;

	i = argc;
	data->file_count = 200;
	while (i-- > 0)
	{
		if (0 == ft_strcmp(argv[i], "-c") && argc - 1 >= i + 1
			&& ft_isstrdigit(argv[i + 1]))
		{
			data->file_count = atoi(argv[i + 1]);
			if (data->file_count < 2 || data->file_count > INT16_MAX)
				printf("File count out of range, file_count will be normalized\n");
		}
		else if (0 == ft_strcmp(argv[i], "-p") && argc - 1 >= i + 1)
		{
			data->active_dir = strdup(argv[i + 1]);
		}
	}
	data->file_count = min(max(data->file_count, 2), INT16_MAX);
	return (0);
}
