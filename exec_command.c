/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusouza- <gusouza-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 22:16:07 by gusouza-          #+#    #+#             */
/*   Updated: 2023/01/09 01:31:24 by gusouza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

static char	**get_directories(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			return (ft_split(env[i] + 5, ':'));
	}
	return (NULL);
}

static char	*find_command(char *command, char **env)
{
	char	**directories;
	char	*raw_path;
	char	*temp;
	int		i;

	directories = get_directories(env);
	i = -1;
	while (directories[++i])
	{
		temp = ft_strjoin(directories[i], "/");
		raw_path = ft_strjoin(temp, command);
		free(temp);
		if (access(raw_path, F_OK) == 0)
		{
			free_array(directories);
			return (raw_path);
		}
		free(raw_path);
	}
	free_array(directories);
	return (NULL);
}

void	child(char **argv, char **env, t_pipex *pipex)
{
	pipex->cmd = command_review(argv[2]);
	pipex->cmd_path = find_command(pipex->cmd[0], env);
	if (pipex->cmd_path == NULL)
		command_not_found(pipex);
	if (pipex->fd_infile == ERROR)
		permission_denied(pipex);
	dup2(pipex->fd_infile, STDIN_FILENO);
	dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close(pipex->fd_infile);
	execve(pipex->cmd_path, pipex->cmd, env);
}

void	parent(char **argv, char **env, t_pipex *pipex)
{
	pipex->cmd = command_review(argv[3]);
	pipex->cmd_path = find_command(pipex->cmd[0], env);
	if (pipex->cmd_path == NULL)
		command_not_found(pipex);
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	dup2(pipex->fd_outfile, STDOUT_FILENO);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	execve(pipex->cmd_path, pipex->cmd, env);
}
