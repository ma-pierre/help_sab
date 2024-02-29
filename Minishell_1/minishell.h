/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouhsan <saouhsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 04:20:39 by saouhsan          #+#    #+#             */
/*   Updated: 2024/02/29 00:15:43 by saouhsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE
# define _XOPEN_SOURCE
# define _GNU_SOURCE

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <signal.h>
# include <string.h>
# include <limits.h>
# include <linux/limits.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "ms_error_display.h"

# include <stdbool.h>
# include <termios.h>

# define PROMPT "minishell$ "

/*---------- EXIT STATUS CODE ----------*/
// EXIT_SUCCESS 0
// EXIT_FAILURE 1

/*---------- ERROR CODE ----------*/
# define ER_GENERAL 1
# define ER_INVALID_USE_BI 2
# define ER_CMD_CANNOT_EXEC 126
# define ER_CMD_NOT_FOUND 127
# define ER_CTRL_C 130
/*
128
255*/

# define DELIMITERS " \t"
# define BUFFER_SIZE 1024

typedef enum e_io
{
	IO_INPUT,
	IO_OUTPUT,
	IO_HEREDOC,
}			t_e_io;

typedef enum e_cmd
{
	CMD_CD,
	CMD_ECHO,
	CMD_ENV,
	CMD_EXIT,
	CMD_EXPORT,
	CMD_PWD,
	CMD_UNSET,
	CMD_OTHER,
	CMD_NULL,
}			t_e_cmd;

typedef enum e_token
{
	T_WORD,
	T_REDIRECTION,
	T_CONTROL_OP,
	T_NULL,
}			t_e_token;

typedef enum e_metachar
{
	M_PIPE,
	M_LESS,
	M_GREAT,
	M_DLESS,
	M_DGREAT,
	M_NULL,
}			t_e_metachar;

//typedef enum e_state
//{
//	S_IN_QUOTE,
//	S_IN_DQUOTE,
//	S_GENERAL,
//}			t_e_state;

typedef struct s_cmd_table
{
	char				*content;
	char				**args;
	char				*filename;
	int					nb_args;
	enum e_token		token;
	enum e_cmd			cmd;
	enum e_metachar		metachar;
	char				*cmd_path;
	int					fd[2];
	pid_t				pid;
	struct s_cmd_table	*prev;
	struct s_cmd_table	*next;
}			t_cmd_table;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_data
{
	char	*pwd;
	char	*oldpwd;
	char	*home_path;

}			t_data;

typedef struct	s_hd_data
{
	char		*content;
	struct s_hd_data	*next;
}				t_hd_data;

typedef struct s_minishell
{
	char		**env_copy;
	char		**valid_input;
	int			flag_pipe;
	int			flag_redir;
	int			flag_hd;
	int			exit_status;
	t_env		*env;
	t_cmd_table	*cmd_table;
	int			cmd_nb; //init when fill cmdsplit
	t_hd_data	*hd;
}			t_minishell;

// UTILS
int				ft_strlen(char *str);
int				ft_strchr(char *str, char c);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strdup(char *str);
char			*ft_strjoin(char *s1, char *s2);
char			**ft_split(char const *s, char c);

// GNL
char			*get_next_line(int fd);
char			*fill_line(char **buffer);

// INIT
void			init_signals(void);
t_minishell		*init_struc(void);
t_cmd_table		*init_cmd_list(void);

// ENV
void			duplicate_env(t_minishell *ms, char **envp);
char			*find_env_var(t_env *env, char *target_key);

// INPUT LIST
t_cmd_table	*create_cmd_node(t_minishell *ms, t_cmd_table *cmd, char **input);
void			fill_cmd_list_data(t_minishell *ms, t_cmd_table *cmd, char *input);
t_e_token		assign_token(char *input_slice);
t_e_cmd			assign_cmd(char *input_slice);
t_e_metachar	assign_metachar(t_minishell *ms, char *input_slice);

// CMD TABLE
void			split_list_by_cmd(t_minishell *ms, t_cmd_table *cmd);
char			**create_cmd_args_array(t_cmd_table *cmd);
int				args_tab_size(t_cmd_table *cmd);
void			del_cmd_list_node(t_cmd_table *cmd);


// PARSE
// REDIRECTION
// PIPE
// QUOTE
// SIGNAL HANDLER
// EXECUTION
void			execution(t_minishell *ms);
int				single_cmd(t_minishell *ms);
void			exec_pipe(t_minishell *ms);
void			child_process(t_minishell *ms, t_cmd_table *cmd);
// HEREDOC HANDLER
void			heredoc_handler(t_minishell *ms);
t_hd_data		*init_hd_lst(void);
void				hd_delimitator_lst(t_minishell *ms, t_hd_data *hd);
void			launch_heredoc(t_minishell *ms, t_hd_data *hd_data);







// SYSTEME CALL
void			check_built_in(t_minishell *ms, t_cmd_table *cmd);
void			launch_bash_builtin(t_minishell	*ms, t_cmd_table *cmd);
char			**find_cmd_path(t_env *env, char *key);
char			*grab_value(t_env *env, char *key);
int				check_access(t_minishell *ms, t_cmd_table *cmd, char **path);
// BUILT-IN
void			built_in_cd(t_minishell *ms, t_cmd_table *cmd);
void			built_in_echo(t_minishell *ms, t_cmd_table *cmd);
//void			built_in_env(t_env *env);
// void	built_in_exit();
// void	built_in_export();
void			built_in_pwd(t_minishell *ms);
//void			built_in_unset(t_minishell *ms, t_cmd_table *cmd);
// CD UTILS
char			*get_current_dir_path(t_minishell *ms);
char			*get_absolut_path(char *relative_path, char *cwd);
void			update_env(t_minishell *ms, char *cwd, char *dest_wd);



// ERRORS
void			error_handler(t_minishell *ms, char *cmd_name, char *error_id);

// EXIT & FREE
void			free_array(char **tab);
void			free_env(t_env *env);
void			free_cmd_list(t_cmd_table *cmd);
void			end_program(t_minishell *ms, char *err_description);

#endif
