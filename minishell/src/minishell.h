/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:32:33 by fabperei          #+#    #+#             */
/*   Updated: 2023/07/04 22:01:41 by aguezzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <term.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"

// color

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define RESET "\e[0m"
# define CRESET "\e[0m"
# define COLOR_RESET "\e[0m"

typedef enum	e_type 
{
	COMMAND,
	STRING,
	COMMAND_OPTION,
	PIPE,
	STRING_USD,
}				t_type;

typedef struct	s_str
{
	char			*line;
	char			**split_line;
	char			*word;
	int				index;
	t_type			type;
	char			*home;
	char			*pwd;
	char			*oldpwd;
	char			*tmp_pwd;
	char			*tmp;
	int				i;
	int				count;
	struct s_str	*next;
	struct s_str	*back;
}				t_str;

typedef	struct	s_env
{
	int				nb_var;
	char			*var;
	int 			visible; // si visible viens de env et sinon export
	struct	s_env	*next;
}				t_env;

// parsing input

void	parsing_start(t_str *env);
void	parsing_list(t_str *env, int how_split);
void	word_type(t_str *str);
int		find_command(char *line);
int		check_db_quota(char *line);
int		check_smp_quota(char *line);
int		first_quota(char *line);
int		str_usd(char *word);

void	create_list(t_str *str);
void	print_list(t_str *str);
void	init_next_node(t_str *str, t_str *temp, int end);
void	free_str(t_str *str);
void	ft_quit(char *s);

// execution

void	ft_echo_simple(char *line);
void	ft_echo_smp_quota(char *line);
void	ft_echo(char *line);
int		check_n(char *line);
void	ft_echo_quota(char *line);

void	ft_env(void);
int		check_n(char *line);

void	build_env(t_env *my_env, char **env);
void	execute_line(t_str *str, t_env *my_env);
void	execute_command(t_str *str, t_env *my_env, char *word);

// command_cd
void	command_cd(t_str *str, t_env *my_env);
void	cd_1(t_str *str, t_env *my_env);
void	cd_2(t_str *str, t_env *my_env);
void	cd_3(t_str *str, t_env *my_env);
void	update_oldpwd(t_str *str, t_env *my_env);
void	handle_double_slash(t_str *str);
void    cd_home(t_str *str, t_env *my_env);
void	init_cd(t_str *str, t_env *my_env);
void	search_cd_path(t_str *str);
void	cd_slash(t_str *str);

// commands basic
char	*command_pwd(t_env *my_env, int exec);
void	command_env(t_env *my_env);
void	command_export(t_str *str, t_env *my_env);
void	sort_export(char **var, int nb);
//t_env	*copy_export(t_env *tmp, t_env *tmp_copy);

// fonction interdite juste pour print ma liste
const char *type_to_string(t_type type);

#endif
