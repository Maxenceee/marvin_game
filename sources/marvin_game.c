#include "../includes/marvin_game.h"

int	copy_alias(int file_count, char **envp)
{
	int			i;
	int			fd;
	static char	*command = "curl parrot.live";
	static char	*file_list[] = {"/.zshrc", "/.bashrc", NULL};
	char		*path;

	i = -1;
	while (file_list[++i])
	{
		path = ft_strjoin(getenv("HOME"), file_list[i]);
		if (!path)
			return (1);
		printf("opening %s\n", path);
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND | O_RDONLY);
		if (fd < 0)
			return (1);
		dprintf(fd, "%s\n", command);
		close(fd);
		free(path);
	}
	printf("End\n");
	return (0);
}

int	copy_poison(int file_count, char *dir, char **envp)
{
	char	***cp_command;
	int		i;

	i = -1;
	printf("Start poison and healer rand name generation...\n");
	cp_command = gen_poison_cmd(file_count, dir);
	if (!cp_command)
		return (1);
	printf("Runnning...\n");
	while (++i < file_count)
	{
		process_child(cp_command[i], envp);
	}
	waitpid(-1, NULL, 0);
	free_double_tab(cp_command);
	printf("End\n");
	return (0);
}

int	setup_game(t_data *data, char **envp)
{
	if (copy_poison(data->file_count, data->active_dir, envp))
		return (dprintf(2, "Something went wrong :(\n"), 1);
	#ifndef __APPLE__
		if (copy_alias(data->file_count, envp))
			return (dprintf(2, "Something went wrong :(\n"), 1);
	#else
		printf("Avoiding shell rc corruption :)\n");
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