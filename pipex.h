/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusouza- <gusouza-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 22:15:19 by gusouza-          #+#    #+#             */
/*   Updated: 2023/01/06 22:21:59 by gusouza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>

# define COMMAND_NOT_FOUND 127
# define TRUE 0
# define FALSE 1
# define PIPE 1
# define FORK 2
# define ERROR -1

typedef struct s_pipex
{
	char	**cmd;
	char	*cmd_path;
	char	*inf;
	char	*outf;
	int		fd_infile;
	int		fd_outfile;
	int		pipe_fd[2];
}	t_pipex;

int		pipex(char **argv, char **env, t_pipex *pipex);
char	**command_review(char *cmd);
void	child(char **argv, char **env, t_pipex *pipex);
void	free_array(char **array);
void	parent(char **argv, char **env, t_pipex *pipex);
//Errors
int		function_error(int err, t_pipex *pipex);
void	command_not_found(t_pipex *pipex);
void	permission_denied(t_pipex *pipex);
void	quote_missplaced(char *cmd);

#endif