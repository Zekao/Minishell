/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouquet <mbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:57:06 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/26 11:38:00 by mbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include "libft.h"
# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

// global variable
extern int	g_exit_code;

typedef struct s_var
{
	char	*new;
	int		start;
	int		k;
	int		squote;
	int		dquote;

}		t_variables;

typedef enum e_parse_flag
{
	None,
	Begin,
	RedirectName,
	HereDocEof
}		t_parse_flag;

typedef struct s_word
{
	char			*str;
	struct s_word	*next;
}		t_word;

typedef struct s_redirect
{
	int					src_fd;
	char				*dst_name;
	char				*here_doc_eof;
	int					open_flag;
	int					is_heredoc;
	struct s_redirect	*next;
}		t_redirect;

typedef struct s_command
{
	t_word				*command;
	t_redirect			*redirect;
	struct s_command	*next;
}		t_command;

typedef struct s_parse_param
{
	t_command		*current_command;
	t_redirect		*current_redirect;
	t_parse_flag	flag;
	char			*buf;
	int				quote;
	int				dquote;
	size_t			i;
	char			c;
}		t_parse_param;

typedef struct s_main
{
	char		*ret;
	int			sortie;
	char		**cmd;
	char		pwd[2048];
	char		**my_env;
	char		**export;
	int			save[2];
	int			j;
	int			status;
	int			run;
	t_command	*commandes;
	int			size;
	t_command	*tmp;
}		t_main;

//parsing
t_command	*fct_error_syntaxe(t_command *commandes);
t_command	*ft_parse(char *line);
t_redirect	*ft_make_redirect(t_redirect **l, t_redirect r);
t_command	*ft_make_command(t_command **l, t_command c);
t_command	*ft_free_and_return_null(t_command *ret, t_parse_param *param);
t_word		*ft_make_word(t_word **l, t_word w);
char		**replace_arg(char **cmd, char **env, int exit_code);
char		*my_strtrim(char const *s1, char const set);
int			unclosed_quotes(char *line, int size);
int			unclosed_double_quote(char *line, int size);
int			unclosed_simple_quote(char *line, int size);
void		fill_struct(t_variables *var);
char		**trim_quote(char **cmd);
int			check_cmp(char *s1, char *s2);
int			ft_try_parse(t_command **ret, t_parse_param *param, char *line);
int			ft_try_make_redirect(t_parse_param *param, char *line);
void		ft_free_redirects(t_redirect *l);
int			ft_make_redir(t_parse_param *param, char *line);
int			ft_try_make_command(t_command **ret, t_parse_param *param);
void		ft_free_commands(t_command *l);
int			ft_try_make_word(t_parse_param *param);
int			ft_make_heredoc(t_parse_param *param);
void		ft_free_words(t_word *l);
char		*ft_push_char(char *s, char c);
int			ft_is_oneof(char c, const char *s);
char		**ft_words_to_array(t_word *l);
void		delete_hfile(t_command *cmd);

//utils
int			size_double_ptr(char **arg);
char		**change_ret(char *str, int start, int i, char **ret);
char		**dptr_join(char **dptr1, char **dptr2);
char		**dptr_join_ptr(char **dptr1, char *str);
void		free_dptr(char ***str);
char		**my_split(char *str, char *c);
int			ft_strcmp(const char *s1, const char *s2);
char		*my_strjoin(char *s1, char *s2);
char		*my_getenv(char *var, char **env);
char		**remove_empty(char **cmd);
char		**cut_pipe(char *cmd);
char		**split_spaces(char **cmd);
void		delete_hfile(t_command *cmd);
int			size_commandes(t_command *commandes);
t_command	*syntaxe_error(t_command *commandes);
void		ft_free_commands(t_command *l);
void		free_two_dptr(char ***a, char ***b);

//utils execution
void		free_two_elem(char *s1, char *s2);
void		ft_out(char *str, int i);
char		*ft_free_ret(char **str);
char		*ft_free_ret2(char **str, char *bin);
int			child_process(char **cmd, char **env, char *path_env, int sortie);
int			exec_cmd_2(char **cmd, char *path_env);
int			exec_cmd_3(char **cmd, char *path_env, char *new_cmd);
int			ft_find_line(char **env);
char		*ft_strcat_multiple(char *dest, char *a, char *b, char *c);
int			ft_builtin(char **cmd, char **env, char *pwd, char *path_env);
char		*ft_get_line_p(char **env);
char		*absolute_path(char **cmd, char *path);
char		**path_value(char *path);

//bultins et signaux
void		signal_manager(void);
void		signal_manager2(void);
int			ft_cd(char **cmd, char **env, char *pwd);
int			ft_pwd(char *pwd);
int			ft_env(char **env, char **cmd, int type);
int			exec_cmd(char **cmd, char **env, int sortie);
char		**fill_my_env(char **env);
char		**ft_unset(char **env, char **cmd);
void		export_display_erreur(char *cmd, int nb);
char		**ft_export(char **cmd, char **env, int size);
char		**ascii_sort(char **env);
int			ft_echo(char **cmd, char **env);
char		**ft_redir(t_redirect *redir, char **cmd);
void		ft_pipe(int first, int last, int *sortie);
void		ft_heredoc(t_command *commandes);
int			check_conform(char **cmd, char **env);
char		*what_var(char **env, char *cmd, int *j, char **new_var);
int			index_of_var(char **env, char *var, int place);
char		*change_env(char *cmd, char **env, char *place);
int			create_new_var_dptr(char **cmd, char **env, char ***new_var);
char		*add_var(char *cmd, char **new_var, int j);
char		*export_var(char *cmd, int *j, char **env, char **new_var);
char		*add_dquotes(char *env);

//main utils
t_main		ft_init1(t_main init);
t_main		ft_init_cmd(t_main init);
void		close_stuff(t_main init);
void		do_export(t_main *init);
void		execute_builtin(t_main *init);
void		exec_command(t_main *init);
void		init_output(t_main *init, char **env);
void		manage_loop(t_main *init);
void		exit_assign(char *str, t_main *init);
int			minishell(char **env);
//bonus
char		**ft_wildcard(char **cmd);
char		**wildcard_with_letters(char *cmd, DIR *rep);
void		fill_with_file(struct dirent *file, char ***tri, DIR *rep);
char		*recup_dir(char *cmd);
typedef struct s_varb
{
	char			**tri;
	char			*place;
	char			*prefixe;
	struct dirent	*file;
	char			**tmp;
}		t_varb;
#endif
