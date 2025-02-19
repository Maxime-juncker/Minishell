#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <fcntl.h>
# include <stdio.h>

/* -------------------------------------------------------------------------- */
/*                                command table                               */
/* -------------------------------------------------------------------------- */

# define SYNTAX_ERR	2
# define NOT_FOUND	127
# define IS_DIR		126
# define MALLOC_ERR	-1

# define DEBUG 0
# define SHOW_LEXER 0

typedef struct s_command
{
	char	**args;
	size_t	n_args;

	int		fd_in;
	int		fd_out;
}	t_command;

typedef struct s_command_table
{
	t_command	*commands;
	size_t		n_commands;

	char		**env;
	char		**exp;
}	t_command_table;

extern int	g_signal_received;

void	handle_signal(int signal);
void	new_prompt(t_command_table *table);

// pipex.c
char	**get_paths(char **env);

// paths.c
char	*get_cmd_path(char **paths, t_command cmd);
void	setup_redirection(t_command cmd);
int		relative_path(char *path);

// pipeline.c
int		run_pipeline(t_command_table *table);
void	cleanup_table(t_command_table *table);

// executor.c
int		run_command(t_command cmd, const t_command_table *table, int *childs);
int		run_env_cmd(t_command_table *table, t_command cmd);
void	close_fds(t_command cmd);

// redirect.c
void	redir(t_command *cmd, char *cmd_str, int is_last, int i);

// init.c
int		init_table(char *line, t_command_table *table);

// checker_utils.c
int		check_needed(char **cmd, const char c_operator);
void	cleanup_arr(void **arr);
int		in_base(const char c, const char *base);
int		token_error(char c1, char c2);

// checker.c
int		check_cmd_line( const char *process_line, char **env );
t_list	*split_line(char *line);
int		check_path(const char *cmd_part, char **env);

// lexer.c
char	*process_line(const char *cmd_line, char **env, int *code);

// quotes_processing.c
t_list	*process_quotes(const char *line);

// var_processing.c
t_list	*process_expanded_vars(const t_list *lst, char **env, int last_code);

// syntax_checker.c
int		check_syntax(const char *cmd_line);
int		new_line_error(const char *str, const char last);

// path_checker.c
int		check_cmd_path(const char *cmd);
int		check_dir_validity(char **path);
int		check_cmd_validity(char **cmd_part, char **env);

// split_line.c
t_list	*split_line(char *line);

// lexer_utils.c
char	toggle_quote(char c, char quote);
int		is_symbol(char c);

// join_lst.c
char	*join_lst(t_list *lst);

// quote_utils.c
size_t	count_space(const char *str);
size_t	get_str_len(const char *str);

// redir_checker.c
int		check_redir_in(const char *cmd_line, int i);
int		check_redir_out(const char *cmd_line, int i);

// token_error.c
int		check_token_error(const char *cmd_line,
			int i, int max_occ, char to_find);

/* ------------------------------ built-in cmd ------------------------------ */
// echo.c
int		echo(char **args, int n);

// env.c
int		env(t_command_table table);
char	**duplicate_env(char **old_env);
size_t	arrlen(void **arr);

// pwd.c
int		pwd(char **env);

// export.c
int		export_cmd(t_command_table *table, t_command cmd);

// unset.c
int		unset_cmd(t_command_table *table, t_command cmd);
void	handle_cmd(t_command_table *table, char *arg);
int		ft_strcmp(char *s1, char *s2);

// dirs.c
int		cd_command(const t_command_table *table, const t_command cmd);
int		change_directory(const char *path, char **env);

// debug
void	show_cmd(t_command cmd);
void	show_table(t_command_table table);

char	*remove_quotes(const char *line);
char	*remove_quotes_pair(char *s);
char	*find_env_var(char **env, const char *to_find, int *index);
int		is_builtin(char *name);

#endif
