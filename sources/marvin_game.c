#include "../includes/marvin_game.h"

int	copy_alias()
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
	return (0);
}

int	copy_poison(int file_count, char **envp)
{
	char	***cp_command;
	int		i;

	i = -1;
	cp_command = gen_poison_cmd(file_count);
	if (!cp_command)
		return (1);
	while (++i < file_count)
	{
		process_child(cp_command[i], envp);
	}
	waitpid(-1, NULL, 0);
	return (0);
}

int	setup_game(int file_count, char **envp)
{
	DIR		*desktop_dir;
	// char	*cp_command[] = {"cp", "poison", "./tmp", NULL};

	if (!(desktop_dir = opendir(getenv("HOME"))))
		return (dprintf(2, "Could not access to Desktop\n"), 1);
	if (copy_poison(file_count, envp))
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	file_count;

	srand(time(NULL));
	file_count = 2;
	if (argc == 2)
		file_count = atoi(argv[1]);
	file_count = min(file_count, 2);
	return (setup_game(file_count, envp));
}