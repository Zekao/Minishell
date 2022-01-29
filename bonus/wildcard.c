/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouquet <mbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:58:03 by mbouquet          #+#    #+#             */
/*   Updated: 2022/01/26 12:22:35 by mbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill(char *cmd, char *dir, char **tmp, DIR **rep)
{
	*tmp = NULL;
	if (dir)
	{
		*rep = opendir(dir);
		*tmp = my_strjoin(*tmp, cmd + ft_strlen(dir));
	}
	else
	{
		*rep = opendir(".");
		*tmp = my_strjoin(*tmp, cmd);
	}
}

static void	wildcard_without_dossier(char ***ret, char *cmd, int *j, char *dir)
{
	DIR		*rep;
	char	**tri;
	char	*tmp;

	fill(cmd, dir, &tmp, &rep);
	if (!rep || !tmp)
		return ;
	else
	{
		tri = wildcard_with_letters(tmp, rep);
		free(tmp);
		while ((tri)[*j])
		{
			if (dir)
			{
				tmp = ft_strjoin(dir, tri[*j]);
				*ret = dptr_join_ptr(*ret, tmp);
			}
			else
				*ret = dptr_join_ptr(*ret, ft_strdup(tri[*j]));
			(*j)++;
		}
		free_dptr(&tri);
	}
	closedir(rep);
}

static void	fct_wildcard(char *cmd, char ***ret, int *j)
{
	char	*dir;

	dir = recup_dir(cmd);
	wildcard_without_dossier(ret, cmd, j, dir);
	free(dir);
	if (*j != 0)
		free(cmd);
	else
		*ret = dptr_join_ptr(*ret, cmd);
}

char	**ft_wildcard(char **cmd)
{
	int		i;
	char	**ret;
	int		j;

	ret = ft_calloc(1, sizeof(char *));
	if (!ret)
		return (cmd);
	i = 0;
	while (cmd[i])
	{
		j = 0;
		if (ft_strchr(cmd[i], '*'))
			fct_wildcard(cmd[i], &ret, &j);
		else
			ret = dptr_join_ptr(ret, cmd[i]);
		i++;
	}
	free(cmd);
	return (ret);
}

char	*recup_dir(char *cmd)
{
	char	*dir;
	char	*ret;

	ret = NULL;
	dir = ft_strnstr(cmd, "/*", ft_strlen(cmd));
	if (dir)
		ret = ft_substr(cmd, 0, (dir - cmd) + 1);
	return (ret);
}
