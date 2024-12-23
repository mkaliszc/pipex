/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:11:06 by mkaliszc          #+#    #+#             */
/*   Updated: 2024/12/23 20:50:45 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	(void)argc;
	int i = 0;
	int id = getpid();
	int id_fork = fork();
	int	id_fork2 = fork();
	if (getpid() == id)
	{
		printf("%d\n", id);
		sleep(1);
	}
	else if (id_fork == 0)
	{
		printf("id_fork so child : %d && parent : %d\n", id_fork, getppid());
		while (i < 10)
		{
			printf("%d ", i);
			i++;
		}
	}
	else
		printf("id_fork2 so child 2 : %d && parent : %d\n", id_fork, getppid());
	char *args[] = {"/bin/sh", "-c", argv[1], NULL};
	printf("Hello World\n");
	execv("/bin/zsh", args);
	return (0);
}