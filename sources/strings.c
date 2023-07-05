/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:20:31 by mgama             #+#    #+#             */
/*   Updated: 2023/07/05 17:51:57 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/marvin_game.h"

char	*gen_rand_name(int length)
{
	int		j;
	char	*res;
	char	randomletter[] = "__ABCDEFGHIJKLMNOPQRSTUVWXYZ__0123456789__abcdefghijklmnopqrstuvwxyz__";

	j = 0;
	res = malloc(sizeof(char) * length + 1);
	while (j < length)
		res[j++] = randomletter[rand() % 70];
	res[j] = '\0';
#if __APPLE__
	return (ft_strjoin_free1(res, "_mxga"));
#else
	return (ft_strjoin_free1(res, ".mxga"));
#endif /* __APPLE__ */
}

char	*gen_rand_string(int length)
{
	int		j;
	char	*res;
	char	randomletter[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz";

	j = 0;
	res = malloc(sizeof(char) * length + 1);
	while (j < length)
		res[j++] = randomletter[rand() % 62];
	res[j] = '\0';
	return (res);
}
