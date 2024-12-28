/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:41:16 by mkaliszc          #+#    #+#             */
/*   Updated: 2024/12/27 19:32:44 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->infile = argv[1];
	data->outfile = argv[argc - 1];
	data->nbr_of_pipe = argc - 4;
}
