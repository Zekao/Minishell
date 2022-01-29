/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouquet <mbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:55:20 by mbouquet          #+#    #+#             */
/*   Updated: 2022/01/26 12:11:44 by mbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_with_file(struct dirent *file, char ***tri, DIR *rep)
{
	while (file)
	{
		if (ft_strcmp(file->d_name, ".") && ft_strcmp(file->d_name, "..")
			&& file->d_name[0] != '.')
			*tri = dptr_join_ptr(*tri, ft_strdup(file->d_name));
		file = readdir(rep);
	}
}

static char	*ft_reverse(char *str)
{
	int		i;
	char	tmp;
	int		size;

	i = 0;
	size = ft_strlen(str);
	while (i < (size / 2))
	{
		tmp = str[i];
		str[i] = str[size - i - 1];
		str[size - i - 1] = tmp;
		i++;
	}
	return (str);
}

static void	fill_with_rfile(struct dirent *file, char ***tri, DIR *rep, char *p)
{
	char	*r_prefixe;
	char	*r_file;

	r_prefixe = ft_reverse(p);
	while (file)
	{
		r_file = ft_reverse(file->d_name);
		if (!ft_strncmp(r_file, r_prefixe, ft_strlen(p)))
			*tri = dptr_join_ptr(*tri, ft_strdup(ft_reverse(r_file)));
		file = readdir(rep);
	}
}

void	lettres_wildcard(char **p, struct dirent *file, char ***tri, DIR *rep)
{
	while (file)
	{
		if (!ft_strncmp(file->d_name, *p, ft_strlen(*p)))
			*tri = dptr_join_ptr(*tri, ft_strdup(file->d_name));
		file = readdir(rep);
	}
}

char	**wildcard_with_letters(char *cmd, DIR *rep)
{
	t_varb	var;

	var.tri = ft_calloc(1, sizeof(char *));
	var.file = readdir(rep);
	if (!ft_strcmp(cmd, "*"))
		fill_with_file(var.file, &var.tri, rep);
	else
	{
		var.place = ft_strchr(cmd, '*');
		if (var.place != cmd)
		{
			var.prefixe = ft_substr(cmd, 0, var.place - cmd);
			lettres_wildcard(&var.prefixe, var.file, &var.tri, rep);
		}
		else
		{
			var.prefixe = ft_substr(cmd, 1, var.place - (cmd + 1));
			fill_with_rfile(var.file, &var.tri, rep, var.prefixe);
		}
		free(var.prefixe);
	}
	var.tmp = var.tri;
	var.tri = ascii_sort(var.tri);
	free_dptr(&var.tmp);
	return (var.tri);
}
