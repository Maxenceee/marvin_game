#include "../includes/marvin_game.h"

char	*gen_rand_name(int lenght)
{
	int		j;
	char	*res;
	char randomletter[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789____";

	j = 0;
	res = malloc(sizeof(char) * lenght + 1 + 3);
	while (j < lenght)
		res[j++] = randomletter[rand() % 50];
	res[j++] = '.';
	res[j++] = 'm';
	res[j++] = 'g';
	res[j] = '\0';
	return (res);
}
