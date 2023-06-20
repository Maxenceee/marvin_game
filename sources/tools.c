#include "../includes/marvin_game.h"

char	***free_double_tab(char ***tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
			free(tab[i][j++]);
		free(tab[i++]);
	}
	free(tab);
	return (NULL);
}

char	**free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
	}
	free(tab);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		str++;
		count++;
	}
	return (count);
}

static int	count_strings(const char *str, char charset)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && charset == str[i])
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && charset != str[i])
			i++;
	}
	return (count);
}

static int	ft_strlen_sep(const char *str, char charset)
{
	int	i;

	i = 0;
	while (str[i] && charset != str[i])
		i++;
	return (i);
}

static char	*ft_word(const char *str, char charset)
{
	int		len_word;
	int		i;
	char	*word;

	i = 0;
	len_word = ft_strlen_sep(str, charset);
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (0);
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(const char *str, char charset)
{
	char	**strings;
	int		i;

	if (str == NULL)
		return (NULL);
	i = 0;
	strings = (char **)malloc(sizeof(char *)
			* (count_strings(str, charset) + 1));
	if (!strings)
		return (0);
	while (*str != '\0')
	{
		while (*str != '\0' && *str == charset)
			str++;
		if (*str != '\0')
		{
			strings[i] = ft_word(str, charset);
			if (strings[i++] == 0)
				return (free_tab(strings));
		}
		while (*str && *str != charset)
			str++;
	}
	strings[i] = 0;
	return (strings);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while ((char)s1[i] == (char)s2[i] \
		&& (char)s1[i] != '\0' && (char)s2[i] != '\0')
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	ft_str_length(char *str)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

static char	*ft_strcpy(char *dest, char *src)
{
	int	index;

	index = 0;
	while (src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

static int	ft_compute_final_length(char **strings, int size, int sep_length)
{
	int	final_length;
	int	index;

	final_length = 0;
	index = 0;
	while (index < size)
	{
		final_length += ft_str_length(strings[index]);
		final_length += sep_length;
		index++;
	}
	final_length -= sep_length;
	return (final_length);
}

char	*ft_strjoin_arr(int size, char **strs, char *sep)
{
	int		full_length;
	int		index;
	char	*string;
	char	*d;

	if (size == 0)
		return ((char *)malloc(sizeof(char)));
	full_length = ft_compute_final_length(strs, size, ft_str_length(sep));
	string = (char *)malloc((full_length + 1) * sizeof(char));
	d = (string);
	if (!d)
		return (0);
	index = -1;
	while (++index < size)
	{
		ft_strcpy(d, strs[index]);
		d += ft_str_length(strs[index]);
		if (index < size - 1)
		{
			ft_strcpy(d, sep);
			d += ft_str_length(sep);
		}
	}
	*d = '\0';
	return (string);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char *)malloc(
			sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[j++] = s2[i];
		i++;
	}
	str[j] = 0;
	return (str);
}

int	max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}