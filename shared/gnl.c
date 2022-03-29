/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:04:18 by abouchfa          #+#    #+#             */
/*   Updated: 2022/03/28 16:30:23 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*get_next_line(int fd)
{
	int		i;
	int		len;
	char	*temp;
	char	*line;
	char	buffer;

	line = NULL;
	buffer = 0;
	while (buffer != '\n' && read(fd, &buffer, 1) > 0)
	{
		i = -1;
		len = 0;
		temp = line;
		if (line)
			len = ft_strlen(line);
		line = malloc(len + 2);
		while (++i < len)
			line[i] = temp[i];
		if (buffer != '\n')
			line[i++] = buffer;
		line[i] = 0;
		if (temp)
			free(temp);
	}
	return (line);
}
