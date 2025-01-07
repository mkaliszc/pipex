/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:11:06 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/01/07 03:14:21 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (perror("allocation data struct failed"), 1);
	if (init_data(data, argc, argv) != 0)
	{
		free(data);
		return (1);
	}
 	if (ft_strncmp(data->infile, "here_doc", 8) == 0)
		handle_here_doc(argv[2]);
	else
		classic_way(data, argc, envp);
	return (0);
}
