#include "../includes/marvin_game.h"

char	*gen_rand_name(int lenght)
{
	int		j;
	char	*res;
	char randomletter[] = "__ABCDEFGHIJKLMNOPQRSTUVWXYZ__0123456789__abcdefghijklmnopqrstuvwxyz__";

	j = 0;
	res = malloc(sizeof(char) * lenght + 1 + 3);
	while (j < lenght)
		res[j++] = randomletter[rand() % 70];
	res[j++] = '.';
	res[j++] = 'm';
	res[j++] = 'g';
	res[j] = '\0';
	return (res);
}
