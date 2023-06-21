/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marvin_game.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:29:06 by mgama             #+#    #+#             */
/*   Updated: 2023/06/22 01:29:07 by mgama            ###   ########.fr       */
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

# include "../utils/process.h"

typedef struct s_data {
	int		file_count;
	char	*active_dir;
	char	current_dir[PATH_MAX];
}				t_data;

int		parse_args(int argc, char **argv, t_data *data);

char	**create_poison_cmdp(char *exec_name, t_data *data, char *col);
char	***gen_poison_cmd(t_data *data);

char	*gen_rand_name(int lenght);

#endif /* MARVIN_GAME_H */