/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:57:34 by mbouquet          #+#    #+#             */
/*   Updated: 2022/01/25 17:08:07 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parse_param	ft_init_param(void)
{
	t_parse_param	param;

	param.current_command = NULL;
	param.current_redirect = NULL;
	param.buf = NULL;
	param.flag = Begin;
	param.quote = 0;
	param.dquote = 0;
	param.i = 0;
	return (param);
}

int	ft_try_make_command(t_command **ret, t_parse_param *param)
{
	if (param->flag == Begin)
	{
		param->current_command = ft_make_command(ret,
				(t_command){NULL, NULL, NULL});
		param->flag = None;
	}
	if (!param->current_command)
		return (0);
	return (1);
}

int	ft_try_make_word(t_parse_param *param)
{
	if (param->buf)
	{
		if (param->flag == RedirectName)
			param->current_redirect->dst_name = param->buf;
		else if (param->flag == HereDocEof)
			param->current_redirect->here_doc_eof = param->buf;
		else
		{
			if (!ft_make_word(&(param->current_command->command),
					(t_word){param->buf, NULL}))
				return (0);
		}
		param->buf = NULL;
		param->flag = None;
	}
	return (1);
}

int	ft_make_heredoc(t_parse_param *p)
{
	char	*filename;
	char	*n;

	n = ft_itoa(p->i);
	if (!n)
		return (0);
	filename = ft_strjoin("./heredoc_", n);
	free(n);
	if (!filename)
		return (0);
	p->current_redirect = ft_make_redirect(&(p->current_command->redirect),
			(t_redirect){0, filename, NULL, O_RDONLY, 1, NULL});
	if (!p->current_redirect)
	{
		free(filename);
		return (0);
	}
	p->flag = HereDocEof;
	p->i++;
	return (1);
}

t_command	*ft_parse(char *line)
{
	t_command		*ret;
	t_parse_param	param;

	ret = NULL;
	param = ft_init_param();
	while (param.i <= ft_strlen(line))
	{
		param.c = line[param.i];
		if (param.c == '\'' && !(param.dquote % 2)
			&& (ft_strchr(line + param.i + 1, '\'') || param.quote % 2))
			param.quote++;
		if (param.c == '\"' && !(param.quote % 2)
			&& (ft_strchr(line + param.i + 1, '\"') || param.dquote % 2))
			param.dquote++;
		if (!ft_try_parse(&ret, &param, line))
			return (ft_free_and_return_null(ret, &param));
		param.i++;
	}
	return (ret);
}
