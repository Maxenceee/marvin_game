/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:29:02 by mgama             #+#    #+#             */
/*   Updated: 2023/06/26 20:45:26 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	***free_double_tab(char ***tab);
char	**free_tab(char **tab);
char	**ft_split(const char *str, char charset);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strnlcmp(const char *s1, const char *s2, unsigned int n);
char	*ft_strjoin_arr(int size, char **strs, char *sep);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free1(char *s1, char const *s2);
char	*ft_strjoin_free2(char const *s1, char *s2);
size_t	ft_strlen(const char *str);
int		max(int a, int b);
int		min(int a, int b);
int		ft_isdigit(int num);
int		ft_isstrdigit(char *num);
char	*replace(char *a, char p, char r);

#endif /* TOOLS_H */