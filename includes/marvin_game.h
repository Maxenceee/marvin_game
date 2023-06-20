#ifndef MARVIN_GAME_H
# define MARVIN_GAME_H

# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
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

char	**create_poison_cmdp(char *exec_name, char *dir);
char	***gen_poison_cmd(int file_count, char *dir);
char	**create_alias_cmdp(char *exec_name, char *shell_rc);
char	***gend_alias_cmd(void);

char	*gen_rand_name(int lenght);

char	***free_double_tab(char ***tab);
char	**free_tab(char **tab);
void	process_child(char **command, char **envp);
char	**ft_split(const char *str, char charset);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin_arr(int size, char **strs, char *sep);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
int		max(int a, int b);


#endif /* MARVIN_GAME_H */