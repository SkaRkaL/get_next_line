/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:18:20 by sakarkal          #+#    #+#             */
/*   Updated: 2022/11/17 10:50:57 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

char	*get_line(char *save)
{
	int		i;
	char	*str;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		str[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		str[i] = save[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*the_saver(char *save)
{
	int		i;
	int		c;
	char	*str;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	str = malloc(sizeof(char) * ((ft_strlen(save) - i) + 1));
	if (!str)
		return (NULL);
	i++;
	c = 0;
	while (save[i])
		str[c++] = save[i++];
	str[c] = '\0';
	free(save);
	return (str);
}

char	*read_and_store(int fd, char *save)
{
	char	*buff;
	int		read_bytes;

	read_bytes = 1;
	while (!ft_search(save, '\n') && read_bytes != 0)
	{
		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buff)
			return (NULL);
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		save = ft_strjoin(save, buff);
	}
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[10240];
	char		*temp;

	line = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 10240)
		return (0);
	temp = read_and_store(fd, save[fd]);
	if (!temp)
	{
		if (save[fd])
			free(save[fd]);
		save[fd] = NULL;
		return (NULL);
	}
	save[fd] = temp;
	if (save[fd])
		line = get_line(save[fd]);
	save[fd] = the_saver(save[fd]);
	return (line);
}
