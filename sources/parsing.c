#include "../includes/marvin_game.h"

int	parse_args(int argc, char **argv, t_data *data)
{
	int		i;

	i = argc;
	data->file_count = 50;
	while (i-- > 0)
	{
		if (0 == ft_strcmp(argv[i], "-c") && argc - 1 >= i + 1
			&& ft_isstrdigit(argv[i + 1]))
		{
			data->file_count = atoi(argv[i + 1]);
		}
		else if (0 == ft_strcmp(argv[i], "-p") && argc - 1 >= i + 1)
		{
			data->active_dir = strdup(argv[i + 1]);
		}
	}
	data->file_count = max(data->file_count, 2);
	return (0);
}
