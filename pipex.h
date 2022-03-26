/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:49:09 by abouchfa          #+#    #+#             */
/*   Updated: 2022/03/26 02:18:59 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPX_H
#define PIPX_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

struct s_pipe_data
{
	char *infile;
	int infile_status;
	char *outfile;
	char **cmds_names;
	char **cmds_paths;
	int cmds_size;
	int is_heredoc;
	char *heredoc;
} typedef t_pipe_data;
int *errors_ids;

void ft_putstr_fd(char *s, int fd);
char *get_cmd(char *str);

int validate_infile(char *infile);
int validate_cmd_from_path(char *cmd_path);
char *validate_cmd(char *cmd, char **exec_programs_dirs);

char **ft_split(char const *s, char c);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strchr(const char *s, char c);
char *ft_strdup(char *src);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strdup(char *src);
char *ft_strnstr(const char *haystack, const char *needle, size_t len);

char *get_next_line(int fd);

#endif