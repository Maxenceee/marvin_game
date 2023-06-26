/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   healer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:23:49 by mgama             #+#    #+#             */
/*   Updated: 2023/06/25 20:16:42 by mgama            ###   ########.fr       */
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

int	replace_line(char *path, char *pattern)
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
		if (strncmp(buffer, "curl parrot.live", 16) == 0 || strncmp(buffer, "GMVRA=", 6) == 0)
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
	char	*rm_cmd[] = {"xargs", "rm", NULL};

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

int	main(int ac, char **av, char **envp)
{
	int			i;
	char		*path;
	char		home_buffer[PATH_MAX];
	char		current_file_buffer[PATH_MAX];
	static char	*file_list[] = {"/.zshrc", "/.bashrc", NULL};

	i = 0;
	realpath(getenv("HOME"), home_buffer);
	realpath(av[0], current_file_buffer);
	printf("home path %s\n", home_buffer);
	while (file_list[i])
	{
		path = ft_strjoin(getenv("HOME"), file_list[i]);
		if (!path)
			return (1);
		printf("\nopening %s\n", path);
		if (replace_line(path, "curl parrot.live"))
			return (free(path), 1);
		free(path);
		i++;
	}
	usleep(10);
	if (rm_file(home_buffer, envp))
		return (1);
	if (remove(current_file_buffer) < 0)
		dprintf(2, "Could not remove file %s", current_file_buffer), perror("");
	return (0);
}
