/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:43:00 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/01/09 00:59:58 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*validate_cmd(char **cmd, char **envp)
{
	if (cmd[0] == NULL)
		return (NULL);
	if (access(cmd[0], X_OK) == 0)
		return (cmd[0]);
	else
		return (get_path(cmd, envp));
}

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
		free(path);
		i++;
	}
	ft_free_char_tab(all_paths);
	return (NULL);
}
