#include "../includes/marvin_game.h"

char	*gen_rand_name(int lenght)
{
	int		j;
	char	*res;
	char randomletter[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	j = 0;
	res = malloc(sizeof(char) * lenght + 1);
	while (j < lenght)
		res[j++] = randomletter[rand() % 26];
	res[j] = '\0';
	return (res);
}
