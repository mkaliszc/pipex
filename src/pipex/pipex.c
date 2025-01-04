/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 22:44:30 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/01/02 21:17:29 by mkaliszc         ###   ########.fr       */
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

int	**init_pipes(t_data *data)
{
	int	i;
	int	**pipes_fd;

	pipes_fd = malloc(sizeof(int *) * data->nbr_of_pipe);
	if (pipes_fd == NULL)
		return (NULL);
	i = 0;
	while (i < data->nbr_of_pipe)
	{
		pipes_fd[i] = malloc(sizeof(int) * 2);
		if (!pipes_fd[i])
		{
			ft_free_int_tab(pipes_fd, i);
			return(perror("Failed to allocate the memory for pipes_fd"), NULL);
		}
		if (pipe(pipes_fd[i]) < 0)
		{
			ft_free_int_tab(pipes_fd, i);
			return(perror("Failed to create pipe"), NULL);
		}
		i++;
	}
	return(pipes_fd);
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

void	handle_fork(t_data *data, int argc, char **envp, int index)
{
	if (index == 0)
		first_child(data);
	else if (index == argc - 4)
		last_child(data);
	else
		inter_child(data, index);
	close_all_pipes(data);
	free_pipex(data);
	data->path = get_path(data->cmd_args->cmd, envp);
	if (execve(data->path, data->cmd_args->cmd, envp) < 0)
		exit(1);
}

void	classic_way(t_data *data, int argc, char **envp)
{
	t_cmd	*tmp;
	int	main_id;
	int	i;
	
	data->pipes_fd = init_pipes(data);
	if (data->pipes_fd == NULL)
		exit(1);
	data->pid = malloc(sizeof(pid_t) * (data->nbr_of_pipe + 1));
	main_id = getpid();
	i = 0;
	tmp = data->cmd_args;
	while (i <= data->nbr_of_pipe)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			return (perror("Fork error"));
		if (data->pid[i] == 0)
			handle_fork(data, argc, envp, i);
		data->cmd_args = data->cmd_args->next;
		ft_free_char_tab(tmp->cmd);
		free(tmp);
		tmp = data->cmd_args;
		i++;
	}
	close_all_pipes(data);
	i = -1;
	while (++i <= data->nbr_of_pipe)
		waitpid(data->pid[i], NULL, 0);
	free_pipex(data);
	free(data);
}
