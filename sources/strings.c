/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:20:31 by mgama             #+#    #+#             */
/*   Updated: 2023/06/22 03:38:05 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/marvin_game.h"

char	*gen_rand_name(int lenght)
{
	int		j;
	char	*res;
	char	randomletter[] = "__ABCDEFGHIJKLMNOPQRSTUVWXYZ__0123456789__abcdefghijklmnopqrstuvwxyz__";

	j = 0;
	res = malloc(sizeof(char) * lenght + 1);
	while (j < lenght)
		res[j++] = randomletter[rand() % 70];
	res[j] = '\0';
	#if __APPLE__
	return (ft_strjoin_free1(res, "_mxga"));
	#else
	return (ft_strjoin_free1(res, ".mxga"));
	#endif /* __APPLE__ */
}
