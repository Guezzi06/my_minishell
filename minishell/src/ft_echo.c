/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:32:00 by fabperei          #+#    #+#             */
/*   Updated: 2023/05/25 11:14:59 by aguezzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *line)
{
	int		i;

	i = 0;

	if (check_smp_quota(line) == 1)
		ft_echo_smp_quota(line);
	if (check_db_quota(line) == 1)
		ft_echo_quota(line);
	else
		ft_echo_simple(line);
	if (check_n(line) == 0)
		printf("\n");
	return ;
}

void	ft_echo_simple(char *line)
{
	char	**split;
	int		i;

	printf("echo simple\n");
	split = ft_split(line, ' ');
	i = 1;
	if (ft_strncmp(split[i], "-n", 2) == 0)
		i++;
	while (split[i])
	{
		if (split[i + 1])
			printf("%s ", split[i]);
		else
			printf("%s", split[i]);
		i++;
	}
	return ;
}

int	check_n(char *line)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(line);
	while (ft_strncmp(&line[i], "echo", 4) != 0)
		i++;
	while (ft_strncmp(&line[i], "-n", 2) != 0 && i < len)
		i++;
	if (i == len)
		return (0);
	return (1);
}

void	ft_echo_quota(char *line)
{
	char	**split;
	int		i;

	i = 0;
	{
		split = ft_split(line, 34);
		i++; // le premier i est la commande
		while (split[i])
		{
			printf("%s", split[i]);
			i++;
		}
	}
	return ;
}

void	ft_echo_smp_quota(char *line)
{
	char	**split;
	int		i;

	i = 0;
	{
		split = ft_split(line, 39);
		i++; // le premier i est la commande
		while (split[i])
		{
			printf("%s", split[i]);
			i++;
		}
	}
	return ;
}
