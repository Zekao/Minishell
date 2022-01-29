/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:14:38 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/27 01:57:48 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

char	*ft_strcat_multiple(char *dest, char *a, char *b, char *c)
{
	dest = ft_strcat(dest, a);
	dest = ft_strcat(dest, b);
	dest = ft_strcat(dest, c);
	return (dest);
}

int	ft_find_line(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' &&
			env[i][3] == 'H' && env[i][4] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	exec_cmd_2(char **cmd, char *path_env)
{
	if (!ft_strchr(cmd[0], '/'))
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else
		perror(cmd[0]);
	free(path_env);
	return (127);
}

int	exec_cmd_3(char **cmd, char *path_env, char *new_cmd)
{
	perror(cmd[0]);
	if (!ft_strcmp(cmd[0], "..") || !ft_strcmp(cmd[0], ".")
		|| !ft_strncmp(cmd[0], "../", 3))
		free_two_elem(new_cmd, path_env);
	else
		free(path_env);
	return (126);
}

int	exec_cmd(char **cmd, char **env, int sortie)
{
	pid_t	pid;
	char	*path_env;
	char	pwd[2048];
	int		ret;

	getcwd(pwd, 2048);
	ret = 0;
	path_env = ft_get_line_p(env);
	if (!path_env)
		exit(127);
	pid = fork();
	signal_manager2();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		ret = child_process(cmd, env, path_env, sortie);
		return (-1);
	}
	if (path_env)
		free(path_env);
	(void)ret;
	return (256);
}
