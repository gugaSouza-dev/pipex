/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusouza- <gusouza-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 22:14:58 by gusouza-          #+#    #+#             */
/*   Updated: 2023/01/09 01:31:50 by gusouza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"
#include <sys/wait.h>

static void	invalid_file(char *file, int ex_code, t_pipex *pipex)
{
	if (pipex->fd_outfile)
		close(pipex->fd_outfile);
	if (!access(file, F_OK))
	{
		ft_printf("bash: %s: Permission denied\n", file);
		exit (ex_code);
	}
	ft_printf("bash: %s: No such file or directory\n", file);
	exit(ex_code);
}

int	pipex(char **argv, char **env, t_pipex *pipex)
{
	int	process_id;

	if (pipe(pipex->pipe_fd) == ERROR)
		return (function_error(PIPE, pipex));
	process_id = fork();
	if (process_id == ERROR)
		return (function_error(FORK, pipex));
	if (process_id == 0)
		child(argv, env, pipex);
	waitpid(process_id, NULL, 0);
	parent(argv, env, pipex);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex_data;

	if (argc != 5)
	{
		ft_printf("Invalid number of arguments for %s\n", argv[0]);
		return (0);
	}
	pipex_data.fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex_data.fd_outfile == -1)
		invalid_file(argv[4], 1, &pipex_data);
	pipex_data.fd_infile = open(argv[1], O_RDONLY);
	if (pipex_data.fd_infile == -1)
		invalid_file(argv[1], 0, &pipex_data);
	if (argv[2][0] == '\0' || argv[3][0] == '\0')
		exit(0);
	pipex(argv, env, &pipex_data);
	return (0);
}
