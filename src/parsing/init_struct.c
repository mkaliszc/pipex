/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:41:16 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/01/04 22:41:03 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*create_node(char *content)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (new == NULL)
		return (NULL);
	new->cmd = ft_split(content, ' ');
	new->next = NULL;
	return (new);
}

int	ft_add_cmd(t_cmd *lst, t_cmd *new)
{
	t_cmd	*pos;

	if(!new || !lst)
		return (1);
	pos = lst;
	while (pos->next != NULL)
		pos = pos->next;
	pos->next = new;
	return(0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	int		i;

	data->infile = argv[1];
	data->infile_fd = -1;
	data->outfile = argv[argc - 1];
	data->outfile_fd = -1;
	data->nbr_of_pipe = argc - 4;
	data->pid = malloc(sizeof(pid_t) * (data->nbr_of_pipe + 1));
	if(!data->pid)
		return (ft_putstr_fd("Error while creating the pid tab", 2), 1);
	data->cmd_args = create_node(argv[2]);
	if (data->cmd_args == NULL)
	{
		free(data->pid);
		ft_putstr_fd("Error while creating the cmd_args", 2);
		return (1);
	}
	i = 3;
	while (i < argc - 1)
	{
		if(ft_add_cmd(data->cmd_args, create_node(argv[i])))
			return (free(data->pid), free_lst(data->cmd_args), 1);
		i++;
	}
	return (0);
}
