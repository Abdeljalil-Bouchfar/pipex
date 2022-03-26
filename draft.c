void here_doc_prep(char *here_doc_limiter, int *here_doc_pipe_fds)
{
	char *line;
	dup2(here_doc_pipe_fds[1], 1);
	line = get_next_line(0);
	while (line != NULL && ft_strncmp(line, here_doc_limiter, strlen(line) - 1))
	{
		write(1, line, strlen(line));
		line = get_next_line(0);
	}
	dup2(here_doc_pipe_fds[0], 0);
	close(here_doc_pipe_fds[1]);
	close(here_doc_pipe_fds[0]);
}