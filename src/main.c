/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:11:06 by mkaliszc          #+#    #+#             */
/*   Updated: 2024/12/21 20:57:25 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	char	*file;
	char	*output_file;

	file = argv[1];
	output_file = argv[argc - 1];
/* 	if (access(argv[1], F_OK) == -1 && access(argv[argc - 1], F_OK) == -1)
		return(perror("Permission denied"), 1); */
	check_arg(argc, argv);
}