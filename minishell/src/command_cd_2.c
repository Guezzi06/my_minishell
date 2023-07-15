/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 00:13:04 by aguezzi           #+#    #+#             */
/*   Updated: 2023/07/04 23:12:00 by aguezzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cd(t_str *str, t_env *my_env)
{
	t_env	*tmp;
	
	str->home = NULL;
	str->pwd = command_pwd(my_env, 0);
	str->oldpwd = NULL;
	str->tmp_pwd = NULL;
	tmp = my_env;
	while (tmp)
	{
		if (ft_strncmp("OLDPWD", tmp->var, 6) == 0)
		{
			str->oldpwd = tmp->var;
			break;
		}
		tmp = tmp->next;
	}
}

void    cd_home(t_str *str, t_env *my_env)
{
	t_env	*tmp;

	tmp = my_env;
    while (tmp)
    {
        if (ft_strncmp("HOME=", tmp->var, 5) == 0)
            str->home = tmp->var + 5;
        tmp = tmp->next;
    }
    if (!str->home)
        printf("myShell: cd: HOME not set\n");
    else
    {
        if (chdir(str->home) == -1)
            printf("myShell: cd: %s: No such file or directory\n", str->split_line[1]);
        else
		{
			str->tmp_pwd = malloc(sizeof(char) * (ft_strlen(str->pwd) + 1));
			ft_strlcpy(str->tmp_pwd, str->pwd, ft_strlen(str->pwd) + 1);
			update_oldpwd(str, my_env);
			free(str->tmp_pwd);
			ft_strlcpy(str->pwd, str->home, ft_strlen(str->home) + 1);
		}
    }
}

void	handle_double_slash(t_str *str)
{
	if (ft_strncmp(str->split_line[1], "//", 2) == 0)
	{
		if (str->split_line[1][2] != '/')
		{
			str->tmp = ft_strjoin("/", str->pwd);
			ft_strlcpy(str->pwd, str->tmp, ft_strlen(str->tmp) + 1);
		}
	}
}

void	search_cd_path(t_str *str)
{
	struct	stat fileStat;
	
	str->tmp = ft_strjoin(str->pwd, "/");
	str->tmp = ft_strjoin(str->tmp, str->split_line[1]);
	if (access(str->tmp, 0) == 0)  // chemin relatif
	{
		if (stat(str->tmp, &fileStat) == 0)
		{
			if (S_ISDIR(fileStat.st_mode))
				ft_strlcpy(str->pwd, str->tmp, ft_strlen(str->tmp) + 1);
			else
				printf("myShell: cd: %s: Not a directory\n", str->split_line[1]);
		}
	}
	else if (access(str->split_line[1], 0) == 0)  // chemin absolu
	{
		if (str->split_line[1][ft_strlen(str->split_line[1]) - 1] == '/')
			ft_strlcpy(str->pwd, str->split_line[1], ft_strlen(str->split_line[1]));
		else
			ft_strlcpy(str->pwd, str->split_line[1], ft_strlen(str->split_line[1]) + 1);
	}
	else
		printf("myShell: cd: %s: No such file or directory\n", str->split_line[1]);
	free(str->tmp);
	cd_slash(str);
}

void	cd_slash(t_str *str)
{
	int		i;
	char	**split_slash;
	char	*build_pwd;
	char	*cat;

	i = 1;
	split_slash = ft_split(str->pwd, '/');
	build_pwd = ft_strjoin("/", split_slash[0]);
	while (split_slash[i])
	{
		cat = ft_strjoin("/", split_slash[i]);
		build_pwd = ft_strjoin(build_pwd, cat);
		i++;
	}
	ft_strlcpy(str->pwd, build_pwd, ft_strlen(build_pwd) + 1);
}