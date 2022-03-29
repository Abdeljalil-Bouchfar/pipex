/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:09:16 by abouchfa          #+#    #+#             */
/*   Updated: 2022/03/28 16:34:56 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}

char	*get_cmd(char *str)
{
	char	*cmd;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	cmd = malloc(sizeof(char) * i + 1);
	if (!cmd)
		return (NULL);
	j = -1;
	while (++j < i)
		cmd[j] = str[j];
	cmd[j] = 0;
	return (cmd);
}
