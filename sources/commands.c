/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:23:12 by mgama             #+#    #+#             */
/*   Updated: 2023/06/22 01:36:22 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/marvin_game.h"

char	***reverse_free(int i, char ***ptr)
{
	int	j;

	while (--i >= 0)
	{
		j = 0;
		while (ptr[i][j])
		{
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
	char		***list;
	char		*u;
	int			i;
	int			k;
	static char	*exec_list[] = {"healer", "poison", NULL};

	list = (char ***)calloc(data->file_count + 1, sizeof(char **));
	if (!list)
		return (NULL);
	i = -1;
	while (exec_list[++i])
	{
		u = ft_strjoin_free2(data->current_dir, ft_strjoin("/", exec_list[i]));
		if (!u)
			return (free(list), NULL);
		if (access(u, F_OK | X_OK | R_OK))
			return (dprintf(2, "Cannot get exec `%s` at %s\n", exec_list[i], u), free(u), free(list), NULL);
		chmod(u, 0111);
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
			if (!(list[i] = create_poison_cmdp(exec_list[1], data, "\033[31m")))
				return (reverse_free(i, list));
	}
	list[i] = NULL;
	i = -1;
	while (exec_list[++i])
	{
		u = ft_strjoin_free2(data->current_dir, ft_strjoin("/", exec_list[i]));
		if (!u)
			return (free_double_tab(list), NULL);
		if (access(u, F_OK))
			return (dprintf(2, "Cannot get exec `%s` at %s\n", exec_list[i], u), free_double_tab(list), NULL);
		chmod(u, 0755);
		free(u);
	}
	return (list);
}
