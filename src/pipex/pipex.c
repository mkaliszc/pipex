/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 22:44:30 by mkaliszc          #+#    #+#             */
/*   Updated: 2024/12/28 03:00:53 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**init_pipes(t_data *data, int argc, char **argv)
{
	int	i;
	int	**pipes_fd;

	pipes_fd = malloc(sizeof(int *) * data->nbr_of_pipe);
	while (i < data->nbr_of_pipe)
	{
		pipes_fd[i] = malloc(sizeof(int) * 2);
		if (!pipes_fd[i])
		{
			free_int_tab(pipes_fd, i);
			return(perror("Failed to allocate the memory for pipes_fd"), NULL);
		}
		if (pipe(pipes_fd[i]) < 0)
		{
			free_int_tab(pipes_fd, i);
			return(perror("Failed to create pipe"), NULL);
		}
		i++;
	}
	return(pipes_fd);
}

void	classic_way(t_data *data, int argc, char **argv, char **envp)
{
	int	main_id;
	int	i;
	
	data->pipes_fd = init_pipes(data, argc, argv);
	if (data->pipes_fd == NULL)
		exit(1);
	main_id = getpid();
	while (i < argc - 3)
	{
		data->pid = fork();
		if (data->pid < 0)
			return (perror("Fork error"));
		if (getpid() == main_id)
			waitpid(data->pid, NULL, 0);
		else
			handle_fork(); // handle children 
		i++;
	}
	// clean open pipes etc
}
