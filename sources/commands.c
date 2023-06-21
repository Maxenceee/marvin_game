#include "../includes/marvin_game.h"

char	***reverse_free(int i, char ***ptr)
{
	int	j;

	while (--i >= 0)
	{
		// printf("i = %d\n", i);
		j = 0;
		while (ptr[i][j])
		{
			// printf("\tj = %d\n", j);
			free(ptr[i][j++]);
		}
		free(ptr[i]);
	}
	free(ptr);
	return (NULL);
}

char	**create_poison_cmdp(char *exec_name, t_data *data, char *col)
{
	char	r[SPRINTF_MAX];
	char	*u;

	u = gen_rand_name(15);
	if (!u)
		return (dprintf(2, "Cannot gen rand name\n"), NULL);
	sprintf(r, "cp %s %s/%s", exec_name, data->active_dir, u);
	printf("%s%s%s\n", col, r, "\033[0m");
	free(u);
	return (ft_split(r, ' '));
}

char	***gen_poison_cmd(t_data *data)
{
	char	***list;
	char	*u;
	int		i;
	int		k;
	static char	*exec_list[] = {"healer", "poison", NULL};

	list = (char ***)calloc(data->file_count + 1, sizeof(char **));
	if (!list)
		return (NULL);
	i = -1;
	while (exec_list[++i])
	{
		u = ft_strjoin_free2(data->current_dir, ft_strjoin("/", exec_list[i]));
		if (!u)
			return (NULL);
		// replace(u, ' ', '\ ');
		if (access(u, F_OK | X_OK | R_OK | W_OK))
			return (dprintf(2, "Cannot get exec `%s` at %s\n", exec_list[i], u), NULL);
		chmod(u, 0511);
		free(u);
	}
	i = -1;
	k = rand() % data->file_count;
	while (++i < data->file_count)
	{
		if (i == k)
		{
			if (!(list[i] = create_poison_cmdp(exec_list[0], data, "\033[32m")))
				return (reverse_free(i, list));
		}
		else
			if (!(list[i] = create_poison_cmdp(exec_list[0], data, "\033[31m")))
				return (reverse_free(i, list));
	}
	list[i] = NULL;
	return (list);
}

// char	**create_alias_cmdp(char *exec_name, char *shell_rc)
// {
// 	char	r[SPRINTF_MAX];
// 	// char	*u;

// 	sprintf(r, "%s_>>_%s", exec_name, shell_rc);
// 	printf("%s\n", r);
// 	return (ft_split(r, '_'));
// }

// char	***gend_alias_cmd(void)
// {
// 	char	***list;

// 	list = (char ***)calloc(2 + 1, sizeof(char **));
// 	if (!list)
// 		return (NULL);
// 	list[0] = create_alias_cmdp("print_'curl parrot.live'", "~/.zshrc");
// 	list[1] = create_alias_cmdp("print_'curl parrot.live'", "~/.bashrc");
// 	return (list);
// }