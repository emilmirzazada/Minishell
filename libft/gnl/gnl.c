/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:16:46 by emirzaza          #+#    #+#             */
/*   Updated: 2023/08/16 23:05:24 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_free(char	*str)
{
	free(str);
	str = NULL;
	return (NULL);
}

char	*get_res(char	*collector)
{
	char	*str;
	int		i;

	i = 0;
	if (collector[i] == '\0')
		return (NULL);
	while (collector[i] != '\0' && collector[i] != '\n')
		i++;
	if (collector[i] == '\n')
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (str);
	i = 0;
	while (*collector != '\0' && *collector != '\n')
		str[i++] = *collector++;
	if (*collector == '\n')
		str[i++] = *collector++;
	str[i] = '\0';
	return (str);
}

char	*read_line(int fd, char *collector, int *read_bytes)
{
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		ft_free(collector);
		return (NULL);
	}
	while (!ft_strchr(collector, '\n') && *read_bytes > 0)
	{
		*read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (*read_bytes == -1)
		{
			ft_free(collector);
			return (ft_free(buffer));
		}
		buffer[*read_bytes] = '\0';
		collector = gnl_strjoin(collector, buffer);
	}
	ft_free(buffer);
	return (collector);
}

char	*get_new_buffer(char	*collector, int read_bytes)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (collector[i] != '\0' && collector[i] != '\n')
		i++;
	if (collector[i] == '\0' || read_bytes == 0)
		return (ft_free(collector));
	str = malloc((ft_strlen(collector) - i + 1) * sizeof(char));
	if (!str)
	{
		ft_free(collector);
		return (str);
	}
	i++;
	while (collector[i] != '\0')
		str[j++] = collector[i++];
	str[j] = '\0';
	ft_free(collector);
	return (str);
}

int	get_next_line(int fd, char	**line)
{
	static char	*collector[4096];
	char		*res;
	int			read_bytes;

	read_bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	collector[fd] = read_line(fd, collector[fd], &read_bytes);
	if (!collector[fd])
		return (-1);
	res = get_res(collector[fd]);
	if (!res)
	{
		ft_free_and_make_null(&collector[fd]);
		return (-1);
	}
	collector[fd] = get_new_buffer(collector[fd], read_bytes);
	*line = res;
	return (0);
}
