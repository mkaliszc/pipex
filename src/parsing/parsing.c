/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:41:16 by mkaliszc          #+#    #+#             */
/*   Updated: 2024/12/28 23:59:16 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_add_cmd(char *content, t_cmd **data)
{
	t_cmd	*new;
	t_cmd	*pos;

	new = malloc(sizeof(t_cmd));
	if (new == NULL)
		return ;
	new->cmd = ft_split(content, ' ');
	if (!*data)
		*data = new;
	else
	{
		pos = *data;
		while (pos->next != NULL)
			pos = pos->next;
		pos->next = new;
	}
	new->next = NULL;
}

void	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	i = 2;
	data->infile = argv[1];
	data->outfile = argv[argc - 1];
	data->nbr_of_pipe = argc - 4;
	data->cmd_args = malloc(sizeof(t_cmd *) * argc - 3);
	while (i < argc - 1)
	{
		ft_add_cmd(argv[i], data->cmd_args);
		i++;
	}
}
