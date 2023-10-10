/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:05:42 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/10 15:28:16 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*search_paths(char **paths, char *cmd)
{
	char	*tmp;
	char	*file_name;
	char	slash[2];

	slash[0] = '/';
	slash[1] = 0;
	while (*paths)
	{
		tmp = ft_strjoin((char *) &slash[0], cmd);
		file_name = ft_strjoin(*paths, tmp);
		free(tmp);
		if (access(file_name, F_OK) == 0)
			return (file_name);
		free(file_name);
		paths++;
	}
	return (NULL);
}

char	*get_executable_path(t_cmd cmd, const char *pwd, const char	*path_env)
{
	char	**paths;
	char	*file_name;
	char	dot_slash[3];

	dot_slash[0] = '.';
	dot_slash[1] = '/';
	dot_slash[2] = 0;
	if (cmd.cmd[0] == '/' && access(cmd.cmd, F_OK) == 0)
		return (cmd.cmd);
	if (ft_strncmp(cmd.cmd, (char *) &dot_slash, 2) == 0)
	{
		file_name = ft_strjoin(pwd, &cmd.cmd[1]);
		printf("%s", file_name);
		if (access(file_name, F_OK) == 0)
			return (file_name);
	}
	paths = ft_split(path_env, ':');
	file_name = search_paths(paths, cmd.cmd);
	// TODO free paths
	return (file_name);
}
