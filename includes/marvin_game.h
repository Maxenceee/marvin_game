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

# define PATH_MAX 4096
# define SPRINTF_MAX 4096

# define PIPE_ERROR "Pipe error"
# define EXEVE_ERROR "Could not execute execve"
# define OPEN_IN_ERROR "Infile"
# define OPEN_OUT_ERROR "Outfile"
# define FORK_ERROR "Fork"
# define NO_COMMAND "Command not found"
# define PERM_DENIED "permission denied"

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

char	***free_double_tab(char ***tab);
char	**free_tab(char **tab);
void	process_child(char **command, char **envp);
char	**ft_split(const char *str, char charset);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin_arr(int size, char **strs, char *sep);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free1(char *s1, char const *s2);
char	*ft_strjoin_free2(char const *s1, char *s2);
size_t	ft_strlen(const char *str);
int		max(int a, int b);
int		ft_isdigit(int num);
int		ft_isstrdigit(char *num);
char	*replace(char *a, char p, char r);


#endif /* MARVIN_GAME_H */