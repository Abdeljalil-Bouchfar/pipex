/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:49:12 by abouchfa          #+#    #+#             */
/*   Updated: 2022/03/24 19:12:03 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void validate_input(t_pipe_data *pipe_data, char *path_var)
{
	char *cmd;
	char **exec_programs_dirs;
	int i;

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
		{
			if (ft_strchr(cmd, '/'))
			{
				if (validate_cmd_from_path(cmd))
					pipe_data->cmds_paths[i] = ft_strdup(cmd);
				else
					pipe_data->cmds_paths[i] = NULL;
			}
			else
				pipe_data->cmds_paths[i] = validate_cmd(cmd, exec_programs_dirs);
		}
		else
			pipe_data->cmds_paths[i] = NULL;
	}
}

void first_cmd_prep(t_pipe_data *pipe_data, int *pipe_fds)
{
	int fd;
	char *line;

	dup2(pipe_fds[1], 1);
	if (pipe_data->infile_status)
	{
		fd = open(pipe_data->infile, O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
	else if (pipe_data->is_heredoc)
	{
		line = get_next_line(0);
		while (line != NULL && ft_strncmp(line, pipe_data->heredoc, strlen(line) - 1))
		{
			write(1, line, strlen(line));
			line = get_next_line(0);
		}
	}
}

void ith_cmd_prep(int i, t_pipe_data *pipe_data, int *pipe_fds, int input_fd)
{
	int fd;

	if (i + 1 == pipe_data->cmds_size)
	{
		fd = open(pipe_data->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		dup2(fd, 1);
		close(fd);
	}
	else
		dup2(pipe_fds[1], 1);
	dup2(input_fd, 0);
}

void exec_cmd(char *cmd, char *cmd_path, char **envp, int *pipe_fds, int input_fd)
{
	char **argv;

	argv = NULL;
	if (ft_strchr(cmd, '\''))
		argv = ft_split(cmd, '\'');
	else
		argv = ft_split(cmd, ' ');
	close(pipe_fds[1]);
	close(pipe_fds[0]);
	close(input_fd);
	if (execve(cmd_path, argv, envp) == -1)
		ft_putstr_fd(strerror(errno), 2);
}

void execute_commands(t_pipe_data *pipe_data, char **envp)
{
	int pipe_fds[2];
	int i = -1;
	int id;
	int input_fd = -1;

	while (++i < pipe_data->cmds_size)
	{
		pipe(pipe_fds);
		if (pipe_data->cmds_paths[i])
		{
			id = fork();
			if (id == 0)
			{
				if (i == 0)
					first_cmd_prep(pipe_data, pipe_fds);
				else
					ith_cmd_prep(i, pipe_data, pipe_fds, input_fd);
				// char d = i + '0';
				// write(2,"here i is ", 10);
				// write(2, &d, 1);
				// write(2,"\n", 1);
				exec_cmd(pipe_data->cmds_names[i], pipe_data->cmds_paths[i], envp, pipe_fds, input_fd);
			}
		}
		close(pipe_fds[1]);
		if (input_fd != -1)
			close(input_fd);
		input_fd = pipe_fds[0];
	}
	close(input_fd);
	i = -1;
	while (++i < pipe_data->cmds_size)
		wait(NULL);
}

void check_heredoc(t_pipe_data *pipe_data, char *argv[], int argc)
{
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		pipe_data->is_heredoc = 1;
		pipe_data->heredoc = argv[2];
		pipe_data->infile = NULL;
		pipe_data->cmds_size = argc - 4;
	}
	else
	{
		pipe_data->is_heredoc = 0;
		pipe_data->heredoc = NULL;
		pipe_data->infile = argv[1];
		pipe_data->cmds_size = argc - 3;
	}
}

void set_pipe_data(t_pipe_data *pipe_data, int argc, char *argv[], char *envp[])
{
	char *path_var;
	int i;

	check_heredoc(pipe_data, argv, argc);
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
		if (!path_var)
			path_var = ft_strnstr(envp[i], "PATH=", 5);
	path_var = path_var + 5;
	// i = -1;
	// while (++i < pipe_data->cmds_size)
	// 	printf("---> %s\n", pipe_data->cmds_names[i]);
	validate_input(pipe_data, path_var);
}

int main(int argc, char *argv[], char *envp[])
{
	t_pipe_data *pipe_data;

	if (argc < 2)
		return (0);
	pipe_data = malloc(sizeof(t_pipe_data));
	if (!pipe_data)
		return (1);
	set_pipe_data(pipe_data, argc, argv, envp);
	execute_commands(pipe_data, envp);
}