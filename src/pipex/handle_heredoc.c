/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 01:11:34 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/01/07 03:14:38 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Create a tmp file and get the line form terminal then write this line on the tmp file with ft_pustr_fd then GL...

void	handle_here_doc(char *limiter)
{
	int		tmp_fd;
	char	*line;

	tmp_fd = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (tmp_fd < 0)
		return ;
	while (true)
	{
		ft_printf("heredoc> ");
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, tmp_fd);
		free(line);
	}
	close(tmp_fd);
}

