/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 01:11:34 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/01/07 23:57:31 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	update_data(t_data *data)
{
	t_cmd	*clean;

	clean = data->cmd_args;
	data->cmd_args = data->cmd_args->next;
	ft_free_char_tab(clean->cmd);
	free(clean);
	data->cmd_args->previous = NULL;
	data->infile = "tmp";
	data->nbr_of_pipe -= 1;
	data->here_doc = true;
}

void	handle_here_doc(char *limiter, t_data *data)
{
	int		tmp_fd;
	char	*line;

	tmp_fd = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
	update_data(data);
}
