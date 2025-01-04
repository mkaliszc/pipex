/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:43:00 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/01/04 21:04:56 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **cmd, char **envp)
{
	char	**all_paths;
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	all_paths = ft_split(*envp + 5, ':');
	while (all_paths[i])
	{
		tmp = ft_strjoin(all_paths[i], "/");
		path = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(path, X_OK) == 0)
		{
			ft_free_char_tab(all_paths);
			return (path);
		}
		i++;
	}
	free(path);
	return (NULL);
}
