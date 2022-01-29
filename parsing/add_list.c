/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouquet <mbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:59:47 by mbouquet          #+#    #+#             */
/*   Updated: 2022/01/25 14:59:48 by mbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_word	*ft_make_word(t_word **l, t_word w)
{
	t_word	*ret;
	t_word	*tmp;

	ret = ft_calloc(1, sizeof(t_word));
	if (ret)
	{
		ret->str = w.str;
		ret->next = w.next;
		if (l)
		{
			tmp = *l;
			if (tmp)
			{
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = ret;
			}
			else
				*l = ret;
		}
	}
	return (ret);
}

static void	fill_lst(t_redirect *ret, t_redirect r)
{
	ret->src_fd = r.src_fd;
	ret->dst_name = r.dst_name;
	ret->here_doc_eof = r.here_doc_eof;
	ret->open_flag = r.open_flag;
	ret->is_heredoc = r.is_heredoc;
	ret->next = r.next;
}

t_redirect	*ft_make_redirect(t_redirect **l, t_redirect r)
{
	t_redirect	*ret;
	t_redirect	*tmp;

	ret = ft_calloc(1, sizeof(t_redirect));
	if (ret)
	{
		fill_lst(ret, r);
		if (l)
		{
			tmp = *l;
			if (tmp)
			{
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = ret;
			}
			else
				*l = ret;
		}
	}
	return (ret);
}

t_command	*ft_make_command(t_command **l, t_command c)
{
	t_command	*ret;
	t_command	*tmp;

	ret = ft_calloc(1, sizeof(t_command));
	if (ret)
	{
		ret->command = c.command;
		ret->redirect = c.redirect;
		ret->next = c.next;
		if (l)
		{
			tmp = *l;
			if (tmp)
			{
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = ret;
			}
			else
				*l = ret;
		}
	}
	return (ret);
}
