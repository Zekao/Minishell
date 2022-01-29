/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 23:26:57 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/26 09:43:52 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check(char *cmd)
{
	int	res;

	res = 0;
	res = ft_strncmp(cmd, "./", 2);
	if (res == 0)
		return (res);
	res = ft_strcmp(cmd, """");
	return (res);
}

char	*absolute_path(char **cmd, char *path)
{
	char	**path_2;
	char	*bin;
	int		i;

	i = -1;
	if (!path)
		ft_out("minishell: No such file or directory\n", 127);
	if ((cmd[0][0]) != '/' && check(cmd[0]) != 0)
	{
		path_2 = path_value(path);
		while (path_2[++i])
		{	
			bin = ft_calloc(sizeof(char), (ft_strlen(path_2[i])
						+ ft_strlen(cmd[0]) + 2));
			if (!bin)
				return (ft_free_ret(path_2));
			bin = ft_strcat_multiple(bin, path_2[i], "/", cmd[0]);
			if (access(bin, X_OK) == 0)
				return (ft_free_ret2(path_2, bin));
			free(bin);
		}
		if (path_2)
			free_dptr(&path_2);
	}
	return (cmd[0]);
}
