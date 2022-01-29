/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:08:16 by mbouquet          #+#    #+#             */
/*   Updated: 2022/01/25 17:07:31 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_words(t_word *l)
{
	if (l)
	{
		if (l->next)
			ft_free_words(l->next);
		l->next = NULL;
		free(l->str);
		l->str = NULL;
		free(l);
	}
}

void	ft_free_redirects(t_redirect *l)
{
	if (l)
	{
		if (l->next)
			ft_free_redirects(l->next);
		l->next = NULL;
		free(l->dst_name);
		l->dst_name = NULL;
		free(l->here_doc_eof);
		l->here_doc_eof = NULL;
		free(l);
	}
}

void	ft_free_commands(t_command *l)
{
	if (l)
	{
		if (l->next)
			ft_free_commands(l->next);
		l->next = NULL;
		ft_free_words(l->command);
		l->command = NULL;
		ft_free_redirects(l->redirect);
		l->redirect = NULL;
		free(l);
	}
}

void	delete_hfile(t_command *cmd)
{
	t_redirect	*tmp;

	while (cmd)
	{
		tmp = cmd->redirect;
		while (tmp)
		{
			if (tmp->here_doc_eof)
				unlink(tmp->dst_name);
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
}

t_command	*ft_free_and_return_null(t_command *ret, t_parse_param *param)
{
	ft_free_commands(ret);
	free(param->buf);
	return (NULL);
}
