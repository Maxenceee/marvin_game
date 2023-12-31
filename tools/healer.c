/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   healer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:23:49 by mgama             #+#    #+#             */
/*   Updated: 2023/07/06 11:21:28 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/process.h"

static void	close_and_rm_file(FILE *f1, FILE *f2)
{
	if (f1)
		fclose(f1);
	if (f2)
		fclose(f2);
}

int	replace_line(char *path)
{
	FILE	*fptr;
	FILE	*ftemp;
	int		i;
	char	buffer[BUFFER_SIZE];
	char	newline[] = "";

	chmod(path, 0644);
	fptr = fopen(path, "r");
	ftemp = fopen(".replace.tmp", "w");
	if (fptr == NULL || ftemp == NULL)
		return (dprintf(2, "Unable to open file %s\a\n", path), close_and_rm_file(fptr, ftemp), remove(".replace.tmp"), 1);
	i = 0;
	while ((fgets(buffer, BUFFER_SIZE, fptr)) != NULL)
	{
		i++;
		if (strncmp(buffer, "curl parrot.live", 16) == 0
			|| strncmp(buffer, "curl \"rand-1.maxencegama.dev?nostatic\" -L", 30) == 0
			|| strncmp(buffer, "GMVRA=", 6) == 0)
		{
			printf("replacing line %d %s\a\n", i, buffer);
			fputs(newline, ftemp);
		}
		else
			fputs(buffer, ftemp);
	}
	close_and_rm_file(fptr, ftemp);
	if (remove(path) < 0)
		dprintf(2, "Could not remove file %s", path), perror("");
	rename(".replace.tmp", path);
	return (0);
}

int	rm_file(char *home_buffer, char **envp)
{
	int		i;
	char	*commands;
	char	**find_cmd;
	char	**rm_file_list;
	int		fds[2];
	char	rm_buffer[BUFFER_SIZE];

#if __APPLE__
	commands = ft_strjoin_free2("find ", ft_strjoin(home_buffer, "/Desktop -type f ( -name *_mxga -o -name consignes.mxga.txt )"));
#else
	commands = ft_strjoin_free2("find ", ft_strjoin(home_buffer, " -type f ( -name *.mxga -o -name consignes.mxga.txt )"));
#endif /* __APPLE__ */
	if (!commands)
		return (1);
	printf("%s\n", commands);
	find_cmd = ft_split(commands, ' ');
	free(commands);
	if (!find_cmd)
		return (1);
	printf("\nRemoving all .mxga files...\n");
	if (pipe(fds) < 0)
		return (dprintf(2, "Could not create pipe"), perror(""), free_tab(find_cmd), 1);
	process_child_fout(find_cmd, envp, fds[1]);
	close(fds[1]);
	waitpid(-1, NULL, 0);
	i = read(fds[0], rm_buffer, BUFFER_SIZE);
	close(fds[0]);
	free_tab(find_cmd);
	if (i < 0)
		return (dprintf(2, "Could not read from pipe\n"), 1);
	rm_buffer[i] = '\0';
	rm_file_list = ft_split(rm_buffer, '\n');
	if (!rm_file_list)
		return (1);
	i = -1;
	while (rm_file_list[++i])
	{
		printf("Removing file %s\n", rm_file_list[i]);
		if (remove(rm_file_list[i]) < 0)
			dprintf(2, "Could not remove file %s", rm_file_list[i]), perror("");
	}
	printf("File removed: %d\n", i);
	printf("--------------------\n");
	free_tab(rm_file_list);
	return (0);
}

int	print_progress(int fd, char **envp)
{
	/* could not find the equivalent of zenity for macOS, function called only under Linux */
	char	*cmd[] = {"zenity", "--no-cancel", "--auto-close", "--progress", "--width=600", "--title", "Well done!", "--text", "You found the good one!\nWe are currently cleaning your session, it might take some time to repair everything, don't panic.\n", NULL};

// #ifndef __APPLE__
	process_child_fdin(cmd, envp, fd);
	// waitpid(-1, NULL, 0);
// #endif /* __APPLE__ */
	return (0);
}

int	print_info(char **envp)
{
	/* could not find the equivalent of zenity for macOS, function called only under Linux */
	char	*cmd[] = {"zenity", "--info", "--width=500", "--title", "Little reminder", "--text", "Did you love our little game? Nah, not sure about that.\n\nThis time it was easy and soft, not everyone is nice so next time lock your session 😉\n", NULL};

// #ifndef __APPLE__
	process_child(cmd, envp);
	// waitpid(-1, NULL, 0);
// #endif /* __APPLE__ */
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	/* could not find easily usable MacOS zenity equivalent, on Mac no popup until I find an good alternative */
	int			i;
#ifndef __APPLE__
	int			fd[2];
#endif /* __APPLE__ */
	char		*path;
	char		home_buffer[PATH_MAX];
	char		current_file_buffer[PATH_MAX];
	static char	*file_list[] = {"/.zshrc", "/.bashrc", NULL};

	(void)(ac);
	i = 0;
	realpath(getenv("HOME"), home_buffer);
	realpath(av[0], current_file_buffer);
	printf("home path %s\n", home_buffer);
#ifndef __APPLE__
	if (pipe(fd) < 0)
		return (dprintf(2, "Could not pipe\n"), 1);
	print_progress(fd[0], envp);
#endif /* __APPLE__ */
#ifndef __APPLE__
	usleep(500 * 1000);
	dprintf(fd[1], "%d\n", 20);
#endif /* __APPLE__ */
	while (file_list[i])
	{
		path = ft_strjoin(getenv("HOME"), file_list[i]);
		if (!path)
			return (1);
		printf("\nopening %s\n", path);
		if (replace_line(path))
			return (free(path), 1);
		free(path);
		i++;
	}
#ifndef __APPLE__
	usleep(500 * 1000);
	dprintf(fd[1], "%d\n", 40);
#endif /* __APPLE__ */
	if (rm_file(home_buffer, envp))
		return (1);
#ifndef __APPLE__
	dprintf(fd[1], "%d\n", 100);
	close(fd[0]);
	close(fd[1]);
	print_info(envp);
	waitpid(-1, NULL, 0);
#endif /* __APPLE__ */
	if (ft_strnrcmp(av[0], "healer", 6) != 0)
		if (remove(current_file_buffer) < 0)
			dprintf(2, "Could not remove file %s", current_file_buffer), perror("");
	return (0);
}
