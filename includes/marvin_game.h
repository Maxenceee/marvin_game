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
// #include "../tools/process.h"

typedef struct s_data {
	int		file_count;
	char	*active_dir;
	char	current_dir[PATH_MAX];
}				t_data;

int		parse_args(int argc, char **argv, t_data *data);

char	**create_poison_cmdp(char *exec_name, t_data *data, char *col);
char	***gen_poison_cmd(t_data *data);
// char	**create_alias_cmdp(char *exec_name, char *shell_rc);
// char	***gend_alias_cmd(void);

char	*gen_rand_name(int lenght);

#endif /* MARVIN_GAME_H */