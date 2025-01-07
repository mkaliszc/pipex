/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:11:32 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/01/08 00:24:41 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
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
	struct s_cmd	*previous;
}			t_cmd;

typedef struct s_data
{
	char	*infile;
	int		infile_fd;
	char	*out;
	int		outfile_fd;
	int		nbr_of_pipe;
	t_cmd	*cmd_args;
	int		**pipes_fd;
	pid_t	*pid;
	char	*path;
	bool	here_doc;
}			t_data;

int		init_data(t_data *data, int argc, char **argv);
void	first_child(t_data *data);
void	last_child(t_data *data);
void	inter_child(t_data *data, int i);
void	classic_way(t_data *data, char **envp);
void	free_pipex(t_data *data);
void	close_all_pipes(t_data *data);
void	free_lst(t_cmd *start);
char	*get_path(char **cmd, char **envp);
char	*validate_cmd(char **cmd, char **envp);

void	handle_here_doc(char *limiter, t_data *data);

#endif