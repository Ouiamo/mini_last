/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 21:11:54 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/10/12 18:15:03 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

extern int			g_exit_status;

typedef struct s_list
{
	int				fd;
	char			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_shell
{
	char			*full_commnad;
	char			**split_cmd;
	char			*cmd;
	int				pipe_type;
	t_list			*flags;
	t_list			*infiles;
	t_list			*outfiles;
	int				ambiguous;
}					t_shell;

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*env_join;
	struct s_env	*next;
}					t_env;

typedef struct s_outils
{
	int				in;
	int				out;
	int				**fd;
	pid_t			*pid;
	pid_t			id;
	char			*path;
	char			**paths;
	char			*cmd_path;
	char			**envp;
	int				nbr_pipes;
}					t_outils;

typedef struct minishell
{
	t_env			*my_env;
	t_env			*my_exp;
	char			**envp;
	int				nbr_commands;
	char			*_save_last_cmd;
	char			*save_pwd;
	char			*save_oldpwd;
	long int		shlvl;
	int				flag;
	int				save_fd;
	int				ex_flag;
	t_shell			*shell;
}					t_minishell;

typedef enum e_signal_status
{
	POS1,
	POS2,
	POS3,
}					t_signal_status;

// parsing functions:
void				handling_signals(t_signal_status status,
						t_minishell *minishell);
void				read_sig_handler(int sig);
void				sig_here_doc(int signal);
char				**ft_split1(char const *s, char c);
int					white_spaces(char c);
int					arg_size(char *input);
void				read_user_cmd(t_minishell minishell, t_outils *exec);
char				**tokensation(char *input);
int					count_tokens(char *input);
char				**cpy_to_arr(char *input, char **arr, int tokens);
int					syntax_error(char **arr);
char				*cheak_prnt(char **arr);
char				*first_cheak(char **arr);
void				initial_my_shell(t_minishell *minishell, char **arr);
char				*second_cheak(char **arr);
int					no_quotes(char *limiter);
int					nbr_commands(char **arr);
t_shell				ambiguous(t_shell shell, char *name,
						t_minishell *minishell);
int					spaces(char *str);
int					ft_help(char *content, t_shell *shell,
						t_minishell *minishell);
char				quote_type(char *arr);
int					her_util(int *fd);
int					loop_text(char *text, int i, int pos, int *quote);
char				*rest_of_exp(char *text, t_minishell *minishell, int *i,
						int quote);
char				*cheak_expand(char *var, char *expand);
t_list				*add_flags(char *arr, t_shell shell,
						t_minishell *minishell);
void				parsing(t_minishell *minishell, char **arr);
void				creat_my_shell(t_minishell *minishell, char **arr);
char				*remove_quotes(char *arr);
t_shell				add_redir(char ***arr, t_shell shell,
						t_minishell *minishell);
int					my_heredoc(char *limiter, t_minishell *minishell);
t_shell				add_cmd(char ***arr, t_shell shell, t_minishell *minishell);
t_shell				add_arg(t_shell *shell, char *ptr, t_minishell *minishell);
t_shell				add_pipetype(char *arr, t_shell shell);
char				*herdoc_expand(char *text, t_minishell *minishell,
						int index);
int					my_heredoc(char *limiter, t_minishell *minishell);
char				*get_user_text(char *limiter);
void				join_my_shell(t_minishell *minishell, int n);
char				*ft_last(char *text, int i);
char				*expand_spisial_char(char *text, int pos);
char				*ex_pand(char *text, t_minishell *minishell, int *i,
						int quote);
void				*ft_malloc(int size, void *p);
char				*expand_cmd_line(char *var, t_minishell *minishell);
int					end_var(char *exp);
char				*turn_exp(char *var, t_minishell *minishell);
char				*my_join(char *s1, char *s2);
void				save_last_cmd(t_minishell *minishell);
char				*expand_pwd(char *text, char *pwd, int i, int pos);
char				*ft_all(char *text, int i, int j, t_minishell *minishell);
char				*ft_num(char *text, int pos);
char				*expand_fun(char *text, t_minishell *minishell, int i);
char				*expand_evn_var(char *text, t_env *envp, int j, int i);

// libft function
char				*ft_itoa(int n);
int					ft_isalphanum(int c);
char				*ft_strdup(const char *s1);
int					ft_strlen(char *str);
int					ft_strcmp(char *s1, char *s2);
char				**free_memory(char **arr);
int					ft_strchr(const char *s, char c);
void				ft_putstr_fd(char *s, int fd);
char				*ft_other_join(char *s1, char *s2);
char				*ft_strdup2(const char *s1);
char				*ft_strjoin(char *s1, char *s2);
int					ft_strncmp(char *s1, char *s2, int n);
t_env				*ft_lstnew(char *key, char *value);
void				ft_lstadd_back(t_env **lst, t_env *new);
void				ft_strncpy(char **dst, const char *src, size_t size);
long double			ft_atoi(const char *str);
int					ft_isdigit(char c);
char				**ft_split(char const *s, char c);
void				ft_lstdelone(t_env *lst);
char				**ft_new(char *cmd, t_list *args);
int					ft_lstsize(t_list *lst);
int					ft_lstsize1(t_env *lst);
char				*ft_substr(char *s, unsigned int start, size_t len);
void				ft_free1(char **p);
int					ft_strncmp2(char *s1, char *s2, int n);

// execution function

// builltings
int					ft_cd(t_minishell *minishell, char **cmd);
int					ft_echo(char **cmd);
int					ft_env(t_minishell *minishell, char **cmd, t_outils *exec);
void				env_join(t_env *my_env);
void				envp(t_env *my_env, t_outils *exec);
int					ft_export(t_minishell *minishell, char **cmd,
						t_outils *exec);
void				ft_getenv(char **env, t_minishell *minishell,
						t_outils *exec);
int					ft_pwd(char **cmd, t_minishell *minishell);
void				ft_exit(char **cmd, t_minishell *minishell);
int					ft_unset(t_minishell *minishell, char **cmd);

void				print_sorted_exp(t_minishell *minishell);
void				my_export(t_minishell *minishell);
int					check_key(t_env *my_env, char *key);
int					exist_value(t_minishell *minishell, char *key, char *value);
void				env_from_exp(t_minishell *minishell, t_outils *exec);
int					check_valid_identifier(char c);
int					check_arg(char *str);
int					export_error(char *c, int n);
void				sheck_warning_shlvl(char *key, char *value);

// execution

char				*search_key(t_env *my_env, char *key);
int					msg_error(int n, char *str, t_outils *exec);
int					execution(t_minishell *minishell, t_outils *exec);
int					execute(t_minishell *minishell, int i, t_outils *exec);
void				dup_file(t_minishell *minishell, int i, t_outils *t);
int					builtins(t_minishell *minishell, int i, t_outils *exec);
void				check_special_case(char **cmd, t_outils *exec);
void				check_cmd(t_minishell *minishell, int i, t_outils *exec);
char				*ckeck_path_cmd(char *cmd, char **paths);
char				*search_paths(char *path, t_minishell *minishell);
void				dup_infile(t_minishell *minishell, int i);
void				dup_outfile(t_minishell *minishell, int i);
void				dup_multi_cmd_outfile(t_outils *t, int i,
						t_minishell *minishell);
int					ft_pipe(t_minishell *minishell, t_outils *t);
int					ft_fork(t_outils *t, t_minishell *minishell, int *status);
void				ft_close(t_outils *t);
void				ft_wait(t_outils *t, int n_cmd, int *status,
						t_minishell *minishell);
void				close_fd(t_list *file);
void				save_in_out(t_outils *t, int n);
void				restore_in_out(t_outils *t);
int					error(char *error, int i);
int					error_p(char *str);
void				ft_error1(char *str, t_shell *shell,
						t_minishell *minishell);
void				free_spicial_ptr(t_list *my_collector, void *p);
void				ft_error(char *str);
void				free_int(t_outils *t);
void				free_all(t_outils *exec);
void				free_malloc(void);
void				free_my_collector(t_list *my_collector);
void				*add_to_my_collector(t_list *my_collector, int size);
void				*ft_malloc2(int size, void *p);
int					ft_free(int **p, int pose);
void				close_all(t_minishell *minishell);
void				close_all1(t_minishell *minishell);

#endif
