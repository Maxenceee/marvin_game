/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:20:14 by mgama             #+#    #+#             */
/*   Updated: 2023/07/06 11:09:21 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/marvin_game.h"

int	parse_args(int argc, char **argv, t_data *data)
{
	int		i;
	char	tmp_path[PATH_MAX];

	i = argc;
	data->file_count = 50;
	data->has_logs = 1;
	data->lang = FR;
	while (i-- > 0)
	{
		if ((0 == ft_strcmp(argv[i], "-c") || 0 == ft_strcmp(argv[i], "--file-count")) && argc - 1 >= i + 1
			&& ft_isstrdigit(argv[i + 1]))
		{
			data->file_count = atoi(argv[i + 1]);
			if (data->file_count < 2 || data->file_count > INT16_MAX)
				printf("❗️File count out of range, file_count will be normalized\n");
		}
		else if ((0 == ft_strcmp(argv[i], "-p") || 0 == ft_strcmp(argv[i], "--dir-path")) && argc - 1 >= i + 1)
		{
			data->active_dir = strdup(realpath(argv[i + 1], NULL));
		}
		else if (0 == ft_strcmp(argv[i], "--lang") || (0 == ft_strcmp(argv[i], "-l") && argc - 1 >= i + 1))
		{
			if (0 == ft_strcmp(argv[i + 1], "fr"))
				data->lang = FR;
			else if (0 == ft_strcmp(argv[i + 1], "en"))
				data->lang = EN;
			else
				printf("❗️Invalid lang, using default `%s`\n", data->lang_list[data->lang]);
		}
		else if (0 == ft_strcmp(argv[i], "--no-log") || 0 == ft_strcmp(argv[i], "-n"))
		{
			data->has_logs = 0;
		}
	}
	data->file_count = min(max(data->file_count, 2), INT16_MAX);
	return (0);
}
