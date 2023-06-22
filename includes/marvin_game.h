/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marvin_game.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:29:06 by mgama             #+#    #+#             */
/*   Updated: 2023/06/22 03:34:57 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MARVIN_GAME_H
# define MARVIN_GAME_H

# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <string.h>
# include <time.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/ioctl.h>

# include "../utils/process.h"

#ifndef __APPLE__
# include <linux/fs.h>
# include "ext2_fs.h"
// # define EXT2_IOC_GETFLAGS		_IOR('f', 1, long)
// # define EXT2_IMMUTABLE_FL		0x00000010 /* Immutable file */
#endif

typedef struct s_data {
	int		file_count;
	char	*active_dir;
	char	current_dir[PATH_MAX];
}				t_data;

/* parsing */
int		parse_args(int argc, char **argv, t_data *data);

/* commands */
char	**create_poison_cmdp(char *exec_name, t_data *data, char *col);
char	***gen_poison_cmd(t_data *data);

/* strings */
char	*gen_rand_name(int lenght);

#endif /* MARVIN_GAME_H */