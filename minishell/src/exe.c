/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:31:43 by fabperei          #+#    #+#             */
/*   Updated: 2023/07/04 22:40:48 by aguezzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	find_command(char *word)
{
	if (ft_strcmp(word, "pwd") == 0)
		return (1);
	else if (ft_strcmp(word, "echo") == 0)
		return (2);
	else if (ft_strcmp(word, "env") == 0)
		return (3);
	else if (ft_strcmp(word, "cd") == 0)
		return (4);
	else if (ft_strcmp(word, "unset") == 0)
		return (5);
	else if (ft_strcmp(word, "export") == 0)
		return (6);
	else if (ft_strcmp(word, "exit") == 0)
		return (7);
	else
		return (0);
}

char	*command_pwd(t_env *my_env, int exec)
{
	t_env	*tmp;
	char	*ptr;
	char	pwd[1024];

	tmp = my_env;
	ptr = NULL;
	if (getcwd(pwd, sizeof(pwd)))
	{
		if (exec)
			printf("%s\n", pwd);
	}
	else
		perror("pwd");
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "PWD=", 4) == 0)
		{
			ptr = tmp->var + 4;
			break;
		}
		tmp = tmp->next;
	}
	return (ptr);
}

void	command_env(t_env *my_env)
{
	t_env	*tmp;
	
	tmp = my_env;
	while (tmp)
	{
		if (tmp->visible)
			printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
}

// !!! A faire : Mettre les "" sur les valeurs des var d'env
void	command_export(t_str *str, t_env *my_env)
{
	char	**copy_var;
	int		i;
	
	copy_var = malloc(sizeof(char *) * (my_env->nb_var + 1));
	i = 0;
	while (my_env)
	{
		copy_var[i] = ft_strdup(my_env->var);
		my_env = my_env->next;
		i++;
	}
	copy_var[i] = NULL;
	if (!str->split_line[1]) // si j'ai uniquement la commande export, j'affiche toutes mes var
	{
		sort_export(copy_var, i);
		i = 0;
		while (copy_var[i])
		{
			printf("declare -x %s\n", copy_var[i]);
			i++;
		}
	}
	// free copy_var;
}
