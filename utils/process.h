/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:29:04 by mgama             #+#    #+#             */
/*   Updated: 2023/06/26 22:25:22 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include <stdint.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/errno.h>

# include "tools.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE INT16_MAX
# endif /* BUFFER_SIZE */

# define PATH_MAX 4096
# define SPRINTF_MAX 8192

# define PIPE_ERROR "Pipe error"
# define EXEVE_ERROR "Could not execute execve"
# define OPEN_IN_ERROR "Infile"
# define OPEN_OUT_ERROR "Outfile"
# define FORK_ERROR "Fork"
# define NO_COMMAND "Command not found"
# define PERM_DENIED "permission denied"

void	exit_error_with_msg(char *msg);
int		dup2_fdinout(int fdin, int fdout);
void	process_child(char **command, char **envp);
void	process_child_fdin(char **command, char **envp, int fdin);
void	process_child_fout(char **command, char **envp, int fdout);

#endif /* PROCESS_H */