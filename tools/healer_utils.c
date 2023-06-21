#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char	*ft_get_line(char *file)
{
	int		i;
	char	*line;

	i = 0;
	if (!file[i])
		return (NULL);
	while (file[i] && file[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (file[i] && file[i] != '\n')
	{
		line[i] = file[i];
		i++;
	}
	if (file[i] == '\n')
	{
		line[i] = file[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*slice_file(char *file)
{
	int		i;
	int		j;
	char	*sliced;

	i = 0;
	j = 0;
	while (file[i] && file[i] != '\n')
		i++;
	if (!file[i])
	{
		free(file);
		return (NULL);
	}
	sliced = (char *)malloc(sizeof(char) * ft_strlen(file) - i + 1);
	if (!sliced)
		return (NULL);
	i++;
	while (file[i])
		sliced[j++] = file[i++];
	sliced[j] = '\0';
	free(file);
	return (sliced);
}

// size_t	ft_strlen(char *str)
// {
// 	int	count;

// 	count = 0;
// 	if (!str)
// 		return (0);
// 	while (str[count] != '\0')
// 		count++;
// 	return (count);
// }

char	*ft_strchr(char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

static char	*ft_strjjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc(
			sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_read_file(int fd, char *file)
{
	char	*buff;
	int		read_bytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(file, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		file = ft_strjjoin(file, buff);
	}
	free(buff);
	return (file);
}

char	*get_next_line(int fd)
{
	static char	*file[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	file[fd] = ft_read_file(fd, file[fd]);
	if (!file[fd])
		return (NULL);
	line = ft_get_line(file[fd]);
	file[fd] = slice_file(file[fd]);
	return (line);
}
