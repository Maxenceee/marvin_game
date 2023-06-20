#include "../includes/marvin_game.h"

char	***reverse_free(int i, char ***ptr)
{
	int	j;

	while (--i >= 0)
	{
		j = 0;
		while (ptr[i][j])
			free(ptr[i][j++]);
		free(ptr[i]);
		printf("%d\n", i);
	}
	free(ptr);
	return (NULL);
}

char	**create_poison_cmdp(char *exec_name, char *dir)
{
	char	r[SPRINTF_MAX];
	char	*u;

	u = gen_rand_name(10);
	if (!u)
		return (NULL);
	sprintf(r, "cp %s %s/%s", exec_name, dir, u);
	printf("%s\n", r);
	free(u);
	return (ft_split(r, ' '));
}

char	***gen_poison_cmd(int file_count, char *dir)
{
	char	***list;
	int		i;
	int		k;

	list = (char ***)calloc(file_count + 1, sizeof(char **));
	if (!list)
		return (NULL);
	i = -1;
	k = rand() % file_count;
	while (++i < file_count)
	{
		// if (i == k)
		// {
		// 	if (!(list[i] = create_poison_cmdp("healer", dir)))
		// 		return (reverse_free(i, list));
		// }
		// else
		// {
		// 	// if (!(list[i] = create_poison_cmdp("poison", dir)))
			
		// }
		list[i] = create_poison_cmdp("poison", dir);
		if (i == 3)
			free(list[i]), list[i] = NULL;
		printf("%p\n", list[i]);
		if (!list[i])
			return (reverse_free(i, list));
	}
	// list[i] = NULL;
	// return (list);
	return (NULL);
}

char	**create_alias_cmdp(char *exec_name, char *shell_rc)
{
	char	r[SPRINTF_MAX];
	// char	*u;

	sprintf(r, "%s >> %s", exec_name, shell_rc);
	printf("%s\n", r);
	return (ft_split(r, ' '));
}

char	***gend_alias_cmd(void)
{
	char	***list;

	list = (char ***)calloc(2 + 1, sizeof(char **));
	if (!list)
		return (NULL);
	list[0] = create_alias_cmdp("print 'curl parrot.live'", ".zshrc");
	list[1] = create_alias_cmdp("print 'curl parrot.live'", ".bashrc");
	return (list);
}