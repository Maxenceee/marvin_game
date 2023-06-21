#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/errno.h>

#include "poison_utils.c"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE INT16_MAX
#endif
#define PATH_MAX 4096
#define FORK_ERROR "Fork"
#define NO_COMMAND "Command not found"
#define PERM_DENIED "permission denied"

void	exit_error_with_msg(char *msg)
{
	perror(msg);
	exit(1);
}

int	dup2_fdinout(int fdin, int fdout)
{
	if (dup2(fdin, STDIN_FILENO) < 0)
		return (3);
	if (dup2(fdout, STDOUT_FILENO) < 0)
		return (3);
	return (0);
}

static char	*get_path(char *envp[])
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
	}
	return (NULL);
}

static char	*parse_env(char *envp[], char *cmd)
{
	char	*path;
	char	**bins;
	char	*joins[3];
	int		i;

	path = get_path(envp);
	if (!path)
		return (NULL);
	bins = ft_split(path, ':');
	if (!bins)
		return (NULL);
	i = -1;
	while (bins[++i])
	{
		joins[0] = bins[i];
		joins[1] = "/";
		joins[2] = cmd;
		path = ft_strjoin_arr(3, joins, "");
		if (access(path, F_OK) == 0)
			return (path);
	}
	free(bins);
	return (NULL);
}

static int	execcmd(char **command, char *envp[])
{
	char		*cmd;

	if (command[0] == NULL)
		return (5);
	cmd = parse_env(envp, command[0]);
	if (!cmd || strcmp(command[0], "") == 0)
		return (2);
	if (execve(cmd, command, envp) == -1)
	{
		perror("Could not execute execve");
		return (1);
	}
	return (0);
}

void	process_child(char **command, char **envp, int fdout)
{
	pid_t	pid;
	int		res;

	pid = fork();
	if (pid == -1)
		exit_error_with_msg(FORK_ERROR);
	if (pid == 0)
	{
		dup2(fdout, STDOUT_FILENO);
		// close(fdc);
		// char buff[BUFFER_SIZE];
		// read(STDIN_FILENO, buff, BUFFER_SIZE);
		// printf("buffer %s\n", buff);
		res = execcmd(command, envp);
		if (res == 5)
			exit_error_with_msg(PERM_DENIED);
		else if (res == 2)
			dprintf(2, "%s : %s\n" , command[0], NO_COMMAND);
		exit(1);
	}
}

int	replace_line(char *path, char *pattern)
{
    FILE	*fPtr;
    FILE	*fTemp;
    char	buffer[BUFFER_SIZE];
    char	newline[] = "";
	int		i;

    fPtr  = fopen(path, "r");
    fTemp = fopen(".replace.tmp", "w"); 
    if (fPtr == NULL || fTemp == NULL)
    {
        printf("Unable to open file %s\n", path);
		return (1);
    }
	i = 0;
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
		i++;
        if (strncmp(buffer, "curl parrot.live", 16) == 0)
		{
			printf("replacing line %d %s", i, buffer);
            fputs(newline, fTemp);
		}
        else
            fputs(buffer, fTemp);
    }
    fclose(fPtr);
    fclose(fTemp);
    remove(path);
    rename(".replace.tmp", path);
    return (0);
}

int	rm_file(char* home_buffer, char **envp)
{
	int		i;
	char	*commands;
	char	**find_cmd;
	char	**rm_file_list;
	int		fds[2];
	char	rm_buffer[BUFFER_SIZE];
	char	*rm_cmd[] = {"xargs", "rm", NULL};

	#if __APPLE__
	commands = ft_strjoin_free2("find ", ft_strjoin(home_buffer,  " -type f ( -name *_mxga -o -name consignes.mxga.txt )"));
	#else
	commands = ft_strjoin_free2("find ", ft_strjoin(home_buffer,  " -type f ( -name *.mxga -o -name consignes.mxga.txt )"));
	#endif
	if (!commands)
		return (1);
	printf("%s\n", commands);
	find_cmd = ft_split(commands, ' ');
	if (!find_cmd)
		return (free(commands), 1);

	printf("\nRemoving all .mxga file...\n");
	pipe(fds);
	process_child(find_cmd, envp, fds[1]);
	close(fds[1]);
	waitpid(-1, NULL, 0);
	i = read(fds[0], rm_buffer, BUFFER_SIZE);
	close(fds[0]);
	rm_buffer[i] = '\0';
	rm_file_list = ft_split(rm_buffer, '\n');
	if (!rm_file_list)
		return (1);
	i = -1;
	while (rm_file_list[++i])
	{
		printf("Removing file %s\n", rm_file_list[i]);
		remove(rm_file_list[i]);
	}
	printf("File removed: %d\n", i);
	printf("--------------------\n");
	free_tab(rm_file_list);
	free_tab(find_cmd);
	free(commands);
	// process_child(rm_cmd, envp, fds[0], STDIN_FILENO, fds[1]);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	// chmod("tttttttt", 0663);
	// return (0);
	char		home_buffer[PATH_MAX];
	char		current_file_buffer[PATH_MAX];
	// int			fd;
	int			i;
	static char	*file_list[] = {"/.zshrc", "/.bashrc", NULL};
	char		*path;
	// char		*find_cmd[] = {"find", "/", "-type", "f", "-name", "*.mxga", NULL};

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
		// fd = open(path, O_RDONLY);
		// printf("on fd %d\n", fd);
		// if (fd < 0)
		// 	return (1);
		if (replace_line(path, "curl parrot.live"))
			return (1);
		// close(fd);
		free(path);
		i++;
	}
	usleep(10);
	if (rm_file(home_buffer, envp))
		return (1);
	remove(current_file_buffer);
	return (0);
}