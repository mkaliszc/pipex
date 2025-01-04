/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:36:58 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/01/05 00:18:04 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_lst(t_cmd *start)
{
	t_cmd	*tmp;

	while (start->previous != NULL)
		start = start->previous;
	tmp = start;
	while (tmp != NULL)
	{
		tmp = start->next;
		ft_free_char_tab(start->cmd);
		free(start);
		start = tmp;
	}
}

void	close_all_pipes(t_data *data)
{
	int	i;

	if (!data || !data->pipes_fd)
		return ;
	i = -1;
	while (++i < data->nbr_of_pipe)
	{
		if (data->pipes_fd[i][0] != -1)
		{
			close(data->pipes_fd[i][0]);
			data->pipes_fd[i][0] = -1;
		}
		if (data->pipes_fd[i][1] != -1)
		{
			close(data->pipes_fd[i][1]);
			data->pipes_fd[i][1] = -1;
		}
	}
}

void	free_pipex(t_data *data)
{
	if (!data)
		return ;
	if (data->pid)
		free(data->pid);
	if (data->pipes_fd)
		ft_free_int_tab(data->pipes_fd, data->nbr_of_pipe);
	if (data->infile_fd != -1)
	{
		close(data->infile_fd);
		data->infile_fd = -1;
	}
	if (data->outfile_fd != -1)
	{
		close(data->outfile_fd);
		data->outfile_fd = -1;
	}
}
