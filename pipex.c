/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:49:12 by abouchfa          #+#    #+#             */
/*   Updated: 2022/03/29 00:50:42 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	validate_input(t_pipe_data *pipe_data, char *path_var)
{
	char	*cmd;
	char	**exec_programs_dirs;
	int		i;

	i = -1;
	cmd = NULL;
	if (!pipe_data->is_heredoc)
		pipe_data->infile_status = validate_infile(pipe_data->infile);
	else
		pipe_data->infile_status = 0;
	exec_programs_dirs = ft_split(path_var, ':');
	i = -1;
	while (++i < pipe_data->cmds_size)
	{
		if (cmd)
			free(cmd);
		cmd = get_cmd(pipe_data->cmds_names[i]);
		if (i != 0 || pipe_data->infile_status || pipe_data->is_heredoc)
			validate_cmd(cmd, pipe_data->cmds_paths + i, exec_programs_dirs);
		else
			pipe_data->cmds_paths[i] = NULL;
	}
}

void	driver(t_pipe_data *pipe_data, char *envp[])
{
	int	i;
	int	input_fd;

	i = -1;
	input_fd = -1;
	while (++i < pipe_data->cmds_size)
	{
		if (i + 1 != pipe_data->cmds_size)
			pipe(pipe_data->cmd_pipe_fds);
		child_process(i, input_fd, pipe_data, envp);
		if (i == 0 && pipe_data->is_heredoc)
		{
			close(pipe_data->here_doc_pipe_fds[1]);
			close(pipe_data->here_doc_pipe_fds[0]);
		}
		close(pipe_data->cmd_pipe_fds[1]);
		if (input_fd != -1)
			close(input_fd);
		input_fd = pipe_data->cmd_pipe_fds[0];
	}
	close(input_fd);
	i = -1;
	while (++i < pipe_data->cmds_size)
		wait(NULL);
}

void	check_heredoc(t_pipe_data *pipe_data, char *argv[], int argc)
{
	char	*line;

	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		pipe_data->is_heredoc = 1;
		pipe_data->heredoc = argv[2];
		pipe_data->infile = NULL;
		pipe_data->cmds_size = argc - 4;
		pipe(pipe_data->here_doc_pipe_fds);
		line = get_next_line(0);
		while (line == NULL || strcmp(line, pipe_data->heredoc))
		{
			write(pipe_data->here_doc_pipe_fds[1], line, ft_strlen(line));
			write(pipe_data->here_doc_pipe_fds[1], "\n", 1);
			line = get_next_line(0);
		}
	}
	else
	{
		pipe_data->is_heredoc = 0;
		pipe_data->heredoc = NULL;
		pipe_data->infile = argv[1];
		pipe_data->cmds_size = argc - 3;
	}
}

void	set_pipe_data(t_pipe_data *pipe_data,
		int argc, char *argv[], char *envp[])
{
	char	*path_var;
	int		i;

	path_var = NULL;
	pipe_data->outfile = argv[argc - 1];
	pipe_data->cmds_names = malloc((pipe_data->cmds_size) * sizeof(char **));
	pipe_data->cmds_paths = malloc((pipe_data->cmds_size) * sizeof(char **));
	if (!pipe_data->cmds_names || !pipe_data->cmds_paths)
		exit(1);
	i = -1;
	while (++i < pipe_data->cmds_size)
		pipe_data->cmds_names[i] = argv[argc - pipe_data->cmds_size + i - 1];
	i = -1;
	while (envp[++i])
	{
		path_var = ft_strnstr(envp[i], "PATH=", 5);
		if (path_var)
			break ;
	}
	path_var = path_var + 5;
	validate_input(pipe_data, path_var);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe_data	*pipe_data;

	if (argc < 2)
		return (0);
	pipe_data = malloc(sizeof(t_pipe_data));
	if (!pipe_data)
		return (1);
	check_heredoc(pipe_data, argv, argc);
	set_pipe_data(pipe_data, argc, argv, envp);
	driver(pipe_data, envp);
}
