#include "../minishell.h"

/*
Executor: Creates a new process for every command in
the command table. If necessary, create a pipe (|)
to pass the output of one process as the input of the
next process. It also redirects (>, <, >>) standard
input, standard output, and standard error.

Subshells: You can use the output of one command as
input to a new command using ( ), $( ), |, &.
The shell created when executing a command like this
is called a subshell.

Variables or functions set in the parent process must
be exported before they can be used in the child
process. However, the feature of subshell is that it
can be used without exporting.
EXPORT??

fork & exec are UNIX system calls aka requests for
operating sys sevices, that UNIX programs use to create
new processes.

When UNIX system start up, it starts with only 1 process,
called init.

That init --> multiple processes. Thanks to fork and exec

1 process SPAWNS another eithe   rforming other tasks and 
can also use wait() to keep an eye on the child process

fork() copies the currently running process and creates
another process. Because it is created by copying, all system
resources such as memory are shared with the original process.
Every process (note: init, the top-level process, has pid 1)
is given a process ID when it is created. The fork() function
returns the pid of the child process to the parent and 0 to
the child. Using this, you can give specific commands to child
processes.

When a child process is created using the fork function, the
parent process and child process are executed regardless of
order, and the process that finished executing first is terminated.
At this time, an unstable process such as a zombie process
(zombie procss) occurs. To prevent this, you must perform a
process synchronization function to synchronize the parent
process and child process.

The wait functions is used as a process synchronization
function
After synchronization, the child process terminates after
executing the statement if (pid == 0), and in the case of
the parent process, the child process terminates through wait(),
executes the remaining statements, and then terminates.

*/
int	single_cmd(t_minishell *ms)
{
	t_cmd_table	*cmd;
	int			fd_dup;

	cmd = ms->cmd_table;
	if (cmd->token == T_WORD && !cmd->next)
	{
		fd_dup = dup(STDOUT_FILENO);
		check_built_in(ms, cmd);
		dup2(fd_dup, STDOUT_FILENO);
		close(fd_dup);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	fd_set_up(t_minishell *ms, t_cmd_table *cmd, int cmd_index)
{
	int	fd_copy;

	if (cmd->prev == NULL)
	{
	}
	if (ms->cmd_nb > cmd_index)
	{
	}
	return ;
}

void	child_process(t_minishell *ms, t_cmd_table *cmd, int cmd_index)
{
	fd_set_up(ms, cmd, cmd_index);//putin de fd need cmdindex to find where I am
	if (cmd->token == T_REDIRECTION)// go back to list and join filename to redir
	{
		redirection();
	}
	check_built_in(ms, cmd);
}

void	exec_pipe(t_minishell *ms)
{
	t_cmd_table	*cmd;
	int			cmd_index;

	cmd = ms->cmd_table;
	cmd_index = 0;
	while (cmd && cmd_index < ms->cmd_nb)
	{
		if (cmd->token == T_REDIRECTION && cmd->metachar != M_DLESS)
			cmd = cmd->next->next;
		else
		{
			if (pipe(cmd->fd) == -1)
				end_program(ms, ER_PIPE);
			cmd->pid = fork();
			if (cmd->pid == -1)
				end_program(ms, ER_FORK);//close fd
			if (cmd->pid == 0)
				child_process(ms, cmd, cmd_index);
			else
			{
				//father
			}
			cmd_index++;
		}
		cmd = cmd->next;
	}
	//close fd ?
}

void	execution(t_minishell *ms)
{
	t_cmd_table	*curr_cmd;

	curr_cmd = ms->cmd_table;

	if (ms->flag_hd)
		heredoc_handler(ms);//fd save?
	if (single_cmd(ms))
	{
		if (ms->flag_pipe == 1)
			exec_pipe(ms);
		else
			exec_cmd_redir(ms);
	}
	//free_heredoc();
	return ;
}
