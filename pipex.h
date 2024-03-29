/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:49:09 by abouchfa          #+#    #+#             */
/*   Updated: 2022/04/09 08:28:07 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_pipe_data
{
	char	*infile_path;
	int		infile_status;
	char	*outfile_path;
	char	**cmds_names;
	char	**cmds_paths;
	int		cmds_size;
	int		is_heredoc;
	char	*heredoc_limiter;
	int		cmd_pipe_fds[2];
	int		here_doc_pipe_fds[2];
}	t_pipe_data;

void	ft_putstr_fd(char *s, int fd);
void	ft_free_str(char *str);
void	ft_free_arr(char **arr);
void	get_herdoc(t_pipe_data *pipe_data);
char	*get_cmd(char *str);

void	validate_cmd(char *cmd, char **cmd_path, char **exec_programs_dirs);
int		validate_infile(char *infile_path);

void	child_process(int i, int input_fd,
			t_pipe_data *pipe_data, char *envp[]);

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, char c);
char	*ft_strdup(char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(char *src);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);

#endif