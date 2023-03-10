/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:43:46 by atoof             #+#    #+#             */
/*   Updated: 2023/03/10 15:16:01 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void validate_args(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("pipex: Argument numbers is invalid\n", STDERR_FILENO);
		exit(1);
	}
}

void create_pipe(t_pipex *pipex)
{
	if (pipe(pipex->end) < 0)
		perror("pipex");
}

void get_command_paths(t_pipex *pipex)
{
	pipex->paths = find_path(environ);
	pipex->cmd_paths = ft_split(pipex->paths, ':');
}

void get_command_arguments(t_pipex *pipex, char **argv)
{
    pipex->cmd_arguments = ft_split(argv[2], ' ');
    if (is_absolute_path(pipex->cmd_arguments[0]))
        pipex->cmd = ft_strdup(pipex->cmd_arguments[0]);
    else
        pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_arguments[0]);
}

void wait_for_child_processes(t_pipex pipex)
{
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
}

int open_files(t_pipex *pipex, char *infile_path, char *outfile_path)
{
	int value;
	value = TRUE;
	
    pipex->infile = open(infile_path, O_RDONLY);
	if (pipex->infile < 0)
    {
        perror("pipex");
        value = FALSE;
    }
	pipex->outfile = open(outfile_path, O_TRUNC | O_CREAT | O_RDWR, 0644);
    if (pipex->outfile < 0)
        error("pipex");
    return value;
}

void fork_child1(t_pipex *pipex, char **argv, char **environ)
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		error("pipex");
	if (pipex->pid1 == 0)
		child1(*pipex, argv, environ);
	free_child(pipex);
}

void fork_child2(t_pipex *pipex, char **argv, char **environ)
{
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		error("pipex");
	if (pipex->pid2 == 0)
		child2(*pipex, argv, environ);
}

int is_absolute_path(char *path)
{
    if (access(path, F_OK) == 0)
        return TRUE;
    else
        return FALSE;
}

void initialize_pipe(t_pipex *pipex)
{
    pipex->pid1 = 0;
    pipex->pid2 = 0;
    pipex->end[0] = 0;
    pipex->end[1] = 0;
    pipex->infile = 0;
    pipex->outfile = 0;
    pipex->paths = getenv("PATH");
    pipex->cmd_paths = NULL;
    pipex->cmd_arguments = NULL;
    pipex->cmd = NULL;
}
