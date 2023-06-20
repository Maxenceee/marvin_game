#include "../includes/marvin_game.h"

char	**create_poison_cmdp(char *exec_name)
{
	char	*r;
	char	*u;

	sprintf(r, "cp %s ./tmp/%s", exec_name, gen_rand_name(10));
	printf("%s\n", r);
	return (ft_split(r, ' '));
}

char	***gen_poison_cmd(int file_count)
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
		if (i == k)
			list[i] = create_poison_cmdp("healer");
		else
			list[i] = create_poison_cmdp("poison");
	}
	list[i] = NULL;
	return (list);
}

char	**create_alias_cmdp(char *exec_name, char *shell_rc)
{
	char	*r;
	char	*u;

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