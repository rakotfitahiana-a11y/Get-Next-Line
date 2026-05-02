/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henirako <henirako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 07:53:07 by henirako          #+#    #+#             */
/*   Updated: 2026/02/18 13:24:05 by henirako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_stock(int fd, char *storage)
{
	char	*temp;
	int		r;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	r = 1;
	while ((!ft_strchr(storage, '\n')) && r > 0)
	{
		r = read(fd, temp, BUFFER_SIZE);
		if (r == -1)
		{
			free(temp);
			free(storage);
			return (NULL);
		}
		else if (r == 0)
			break ;
		temp[r] = '\0';
		storage = ft_strjoin(storage, temp);
	}
	free(temp);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;
	char		*tmp;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = read_and_stock(fd, storage);
	if (!storage)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;
	line = ft_substr(storage, 0, i);
	tmp = storage;
	if (storage[i] != '\0')
		storage = ft_strdup(storage + i);
	else
		storage = NULL;
	free(tmp);
	return (line);
}
