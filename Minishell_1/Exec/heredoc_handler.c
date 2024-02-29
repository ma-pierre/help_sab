#include "../minishell.h"

/*
redeemedone@redeemedone-VirtualBox:~$ <<hi hm
> hi
hm: command not found
*/

/*
create struct to colect all hd
*/

void	exit_heredoc()
{
}

t_hd_data	*init_hd_lst(void)
{
	t_hd_data	*hd_data;

	hd_data = (t_hd_data *)malloc(sizeof(t_hd_data));
	if (!hd_data)
		return (NULL);
	hd_data->content = NULL;
	hd_data->next = NULL;
	return (hd_data);
}

void	hd_delimitator_lst(t_minishell *ms, t_hd_data *hd)
{
	t_hd_data	*hd_data;
	t_hd_data	*new;
	t_cmd_table	*cmd;
	int			i;

	hd_data = hd;
	cmd = ms->cmd_table;
	i = ms->flag_hd;
	while (cmd)
	{
		if (cmd->metachar == M_DLESS)
		{
			hd_data->content = ft_strdup(cmd->next->content);
			if (!hd_data->content)
				return (NULL);
			if (i > 0)
			{
				new = init_hd_lst;
				if (!new)
					return (NULL);
				hd_data->next = new;
				i--;
			}
		}
		cmd = cmd->next;
	}
	return ;
}

void	hd_print(char *line)
{
	//save 
}

void	launch_heredoc(t_minishell *ms, t_hd_data *hd_data)
{
	t_hd_data	*current;
	pid_t		pid;
	char		*hd_prompt;
	int			i;

	current = hd_data;
	i = 0;
	pid = fork();
	if (pid == -1)
		return ;
	//signaux
	if (pid == 0)
	{
		while (i < ms->flag_hd)
		{
			while (1)
			{
				hd_prompt = readline(">");
				if (!line || !ft_strcmp(line, current->content))
					break;
				hd_print(line);
				//free line
			}
			//free head
			//current = current->next;
			i--;
		}
	}
	return ;
}

void	heredoc_handler(t_minishell *ms)
{
	t_hd_data   *hd_data;

	hd_data = init_hd_lst();
	if (!hd_data)
		end_program(ms,ER_MALLOC);
	hd_delimitator_lst(ms, hd_data);
	launch_heredoc(ms, hd_data);
	return ;
}