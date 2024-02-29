#include "../minishell.h"

//all heredoc included
//dup duplicate fd 
//int dup2(fd1,fd2) dup new fd2 to copy of fd1
/*
	*  Si  fd1 n’est pas un descripteur de fichier valable, alors l’appel
		échoue et fd2 n’est pas fermé.

	*  Si fd1 est un descripteur de fichier valable et fd2  a  la  même
		valeur que fd1, alors dup2() ne fait rien et renvoie fd2.
	echec = -1
*/

int	open_fd()
{
	int	fd;
	return (fd);
}

int	redirection(t_minishell *ms)
{
	t_cmd_table	*current;
	int			fd;

	current = ms->cmd_table;
	while (current)
	{
		if (current->token == T_REDIRECTION)
		{
			fd = open_fd();
			if (fd < )
				return (EXIT_FAILURE);
			if (current->metachar == M_GREAT || current->metachar == M_DGREAT)
			if (current->metachar == M_LESS)
			{
			}
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

