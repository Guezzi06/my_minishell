/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 00:13:28 by aguezzi           #+#    #+#             */
/*   Updated: 2023/07/04 23:08:12 by aguezzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Reste a faire : Verifier si le repertoire ou l'on se dirige est un dossier et non un fichier ou autre
                   Gerer les $ apres le cd
                   Gerer le ~ et ~/xxx en transformant notre ~ en le contenu de $HOME
*/ 

void	command_cd(t_str *str, t_env *my_env)
{
	init_cd(str, my_env);
	if (str->split_line[1] && ft_strcmp(str->split_line[1], "~") != 0)
	{
		if (chdir(str->split_line[1]) == -1 && ft_strcmp(str->split_line[1], "-") != 0)
			printf("myShell: cd: %s: No such file or directory\n", str->split_line[1]);
		else
		{
			if (ft_strcmp(str->split_line[1], "-") == 0)
				cd_1(str, my_env);
			else if (ft_strcmp(str->split_line[1], "..") == 0)
				cd_2(str, my_env);
			else if (ft_strcmp(str->split_line[1], ".") == 0)
				return ;
			else
				cd_3(str, my_env);
			handle_double_slash(str);
		}
	}
	else
		cd_home(str, my_env);
}

void	cd_1(t_str *str, t_env *my_env)
{
	if (ft_strchr(str->oldpwd, '=') == 0)
		printf("myShell: cd: OLDPWD not set\n");
	else
	{
		str->tmp_pwd = malloc(sizeof(char) * (ft_strlen(str->pwd) + 1));
		ft_strlcpy(str->tmp_pwd, str->pwd, ft_strlen(str->pwd) + 1);
		ft_strlcpy(str->pwd, str->oldpwd, ft_strlen(str->oldpwd) + 1);
		update_oldpwd(str, my_env);
		free(str->tmp_pwd);
	}
}

void	cd_2(t_str *str, t_env *my_env)
{
	if (ft_strcmp(str->pwd, "/") != 0 && ft_strcmp(str->pwd, "//") != 0)
	{
		str->tmp_pwd = malloc(sizeof(char) * (ft_strlen(str->pwd) + 1));
		ft_strlcpy(str->tmp_pwd, str->pwd, ft_strlen(str->pwd) + 1);
		update_oldpwd(str, my_env);
		free(str->tmp_pwd);
		str->tmp = ft_strrchr(str->pwd, '/');
		if (str->tmp != str->pwd)
			str->pwd[str->tmp - str->pwd] = '\0';
		else
			str->pwd[1] = '\0';
	}
	else
	{
		str->tmp_pwd = malloc(sizeof(char) * (ft_strlen(str->pwd) + 1));
		ft_strlcpy(str->tmp_pwd, str->pwd, ft_strlen(str->pwd) + 1);
		update_oldpwd(str, my_env);
		free(str->tmp_pwd);
	}
}

// !! Probleme avec double slash en debut de chemin, a revoir
void	cd_3(t_str *str, t_env *my_env)
{
	str->tmp_pwd = malloc(sizeof(char) * (ft_strlen(str->pwd) + 1));
	ft_strlcpy(str->tmp_pwd, str->pwd, ft_strlen(str->pwd) + 1);
	update_oldpwd(str, my_env);
	free(str->tmp_pwd);
	if (str->split_line[1][0] == '/')
	{
		while (str->split_line[1][str->i])
		{
			if (str->split_line[1][str->i] != '/')
				str->count++;
			str->i++;
		}
		if (!str->count)
			ft_strlcpy(str->pwd, "/", 2);
		else
			search_cd_path(str);
	}
	else
		search_cd_path(str);
}

void	update_oldpwd(t_str *str, t_env *my_env)
{
	t_env	*tmp;
	
	tmp = my_env;
	if (str->oldpwd)
	{
		while (tmp)
		{
			if (ft_strncmp("OLDPWD", tmp->var, 6) == 0)
			{
				free(tmp->var);
				tmp->var = ft_strjoin("OLDPWD=", str->tmp_pwd);
				tmp->visible = 1;
			}
			tmp = tmp->next;
		}
	}
}