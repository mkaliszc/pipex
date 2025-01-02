/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:08:34 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/01/02 23:52:49 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_file_opening(t_data *data, bool input)
{
	data->infile_fd = -1;
	data->outfile_fd = -1;
	data->infile_fd = open(data->infile, O_RDONLY);
	if (data->infile_fd < 0 && input == true)
	{
		// clean
		perror("Error encountered while oppening the infile");
		exit(1);
	}
	data->outfile_fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile_fd < 0 && input == false)
	{
		// clean
		perror("Error encountered while oppening the outfile");
		exit(EXIT_FAILURE);
	}
}

void	first_child(t_data *data)
{
	handle_file_opening(data, true);
	if (dup2(data->infile_fd, STDIN_FILENO) < 0)
	{
		//clean
		perror("Error encountered while redirecting the first child reading");
		exit(1);
	}
	if (dup2(data->pipes_fd[0][1], STDOUT_FILENO) < 0)
	{
		// clean
		perror("Error encountered while redirecting the first child writing");
		exit(1);
	}
}

void	last_child(t_data *data)
{
	handle_file_opening(data, false);
	if (dup2(data->pipes_fd[data->nbr_of_pipe - 1][0], STDIN_FILENO) < 0)
	{
		// clean
		perror("Error encountered while redirecting the last child reading");
		exit(1);
	}
	if (dup2(data->outfile_fd, STDOUT_FILENO) < 0)
	{
		//clean
		perror("Error encountered while redirecting the last child writing");
		exit(1);
	}
}
void	inter_child(t_data *data, int i)
{
	if (dup2(data->pipes_fd[i - 1][0], STDIN_FILENO) < 0)
	{
		//clean
		perror("Error encountered while redirecting one of the child reading");
		exit(1);
	}
	if (dup2(data->pipes_fd[i][1], STDOUT_FILENO) < 0)
	{
		// clean
		perror("Error encountered while redirecting one of the child writing");
		exit(1);
	}
}