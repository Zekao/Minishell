/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 06:22:49 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/25 16:25:26 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	stop_heredoc(t_redirect *redir)
{
	char	*line;
	int		fd;

	fd = open(redir->dst_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return ;
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, redir->here_doc_eof))
		{
			close(fd);
			break ;
		}
		else
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
	}
}

void	ft_heredoc(t_command *commandes)
{
	t_redirect		*tmp;
	int				i;

	i = 0;
	while (commandes)
	{
		tmp = commandes->redirect;
		while (tmp)
		{
			if (tmp->here_doc_eof)
				stop_heredoc(tmp);
			tmp = tmp->next;
			i++;
		}
		commandes = commandes->next;
	}
}

// static void redir_stdin(int *i, char **cmd)
// {
// 	int fdo;

// 	if (cmd[*i + 1])
// 	{
// 		fdo = open(cmd[*i + 1], O_RDONLY);
// 		if (fdo == -1)
// 			ft_putstr_fd("File is not opened\n", 2);
// 		dup2(fdo, 0);
// 		close(fdo);
// 		(*i)++;
// 	}
// }

// static void redir_stdout(int *i, char **cmd)
// {
// 	int fdo;

// 	if (cmd[*i + 1])
// 	{
// 		fdo = open(cmd[*i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 		if (fdo == -1)
// 			ft_putstr_fd("File is not opened\n", 2);
// 		dup2(fdo, 1);
// 		close(fdo);
// 		(*i)++;
// 	}
// }

// static void dredir_stdout(int *i, char **cmd)
// {
// 	int fdo;

// 	if (cmd[*i + 1])
// 	{
// 		fdo = open(cmd[*i + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
// 		if (fdo == -1)
// 			ft_putstr_fd("File is not opened\n", 2);
// 		dup2(fdo, 1);
// 		close(fdo);
// 		(*i)++;
// 	}
// }

char	**ft_redir(t_redirect *redir, char **cmd)
{
	int	fd;

	while (redir)
	{
		if (redir->dst_name)
		{
			fd = open(redir->dst_name, redir->open_flag, 0644);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(redir->dst_name, 2);
				ft_putstr_fd(": ", 2);
				perror("");
				free_dptr(&cmd);
				return (NULL);
			}
			dup2(fd, redir->src_fd);
			close(fd);
		}
		redir = redir->next;
	}
	return (cmd);
}

/* On redirige le resultat de la commande dans le fichier.
	 = On redirige la sortie std vers le fichier 
	 pfd[0] -> extremité de lecture du tube
	 pfd[1] -> extremité d'écriture du tube
	 */