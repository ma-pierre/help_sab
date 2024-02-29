#include "../minishell.h"

t_e_token	assign_token(char *input_slice)
{
	if (!ft_strcmp(input_slice, "|"))
		return (T_CONTROL_OP);
	if (!ft_strcmp(input_slice, "<") || !ft_strcmp(input_slice, ">")
		|| !ft_strcmp(input_slice, ">|") || !ft_strcmp(input_slice, "<<")
		|| !ft_strcmp(input_slice, ">>"))
		return (T_REDIRECTION);
	else
		return (T_WORD);
	return (T_NULL);
}

t_e_cmd	assign_cmd(char *input)
{
	if (!ft_strcmp(input, "cd") || !ft_strcmp(input, ""))
		return (CMD_CD);
	if (!ft_strcmp(input, "echo") || !ft_strcmp(input, "/usr/bin/echo"))
		return (CMD_ECHO);
	if (!ft_strcmp(input, "env") || !ft_strcmp(input, "/usr/bin/env"))
		return (CMD_ENV);
	if (!ft_strcmp(input, "exit") || !ft_strcmp(input, ""))
		return (CMD_EXIT);
	if (!ft_strcmp(input, "export") || !ft_strcmp(input, ""))
		return (CMD_EXPORT);
	if (!ft_strcmp(input, "pwd") || !ft_strcmp(input, "/usr/bin/pwd"))
		return (CMD_PWD);
	if (!ft_strcmp(input, "unset") || !ft_strcmp(input, ""))
		return (CMD_UNSET);
	else
		return (CMD_OTHER);
	return (CMD_NULL);
}

t_e_metachar	assign_metachar(t_minishell *ms, char *input_slice)
{
	if (!ft_strcmp(input_slice, "|"))
	{
		ms->flag_pipe++;
		return (M_PIPE);
	}
	if (!ft_strcmp(input_slice, "<"))
		return (M_LESS);
	if (!ft_strcmp(input_slice, ">"))
		return (M_GREAT);
	if (!ft_strcmp(input_slice, "<<"))
	{
		ms->flag_hd++;
		return (M_DLESS);
	}
	if (!ft_strcmp(input_slice, ">>"))
		return (M_DGREAT);
	return ( M_NULL);
}

void	fill_cmd_list_data(t_minishell *ms, t_cmd_table *cmd, char *input)
{
	t_cmd_table	*current;

	current = cmd;
	current->content = ft_strdup(input);
	if (!current->content)
		end_program(ms, ER_MALLOC);
	current->token = assign_token(current->content);
	current->cmd = assign_cmd(current->content);
	current->metachar = assign_metachar(ms, current->content);
	return ;
}

t_cmd_table	*create_cmd_node(t_minishell *ms, t_cmd_table *cmd, char **input)
{
	t_cmd_table	*current;
	t_cmd_table	*new;
	int			i;

	current = cmd;
	i = 0;
	while (input[i] != NULL)
	{
		fill_cmd_list_data(ms, current, input[i]);
		new = malloc(sizeof(*new));
		if (new == NULL)
			end_program(ms, ER_MALLOC);
		current->next = new;
		new->content = NULL;
		new->args = NULL;
		new->nb_args = 0;
		new->token = T_NULL;
		new->cmd = CMD_NULL;
		new->metachar = M_NULL;
		new->prev = current;
		new->next = NULL;
		i++;
	}
	return (current);
}
