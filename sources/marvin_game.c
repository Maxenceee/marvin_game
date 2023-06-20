#include "../includes/marvin_game.h"

int	copy_alias(int file_count, char **envp)
{
	char	***cp_command;
	int		i;

	i = -1;
	cp_command = gend_alias_cmd();
	if (!cp_command)
		return (1);
	while (++i < file_count)
	{
		process_child(cp_command[i], envp);
	}
	waitpid(-1, NULL, 0);
	free_double_tab(cp_command);
	return (0);
}

int	copy_poison(int file_count, char *dir, char **envp)
{
	char	***cp_command;
	int		i;

	i = -1;
	cp_command = gen_poison_cmd(file_count, dir);
	if (!cp_command)
		return (1);
	while (++i < file_count)
	{
		process_child(cp_command[i], envp);
	}
	waitpid(-1, NULL, 0);
	free_double_tab(cp_command);
	return (0);
}

int	setup_game(t_data *data, char **envp)
{
	printf("Start copy...\n");
	if (copy_poison(data->file_count, data->active_dir, envp))
		return (dprintf(2, "Something went wrong :(\n"), 1);
	#ifndef __APPLE__
		if (copy_alias(data->file_count, envp))
			return (1);
	#else
		printf("Avoiding shell rc corruption");
	#endif
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		t;

	srand(time(NULL));
	bzero(&data, sizeof(t_data));
	if (parse_args(argc, argv, &data))
		return (1);
	printf("----------Start Marvin Game----------\n");
	printf("Params:\nFile count = %d\nActive dir = %s\n--------------------\n", data.file_count, data.active_dir);
	t = setup_game(&data, envp);
	free(data.active_dir);
	return (t);
}