/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouquet <mbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:11:27 by mbouquet          #+#    #+#             */
/*   Updated: 2022/01/26 12:25:49 by mbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_struct(t_variables *var)
{
	var->dquote = 0;
	var->squote = 0;
	var->k = 0;
	var->start = 0;
	var->new = NULL;
}

int	size_commandes(t_command *commandes)
{
	int	i;

	i = 0;
	while (commandes)
	{
		i++;
		commandes = commandes->next;
	}
	return (i);
}

t_command	*syntaxe_error(t_command *commandes)
{
	t_command	*tmp;
	int			size;

	tmp = commandes;
	size = size_commandes(commandes);
	if (size > 1)
	{
		while (tmp)
		{
			if (!tmp->command)
			{
				ft_putstr_fd("minishell: syntax error\n", 2);
				return (NULL);
			}
			tmp = tmp->next;
		}
	}
	if (!fct_error_syntaxe(commandes))
		return (NULL);
	return (commandes);
}

t_command	*fct_error_syntaxe(t_command *commandes)
{
	t_command	*tmp;
	t_redirect	*redir_tmp;

	tmp = commandes;
	while (tmp)
	{
		redir_tmp = tmp->redirect;
		while (redir_tmp)
		{
			if (!redir_tmp->dst_name
				|| (redir_tmp->is_heredoc && !redir_tmp->here_doc_eof))
			{
				ft_putstr_fd("minishell: syntax error\n", 2);
				return (NULL);
			}
			redir_tmp = redir_tmp->next;
		}
		tmp = tmp->next;
	}
	return (commandes);
}

char	**ft_words_to_array(t_word *l)
{
	char	**ret;

	ret = ft_calloc(1, sizeof(char *));
	while (l)
	{
		ret = dptr_join_ptr(ret, ft_strdup(l->str));
		l = l->next;
	}
	return (ret);
}
