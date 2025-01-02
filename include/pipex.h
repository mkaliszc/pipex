/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:11:32 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/01/02 20:36:56 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
# define PIPEX_H

# include "../OctoLIB/include/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdbool.h>

typedef struct s_cmd
{
	char			**cmd;
	struct s_cmd	*next;
}			t_cmd;

typedef	struct s_data
{
	char	*infile;
	int		infile_fd;
	char	*outfile;
	int		outfile_fd;
	int		nbr_of_pipe;
	t_cmd 	*cmd_args;
	int		**pipes_fd;
	pid_t	*pid;
	char	*path;
}			t_data;

void	init_data(t_data *data, int argc, char **argv);
void	first_child(t_data *data);
void	last_child(t_data *data);
void	inter_child(t_data *data, int i);
void	classic_way(t_data *data, int argc, char **envp);
char	*get_path(char **cmd, char **envp);

#endif