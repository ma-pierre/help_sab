/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouhsan <saouhsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 04:19:58 by saouhsan          #+#    #+#             */
/*   Updated: 2024/02/28 23:48:06 by saouhsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_table	*init_cmd_list(void)
{
	t_cmd_table	*cmd;

	cmd = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	if (!cmd)
		return (NULL);
	cmd->content = NULL;
	cmd->args = NULL;
	cmd->filename = NULL;
	cmd->nb_args = 0;
	cmd->token = T_NULL;
	cmd->cmd = CMD_NULL;
	cmd->metachar = M_NULL;
	cmd->cmd_path = NULL;
	cmd->fd[0] = -1;
	cmd->fd[1] = -1;
	cmd->prev = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_minishell	*init_struc(void)
{
	t_minishell	*ms;

	ms = (t_minishell *)malloc(sizeof(t_minishell));
	if (!ms)
		return (NULL);
	ms->env_copy = NULL;
	ms->valid_input = NULL;
	ms->flag_pipe = 0;
	ms->flag_redir = 0;
	ms->flag_hd = 0;
	ms->env = (t_env *)malloc(sizeof(t_env));
	if (!ms->env)
		return (NULL);
	ms->env->key = NULL;
	ms->env->value = NULL;
	ms->env->next = NULL;
	ms->cmd_table = init_cmd_list();
	if (!ms->cmd_table)
		return (NULL);
	ms->cmd_nb = 0;
	//hd
	return (ms);
}

//int	main(int argc, char **argv, char **envp)
//{
//	t_minishell	*ms;
//	char		*usr_input;

//	(void)argv;
//	usr_input = NULL;
//	if (argc != 1 || !*envp || !isatty(STDIN_FILENO))
//		return (EXIT_FAILURE);
//	init_signals();
//	ms = init_struc();
//	if(ms == NULL)
//		end_program(ms, ER_STRUC_INIT);
//	duplicate_env(ms, envp);
//	while (1)
//	{
//		usr_input = readline(PROMPT);
//		if(!usr_input)
//			return (EXIT_FAILURE);
//		if(*usr_input)
//			add_history(usr_input);


//		//parsing
		
//		//execute
		

//		//free(usr_input);
//		//free list cmd
//		//free list env
//		//free lexer/parser
//	}
//	return (EXIT_SUCCESS);
//}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*ms;
	char		*usr_input;
	char		**valid_input;

	(void)argv;
	(void)argc;
	usr_input = NULL;
	if (argc != 1 || !*envp/* || !isatty(STDIN_FILENO)*/)
		return (EXIT_FAILURE);
	////init_signals();
	ms = init_struc();
	if(ms == NULL)
		return(1);
	duplicate_env(ms, envp);
	//update_shlvl(ms);

	usr_input = "echo hello";
	valid_input = ft_split(usr_input, ' ');

	ms->cmd_table = create_cmd_node(ms, ms->cmd_table, valid_input);


	//ms->cmd_table = split_list_by_cmd(ms, ms->cmd_table);

	free_array(valid_input);
	end_program(ms, END);
	return (EXIT_SUCCESS);
}