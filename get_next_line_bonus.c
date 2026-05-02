/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henirako <henirako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 08:22:38 by henirako          #+#    #+#             */
/*   Updated: 2026/02/24 08:28:58 by henirako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_and_stock(int fd, char *strg)
{
	char	*temp;
	int		r;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	r = 1;
	while (!ft_strchr(strg, '\n') && r > 0)
	{
		r = read(fd, temp, BUFFER_SIZE);
		if (r == -1)
		{
			free(temp);
			free(strg);
			return (NULL);
		}
		if (r == 0)
			break ;
		temp[r] = '\0';
		strg = ft_strjoin(strg, temp);
	}
	free(temp);
	return (strg);
}

char	*get_next_line(int fd)
{
	static char	*strg[1024];
	char		*line;
	char		*tmp;
	int			i;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	strg[fd] = read_and_stock(fd, strg[fd]);
	if (!strg[fd])
		return (NULL);
	i = 0;
	while (strg[fd][i] && strg[fd][i] != '\n')
		i++;
	if (strg[fd][i] == '\n')
		i++;
	line = ft_substr(strg[fd], 0, i);
	tmp = strg[fd];
	if (strg[fd][i] != '\0')
		strg[fd] = ft_strdup(strg[fd] + i);
	else
		strg[fd] = NULL;
	free(tmp);
	return (line);
}
