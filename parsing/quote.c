/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouquet <mbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 06:54:01 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/25 15:07:19 by mbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unclosed_simple_quote(char *line, int size)
{
	int	i;
	int	squote;
	int	dquote;

	squote = 0;
	dquote = 0;
	i = 0;
	while (line[i] && i < size)
	{
		if (line[i] == '\'' && !(dquote % 2)
			&& (ft_strchr(line + i + 1, '\'') || (squote % 2)))
			squote++;
		if (line[i] == '\"' && !(squote % 2)
			&& (ft_strchr(line + i + 1, '\"') || (dquote % 2)))
			dquote++;
		i++;
	}
	if (!(squote % 2))
		return (0);
	return (1);
}

int	unclosed_double_quote(char *line, int size)
{
	int	i;
	int	squote;
	int	dquote;

	squote = 0;
	dquote = 0;
	i = 0;
	while (line[i] && i < size)
	{
		if (line[i] == '\'' && !(dquote % 2) && (ft_strchr(line + i + 1, '\'')
				|| (squote % 2)))
			squote++;
		if (line[i] == '\"' && !(squote % 2) && (ft_strchr(line + i + 1, '\"')
				|| (dquote % 2)))
			dquote++;
		i++;
	}
	if (!(dquote % 2))
		return (0);
	return (1);
}

int	unclosed_quotes(char *line, int size)
{
	if (unclosed_double_quote(line, size) || unclosed_simple_quote(line, size))
		return (1);
	return (0);
}

static void	trim_bis(t_variables *var, char *cmd)
{
	char	*tmp;

	if (cmd[var->k] == '\'' && !(var->dquote % 2)
		&& (ft_strchr(cmd + var->k + 1, '\'') || (var->squote % 2)))
	{
		var->squote++;
		tmp = ft_substr(cmd, var->start, var->k - var->start);
		var->new = my_strjoin(var->new, tmp);
		free(tmp);
		var->start = var->k + 1;
	}
	if (cmd[var->k] == '\"' && !(var->squote % 2)
		&& (ft_strchr(cmd + var->k + 1, '\"') || (var->dquote % 2)))
	{
		var->dquote++;
		tmp = ft_substr(cmd, var->start, var->k - var->start);
		var->new = my_strjoin(var->new, tmp);
		free(tmp);
		var->start = var->k + 1;
	}
	var->k++;
}

char	**trim_quote(char **cmd)
{
	t_variables	var;
	char		*tmp;
	int			i;

	i = 0;
	while (cmd[i])
	{
		fill_struct(&var);
		while (cmd[i][var.k])
			trim_bis(&var, cmd[i]);
		tmp = ft_substr(cmd[i], var.start, var.k - var.start);
		var.new = my_strjoin(var.new, tmp);
		free(tmp);
		if (var.new)
		{
			free(cmd[i]);
			cmd[i] = var.new;
		}
		i++;
	}
	return (cmd);
}
