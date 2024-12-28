/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:11:32 by mkaliszc          #+#    #+#             */
/*   Updated: 2024/12/28 02:44:01 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
# define PIPEX_H

# include "../OctoLIB/include/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_cmd
{
	char	**cmd; // split pour les args exemple "ls" "-l"
	t_cmd	*next;
}			t_cmd;

typedef	struct s_data
{
	char	*infile;
	char	*outfile;
	int		nbr_of_pipe;
	t_cmd 	**cmd_args;
	int		**pipes_fd;
	pid_t	pid;
}			t_data;

#endif