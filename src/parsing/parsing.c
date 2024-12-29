/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:41:16 by mkaliszc          #+#    #+#             */
/*   Updated: 2024/12/29 02:40:55 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*create_node(char *content)
{
	t_cmd	*new;
	
	new = malloc(sizeof(t_cmd));
	if (new == NULL)
		return ;
	new->cmd = ft_split(content, ' ');
	new->next = NULL;
}

void	ft_add_cmd(t_cmd *lst, t_cmd *new)
{
	t_cmd	*pos;


	pos = lst;
	while (pos->next != NULL)
		pos = pos->next;
	pos->next = new;
	new->next = NULL;
}

void	init_data(t_data *data, int argc, char **argv)
{
	int		i;

	data->infile = argv[1];
	data->outfile = argv[argc - 1];
	data->nbr_of_pipe = argc - 4;
	data->cmd_args = create_node(argv[2]);
	if (data->cmd_args == NULL)
		return(ft_printf("Error while creating the cmd_args"));
	i = 3;
	while (i < argc - 1)
	{
		ft_add_cmd(data->cmd_args, create_node(argv[i]));
		i++;
	}
}
