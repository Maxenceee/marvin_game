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

int	setup_game(int file_count, char **envp)
{
	DIR		*desktop_dir;
	char	home_buffer[PATH_MAX];
	char	*desktop_path;
	// char	*cp_command[] = {"cp", "poison", "./tmp", NULL};

	if (!(desktop_dir = opendir(getenv("HOME"))))
		return (dprintf(2, "Could not access to User\n"), 1);

	desktop_path = ft_strjoin(realpath(getenv("HOME"), home_buffer), "/Desktop");
	if (!desktop_path)
		return (dprintf(2, "Cannot get Desktop paht\n"), 1);
	printf("%s\n", desktop_path);
	#if __APPLE__
		if (copy_poison(file_count, "./tmp", envp))
			return (dprintf(2, "Something went wrong :(\n"), 1);
	#else
		if (copy_poison(file_count, desktop_path, envp))
			return (dprintf(2, "Something went wrong :(\n"), 1);
	#endif
	// if (copy_alias(file_count, envp))
	// 	return (1);
	free(desktop_path);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	file_count;

	srand(time(NULL));
	file_count = 2;
	if (argc == 2)
		file_count = atoi(argv[1]);
	file_count = max(file_count, 2);
	printf("----------Start Marvin Game----------\nParams:\nfiles = %d\n--------------------\n", file_count);
	return (setup_game(file_count, envp));
}