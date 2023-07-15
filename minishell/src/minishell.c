/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:31:32 by fabperei          #+#    #+#             */
/*   Updated: 2023/06/27 15:46:16 by aguezzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_str	*str;
	t_env	*my_env;

	str = (t_str *)malloc(sizeof(t_str));
	my_env = (t_env *)malloc(sizeof(t_env));
	build_env(my_env, env);
	while (1 && argc == 1 && argv[0][0] == '.')
	{
		str->line = readline("\e[0;30m➢\e[0m\e[0;34mmyShell\e[0m\e[0;33m$ \e[0m");
		if (ft_strlen(str->line) == 0)
			continue;
		if (ft_strcmp(str->line, "exit") == 0)
		{
			printf("exit\n");
			exit (0);
		}
		if (str->line)
		{
			printf("%sinput : %s%s\n", YEL, str->line, RESET);
			parsing_start(str);
			print_list(str);
			execute_line(str, my_env);
		}
	}
	free(str);
	//add_history(str.line);
	return (0);
}

void	build_env(t_env *my_env, char **env)
{
	t_env	*tmp;
	int	i;

	tmp = my_env;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp("OLDPWD", env[i], 6) != 0)
			tmp->var = ft_strdup(env[i]);
		else
			tmp->var = ft_strdup("OLDPWD");
		if (env[i + 1])
			tmp->next = malloc(sizeof(t_env));
		else
			tmp->next = NULL;
		if (ft_strchr(tmp->var, '='))
			tmp->visible = 1;
		else
			tmp->visible = 0;
		tmp = tmp->next;
		i++;
	}
	my_env->nb_var = i;
}

void	sort_export(char **var, int nb)
{
	int		i;
	int		j;
	char	*save;

	i = 0;
	while (i < nb - 1)
	{
		j = 0;
		while (var[j + 1])
		{
			if (ft_strcmp(var[j], var[j + 1]) > 0)
			{
				save = var[j];
				var[j] = var[j + 1];
				var[j + 1] = save;
			}
			j++;
		}
		i++;
	}
}

void	execute_line(t_str *str, t_env *my_env)
{
	t_str	*tmp;

	tmp = str;
	while (tmp)
	{
		if (tmp->type == COMMAND)
		{
			execute_command(str, my_env, tmp->word);
		}
		tmp = tmp->next;
	}
}

void	execute_command(t_str *str, t_env *my_env, char *word)
{
	if (ft_strcmp(word, "echo") == 0)
		ft_echo(str->line);
	else if (ft_strcmp(word, "pwd") == 0)
		command_pwd(my_env, 1);
	else if (ft_strcmp(word, "env") == 0)
		command_env(my_env);
	else if (ft_strcmp(word, "cd") == 0)
		command_cd(str, my_env);
	else if (ft_strcmp(word, "export") == 0)
		command_export(str, my_env);
}

void	ft_quit(char *s)
{
	ft_printf("%s\n", s);
	exit (0);
}