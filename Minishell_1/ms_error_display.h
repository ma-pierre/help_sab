/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_display.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouhsan <saouhsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 07:14:37 by saouhsan          #+#    #+#             */
/*   Updated: 2024/02/28 22:45:43 by saouhsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERROR_DISPLAY_H
# define MS_ERROR_DISPLAY_H

/*---------- MS ERROR SYNTAX----------*/

/*---------- MS SHELL ERROR ----------*/
# define MS "minishell:"
# define NO_F_OR_D "No such file or directory"
# define ARG "too many arguments"
# define NOT_SET "not set"
# define NOT_FOUND "not found"

/*---------- END PROGRAM ERROR ----------*/

# define ER_READLINE "Error: readline failure"
# define ER_STRUC_INIT "Error: ms structure initilization failure"
# define ER_FORK "Error: fork failure"
# define ER_PIPE "Error: pipe failure"
# define ER_GETCWD "Error: getcwd failure"
# define ER_CHDIR "Error: chdir failure"
# define ER_MALLOC "Error: malloc failure"
# define END "Minish test"

#endif
