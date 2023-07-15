/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:45:17 by fabperei          #+#    #+#             */
/*   Updated: 2023/05/31 11:58:10 by aguezzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_list(t_str *str, int how_split)
{
	if (how_split == 1)
		str->split_line = ft_split(str->line, '\"');
	else if (how_split == 2)
		str->split_line = ft_split(str->line, '\'');
	else
		str->split_line = ft_split(str->line, ' ');
	create_list(str);
	word_type(str);
}

void	print_list(t_str *str)
{
	while (str)
	{
		ft_printf("index : %d\nword : %s\ncommand : %s\nback : %p\nnext : %p\n", str->index, str->word, type_to_string(str->type), str->back, str->next);
		str = str->next;
	}
}

void	create_list(t_str *str)
{
	t_str	*temp;
	int		i;

	i = 0;
	temp = str;
	while (str->split_line[i])
	{
		if (i == 0)
		{
			temp->back = NULL;
			temp->next = NULL;
			temp->index = 0;
			temp->word = str->split_line[0];
		}
		if (str->split_line[i + 1])
		{
			init_next_node(str, temp, 0);
			temp = temp->next;
		}
		else
			init_next_node(str, temp, 1);
		i++;
	}
}

void	init_next_node(t_str *str, t_str *temp, int end)
{
	if (!end)
	{
		temp->next = malloc(sizeof(t_str));
		if (!temp->next)
			exit (EXIT_FAILURE);
		temp->next->back = temp;
		temp->next->line = NULL;
		temp->next->index = temp->index + 1;
		temp->next->word = str->split_line[temp->next->index];
		temp->next->next = NULL;
	}
	else
		temp->next = NULL;
}

void	word_type(t_str *str)
{
	t_str	*temp;

	temp = str;
	while (temp != NULL)
	{
		if ((find_command(str->word) >= 1 && temp->index == 0)
			|| (find_command(str->word) >= 1 && temp->back->type == PIPE))
			temp->type = COMMAND;
		else if (strcmp(temp->word, "|") == 0)
			temp->type = PIPE;
		else if (strcmp(temp->word, "-n") == 0)
			temp->type = COMMAND_OPTION;
		else if(str_usd(temp->word) == 1)
			temp->type = STRING_USD;
		else
			temp->type = STRING;
		temp = temp->next;
	}
	return ;
}

void	free_str(t_str *str)
{
	t_str	*temp;

	temp = str;
	while (str)
	{
		temp = str;
		str = str->next;
		free(temp);
	}
}


const char *type_to_string(t_type type) {
    switch(type) {
        case COMMAND: return "COMMAND";
        case STRING: return "STRING";
        case COMMAND_OPTION: return "COMMAND_OPTION";
        case PIPE: return "PIPE";
        case STRING_USD: return "STRING_USD";
        default: return "UNKNOWN_TYPE";
    }
}
