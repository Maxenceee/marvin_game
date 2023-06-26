/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:28:59 by mgama             #+#    #+#             */
/*   Updated: 2023/06/26 22:25:14 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

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
			dprintf(2, "%s : %s\n", command[0], NO_COMMAND);
		exit(1);
	}
}

void	process_child_fdin(char **command, char **envp, int fdin)
{
	pid_t	pid;
	int		res;

	pid = fork();
	if (pid == -1)
		exit_error_with_msg(FORK_ERROR);
	if (pid == 0)
	{
		dup2(fdin, STDIN_FILENO);
		res = execcmd(command, envp);
		if (res == 5)
			exit_error_with_msg(PERM_DENIED);
		else if (res == 2)
			dprintf(2, "%s : %s\n", command[0], NO_COMMAND);
		exit(1);
	}
}

void	process_child_fout(char **command, char **envp, int fdout)
{
	pid_t	pid;
	int		res;

	pid = fork();
	if (pid == -1)
		exit_error_with_msg(FORK_ERROR);
	if (pid == 0)
	{
		dup2(fdout, STDOUT_FILENO);
		res = execcmd(command, envp);
		if (res == 5)
			exit_error_with_msg(PERM_DENIED);
		else if (res == 2)
			dprintf(2, "%s : %s\n", command[0], NO_COMMAND);
		exit(1);
	}
}
