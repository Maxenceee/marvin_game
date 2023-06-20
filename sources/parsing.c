#include "../includes/marvin_game.h"

int	parse_args(int argc, char **argv, t_data *data)
{
	DIR		*desktop_dir;
	char	home_buffer[PATH_MAX];
	char	*active_dir;
	int		i;

	i = argc;
	data->file_count = 2;
	desktop_dir = NULL;
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
	if (!data->active_dir)
	{
		#if __APPLE__
			data->active_dir = strdup("./tmp");
		#else
			data->active_dir = ft_strjoin(realpath(getenv("HOME"), home_buffer), "/Desktop");
		#endif
	}
	if (!data->active_dir || !(desktop_dir = opendir(data->active_dir)))
		return (data->active_dir && (free(data->active_dir), 1), dprintf(2, "Cannot get active dir\n"), 1);
	free(desktop_dir);
	return (0);
}
