/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marvin_game.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:29:06 by mgama             #+#    #+#             */
/*   Updated: 2023/07/05 17:26:56 by mgama            ###   ########.fr       */
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
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/ioctl.h>

# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>

# include <sys/utsname.h>

# include "../utils/process.h"
# include "../utils/time.h"

// # ifndef __APPLE__
// #  include <linux/fs.h>
// // #  include "ext2_fs.h"
// # else
// // #  include <Cocoa/Cocoa.h>
// # endif /* __APPLE__ */

// # define DEF_LANGS(...) const char *LANGS[] = { __VA_ARGS__ };

typedef enum e_lang {
	FR,
	EN
}			t_lang;

typedef struct s_data {
	int		has_logs;
	int		log_fd;
	t_lang	lang;
	char	**lang_list;
	int		file_count;
	char	*active_dir;
	char	current_dir[PATH_MAX];
}				t_data;

/* parsing */
int				parse_args(int argc, char **argv, t_data *data);

/* commands */
char			**create_poison_cmdp(char *exec_name, t_data *data, char *col);
char			***gen_poison_cmd(t_data *data);

/* strings */
char			*gen_rand_name(int lenght);
char			*gen_rand_string(int lenght);

#endif /* MARVIN_GAME_H */