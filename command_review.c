/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_review.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusouza- <gusouza-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 22:17:04 by gusouza-          #+#    #+#             */
/*   Updated: 2023/01/06 22:17:14 by gusouza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

int	quote_check(char *cmd)
{
	int	i;
	int	quote;

	i = -1;
	quote = FALSE;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			quote = TRUE;
			i++;
			if (!cmd[i])
				quote_missplaced(cmd);
			while ((cmd[i] != '\'') && (cmd[i] != '\"'))
			{
				i++;
				if (!cmd[i])
					quote_missplaced(cmd);
			}
		}
	}
	return (quote);
}

void	map_spaces(char **cmd)
{
	int	i;

	i = -1;
	while ((*cmd)[++i])
	{
		if (((*cmd)[i] == '\'') || ((*cmd)[i] == '\"'))
		{
			i++;
			while ((((*cmd)[i] != '\'') && ((*cmd)[i] != '\"')) && (*cmd)[i])
			{
				if ((*cmd)[i] == ' ')
					(*cmd)[i] = 1;
				i++;
			}
		}
	}
}

static void	remap_spaces(char ***cmd)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while ((*cmd)[++i])
	{
		while ((*cmd)[i][++j])
		{
			if (((*cmd)[i][j] == '\'') || ((*cmd)[i][j] == '\"'))
			{
				j++;
				while (((*cmd)[i][j] != '\'') \
				&& ((*cmd)[i][j] != '\"') && ((*cmd)[i][j]))
				{
					if ((*cmd)[i][j] == 1)
						(*cmd)[i][j] = ' ';
					j++;
				}
			}
		}
		j = -1;
	}
}

static void	remove_quotes(char ***cmd)
{
	int		i;
	char	*temp;

	i = -1;
	while ((*cmd)[++i])
	{
		if (((*cmd)[i][0] == '\'') || ((*cmd)[i][0] == '\"'))
		{
			temp = ft_substr((*cmd)[i], 1, ft_strlen((*cmd)[i]) - 2);
			free ((*cmd)[i]);
			(*cmd)[i] = temp;
		}
	}
}

char	**command_review(char *cmd)
{
	char	**formatted_cmd;
	int		quote;

	quote = quote_check(cmd);
	if (quote == TRUE)
	{
		map_spaces(&cmd);
		formatted_cmd = ft_split(cmd, ' ');
		remap_spaces(&formatted_cmd);
		remove_quotes(&formatted_cmd);
		return (formatted_cmd);
	}
	formatted_cmd = ft_split(cmd, ' ');
	return (formatted_cmd);
}
