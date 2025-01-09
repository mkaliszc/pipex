/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:41:16 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/01/09 00:59:16 by mkaliszc         ###   ########.fr       */
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
	new->previous = NULL;
	new->next = NULL;
	return (new);
}

int	ft_add_cmd(t_cmd *lst, t_cmd *new)
{
	t_cmd	*pos;

	if (!new || !lst)
		return (1);
	pos = lst;
	while (pos->next != NULL)
		pos = pos->next;
	pos->next = new;
	new->previous = pos;
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	int		i;

	data->infile = argv[1];
	data->infile_fd = -1;
	data->out = argv[argc - 1];
	data->outfile_fd = -1;
	data->nbr_of_pipe = argc - 4;
	data->cmd_args = create_node(argv[2]);
	if (data->cmd_args == NULL)
	{
		ft_putstr_fd("Error while creating the cmd_args", 2);
		return (1);
	}
	i = 3;
	while (i < argc - 1)
	{
		if (ft_add_cmd(data->cmd_args, create_node(argv[i])) == 1)
			return (free_lst(data->cmd_args), 1);
		i++;
	}
	return (0);
}
