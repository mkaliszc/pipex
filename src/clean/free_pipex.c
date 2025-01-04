/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:36:58 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/01/04 21:06:07 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
