#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/errno.h>

#include "poison_utils.c"
#include "healer_utils.c"

#define PATH_MAX 4096
#define FORK_ERROR "Fork"
#define NO_COMMAND "Command not found"
#define PERM_DENIED "permission denied"

void	exit_error_with_msg(char *msg)
{
	perror(msg);
	exit(1);
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

void	process_child(char **command, char **envp)
{
	pid_t	pid;
	int		res;

	pid = fork();
	if (pid == -1)
		exit_error_with_msg(FORK_ERROR);
	if (pid == 0)
	{
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

    fPtr  = fopen(path, "r");
    fTemp = fopen("replace.tmp", "w"); 
    if (fPtr == NULL || fTemp == NULL)
    {
        printf("\nUnable to open file.\n");
		return (1);
    }
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        if (strncmp(buffer, "curl parrot.live", 17) == 0)
		{
			printf("replacing line %s", buffer);
            fputs(newline, fTemp);
		}
        else
            fputs(buffer, fTemp);
    }
    fclose(fPtr);
    fclose(fTemp);
    remove(path);
    rename("replace.tmp", path);
    printf("\nSuccessfully replaced line\n");
    return (0);
}

int	clear_file(int fd, char *path)
{
	char	*line;
	int		i;

	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (strncmp(line, "curl parrot.live", 16) == 0)
		{
			printf("here line %d\n", i);
			// replace_line(path, i);
		}
		free(line);
		i++;
	}
	return (0);
}


int	main(int ac, char **av, char **envp)
{
	char		home_buffer[PATH_MAX];
	char		current_file_buffer[PATH_MAX];
	int			fd;
	int			i;
	static char	*file_list[] = {"/.zshrc", "/.bashrc", NULL};
	char		*path;
	// char	*rm_cmd[] = {"find", "Desktop/*", "-type", "f", "-name", "*.mg", NULL};

	i = 0;
	realpath(getenv("HOME"), home_buffer);
	realpath(av[0], current_file_buffer);
	printf("home path %s\n", home_buffer);
	// process_child(rm_cmd, envp);
	while (file_list[i])
	{
		path = ft_strjoin(getenv("HOME"), file_list[i]);
		if (!path)
			return (1);
		printf("opening %s\n", path);
		// fd = open(path, O_RDONLY);
		// printf("on fd %d\n", fd);
		// if (fd < 0)
		// 	return (1);
		if (replace_line(path, "curl parrot.live"))
			return (1);
		close(fd);
		free(path);
		i++;
	}
	remove(current_file_buffer);
	return (0);
}