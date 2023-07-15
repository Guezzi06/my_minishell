/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:20:24 by fabperei          #+#    #+#             */
/*   Updated: 2023/05/25 15:53:01 by aguezzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
je cherche a donner des id au different input
le but est de savoir si l'input est :
1/ une commande 2/ une instruction de commande  3/ une string
*/

void	parsing_start(t_str *str)
{
	//if(ft_strchrint(str->word, ' ') == 1)
		//return ;
	if (first_quota(str->line) == 0)
		parsing_list(str, 0);
	else if (first_quota(str->line) == 1 && check_db_quota(str->line) == 1)
		parsing_list(str, 1);
	else if (first_quota(str->line) == 2 && check_smp_quota(str->line) == 1)
		parsing_list(str, 2);
	return ;
}

int	check_db_quota(char *line)
{
	int	i;
	int	y;
	int	nb_quota;

	i = 0;
	nb_quota = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			y = i;
			nb_quota++;
			while (line[y] != '\"' && line[y])
				y++;
			if (line[y] == '\"')
				nb_quota++;
		}
		i++;
	}
	if (nb_quota % 2 == 0 && nb_quota != 0)
	{
		printf("%sopen by : [\"]%s\n", GRN, RESET);
		return (1);
	}
	return (0);
}

int	check_smp_quota(char *line)
{
	int	i;
	int	y;
	int	nb_quota;

	i = 0;
	nb_quota = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			y = i;
			nb_quota++;
			while (line[y] != '\'' && line[y])
				y++;
			if (line[y] == '\'')
				nb_quota++;
		}
		i++;
	}
	if (nb_quota % 2 == 0 && nb_quota != 0)
	{
		printf("%sopen by : [\']%s\n", GRN, RESET);
		return (1);
	}
	return (0);
}

int		first_quota(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			return (1);
		else if (line[i] == '\'')
			return (2);
		i++;
	}
	return (0);
}

int		str_usd(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
