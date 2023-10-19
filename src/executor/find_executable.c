/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:05:42 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/19 15:05:18 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*search_paths(char **paths, char *cmd)
{
	char	*tmp;
	char	*file_name;
	char	*slash;

	slash = "/";
	while (paths && *paths)
	{
		tmp = ft_strjoin(slash, cmd);
		file_name = ft_strjoin(*paths, tmp);
		free(tmp);
		if (access(file_name, F_OK) == 0)
			return (file_name);
		free(file_name);
		paths++;
	}
	return (NULL);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

char	*get_executable_path(t_cmd cmd, const char *pwd, const char	*path_env)
{
	char	**paths;
	char	*file_name;
	char	*dot_slash;

	dot_slash = "./";
	if (cmd.name && access(cmd.name, F_OK) == 0)
		return (cmd.name);
	paths = ft_split(path_env, ':');
	file_name = search_paths(paths, cmd.name);
	free_paths(paths);
	return (file_name);
}
