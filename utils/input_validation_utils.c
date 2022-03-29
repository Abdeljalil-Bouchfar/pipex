/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:09:57 by abouchfa          #+#    #+#             */
/*   Updated: 2022/03/28 23:58:48 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*put_cmd_status(int status, char *cmd_path, char *cmd)
{
	if (status)
	{
		if (status == 1)
			ft_putstr_fd("command not found: ", 2);
		else
			ft_putstr_fd("permission denied: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
	}
	if (status)
	{
		if (cmd_path)
			free(cmd_path);
		return (NULL);
	}
	else
		return (cmd_path);
}

char	*get_cmd_path(char *cmd, char **exec_programs_dirs)
{
	char	*cmd_path;
	int		i;
	int		status;

	i = -1;
	status = 1;
	cmd_path = NULL;
	while (exec_programs_dirs[++i] && cmd[0])
	{
		if (cmd_path)
			free(cmd_path);
		cmd_path = ft_strjoin(exec_programs_dirs[i], "/");
		cmd_path = ft_strjoin(cmd_path, cmd);
		if (access(cmd_path, F_OK))
			status = 1;
		else if (access(cmd_path, X_OK))
			status = 2;
		else
		{
			status = 0;
			break ;
		}
	}
	return (put_cmd_status(status, cmd_path, cmd));
}

void	validate_cmd(char *cmd, char **cmd_path, char **exec_programs_dirs)
{
	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, F_OK) && !access(cmd, X_OK))
			*cmd_path = ft_strdup(cmd);
		else
		{
			*cmd_path = NULL;
			perror(cmd);
		}
	}
	else
		*cmd_path = get_cmd_path(cmd, exec_programs_dirs);
}

int	validate_infile(char *infile)
{
	if (!access(infile, F_OK) && !access(infile, R_OK))
		return (1);
	perror(infile);
	return (0);
}
