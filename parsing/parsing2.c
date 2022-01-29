/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:53:48 by mbouquet          #+#    #+#             */
/*   Updated: 2022/01/25 17:10:39 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_make_redir(t_parse_param *p, char *line)
{
	if (!ft_strncmp(line + p->i, ">>", 2))
	{
		p->current_redirect = ft_make_redirect(&(p->current_command->redirect),
				(t_redirect){1, NULL, NULL, O_CREAT | O_APPEND | O_WRONLY,
				0, NULL});
		p->flag = RedirectName;
		p->i++;
	}
	else if (!ft_strncmp(line + p->i, "<", 1))
	{
		p->current_redirect = ft_make_redirect(&(p->current_command->redirect),
				(t_redirect){0, NULL, NULL, O_RDONLY, 0, NULL});
		p->flag = RedirectName;
	}
	else if (!ft_strncmp(line + p->i, ">", 1))
	{
		p->current_redirect = ft_make_redirect
			(&(p->current_command->redirect),
				(t_redirect){1, NULL, NULL, O_CREAT | O_TRUNC | O_WRONLY,
				0, NULL});
		p->flag = RedirectName;
	}
	if (!p->current_redirect)
		return (0);
	return (1);
}

int	ft_try_make_redirect(t_parse_param *param, char *line)
{
	if (param->c == '<' || param->c == '>')
	{
		if (!ft_strncmp(line + param->i, "<<", 2))
		{
			if (!ft_make_heredoc(param))
				return (0);
		}
		else
		{
			if (!ft_make_redir(param, line))
				return (0);
		}
	}
	return (1);
}

int	ft_try_parse(t_command **ret, t_parse_param *param, char *line)
{
	if (!ft_try_make_command(ret, param))
		return (0);
	if ((!(param->quote % 2) && !(param->dquote % 2)
			&& ft_is_oneof(param->c, " \t\n|<>")) || param->c == '\0')
	{
		if (!ft_try_make_word(param))
			return (0);
		if (!ft_try_make_redirect(param, line))
			return (0);
		if (param->c == '|' || param->c == '\0' || param->c == '\n')
			param->flag = Begin;
	}
	else
	{
		param->buf = ft_push_char(param->buf, param->c);
		if (!param->buf)
			return (0);
	}
	return (1);
}
