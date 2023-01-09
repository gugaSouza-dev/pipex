/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusouza- <gusouza-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 22:16:38 by gusouza-          #+#    #+#             */
/*   Updated: 2023/01/06 22:21:52 by gusouza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

int	function_error(int err, t_pipex *pipex)
{
	if (err == PIPE)
	{
		ft_printf("Pipe error\n");
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
		return (-2);
	}
	if (err == FORK)
	{
		ft_printf("Fork error\n");
		return (-3);
	}
	return (0);
}

void	permission_denied(t_pipex *pipex)
{
	ft_printf("bash: %s: Permission denied\n", pipex->inf);
	free(pipex->cmd_path);
	free_array(pipex->cmd);
	exit(0);
}

void	command_not_found(t_pipex *pipex)
{
	ft_printf("bash: %s: Command not found\n", pipex->cmd[0]);
	free(pipex->cmd_path);
	free_array(pipex->cmd);
	exit(COMMAND_NOT_FOUND);
}

void	quote_missplaced(char *cmd)
{
	ft_printf("Error: The quotes in \"%s\" are missplaced\n", cmd);
	exit(EXIT_FAILURE);
}
