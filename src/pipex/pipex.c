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

int	**create_pipes_fd(t_data *data)
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
			return (perror("Failed to allocate the memory for pipes_fd"), NULL);
		}
		pipes_fd[i][0] = -1;
		pipes_fd[i][1] = -1;
		i++;
	}
	return (pipes_fd);
}

bool	init_pipes(t_data *data)
{
	int	i;

	data->pipes_fd = create_pipes_fd(data);
	if (!data->pipes_fd)
		return (false);
	i = 0;
	while (i < data->nbr_of_pipe)
	{
		if (pipe(data->pipes_fd[i]) < 0)
		{
			close_all_pipes(data);
			return (perror("Failed to create pipe"), false);
		}
		i++;
	}
	return (true);
}

void	handle_fork(t_data *data, char **envp, int index)
{
	if (index == 0)
		first_child(data);
	else if (index == data->nbr_of_pipe)
		last_child(data);
	else
		inter_child(data, index);
	close_all_pipes(data);
	free_pipex(data);
	data->path = validate_cmd(data->cmd_args->cmd, envp);
	if (data->path == NULL)
	{
		free_lst(data->cmd_args);
		free(data);
		ft_putstr_fd("Command not found", 2);
		exit(1);
	}
	if (execve(data->path, data->cmd_args->cmd, envp) < 0)
	{
		free_lst(data->cmd_args);
		free(data);
		exit(1);
	}
}

int	init_pipes_and_pid(t_data *data)
{
	if (init_pipes(data) == false)
	{
		data->pid = NULL;
		return (ft_putstr_fd("Error while creating the pipes", 2), -1);
	}
	data->pid = malloc(sizeof(pid_t) * (data->nbr_of_pipe + 1));
	if (!data->pid)
		return (ft_putstr_fd("Error while creating the pid tab", 2), -1);
	return (0);
}

void	classic_way(t_data *data, char **envp)
{
	t_cmd	*start;
	int		i;

	if (init_pipes_and_pid(data) < 0)
		return (free_lst(data->cmd_args), free_pipex(data), free(data));
	i = -1;
	start = data->cmd_args;
	while (++i <= data->nbr_of_pipe)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			return (perror("Fork error"));
		if (data->pid[i] == 0)
			handle_fork(data, envp, i);
		data->cmd_args = data->cmd_args->next;
	}
	close_all_pipes(data);
	i = -1;
	while (++i <= data->nbr_of_pipe)
		waitpid(data->pid[i], NULL, 0);
	free_lst(start);
	free_pipex(data);
	free(data);
}
