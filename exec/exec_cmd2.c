/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 23:24:19 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/26 08:55:11 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	child_process(char **cmd, char **env, char *path_env, int sortie)
{
	char	pwd[2048];
	char	*new_cmd;

	getcwd(pwd, 2048);
	if (ft_builtin(cmd, env, pwd, path_env) != -1)
		return (g_exit_code);
	else
	{
		if (sortie != -1)
			close(sortie);
		new_cmd = absolute_path(cmd, path_env);
		execve(new_cmd, cmd, env);
		ft_putstr_fd("minishell: ", 2);
		if (errno == ENOENT)
			return (exec_cmd_2(cmd, path_env));
		if (errno == EACCES)
			return (exec_cmd_3(cmd, path_env, new_cmd));
		return (free(path_env), perror(cmd[0]), -1);
	}
	return (-1);
}

static int	ft_builtin_2(char **cmd, char **env, char *path_env)
{
	char	**export;

	export = ft_export(&cmd[1], env, size_double_ptr(env));
	if (export)
	{
		free_dptr(&env);
		env = export;
		free_two_dptr(&export, &env);
	}
	return (free(path_env), g_exit_code);
}

int	ft_builtin(char **cmd, char **env, char *pwd, char *path_env)
{
	if (check_cmp(cmd[0], "cd"))
		return (free(path_env), ft_cd(cmd, env, pwd));
	else if (check_cmp(cmd[0], "pwd"))
		return (free(path_env), ft_pwd(pwd));
	else if (check_cmp(cmd[0], "env"))
		return (free(path_env), ft_env(env, cmd, 2));
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_putstr_fd("exit\n", 1);
	else if (check_cmp(cmd[0], "unset"))
	{
		env = ft_unset(env, &cmd[1]);
		if (!env)
			ft_putstr_fd("Erreur fonction unset\n", 2);
		return (free(path_env), g_exit_code);
	}
	else if (check_cmp(cmd[0], "export"))
		return (ft_builtin_2(cmd, env, path_env));
	else if (check_cmp(cmd[0], "echo"))
		return (free(path_env), ft_echo(&cmd[1], env));
	return (-1);
}

char	*ft_get_line_p(char **env)
{
	char	*str;
	int		i;

	i = ft_find_line(env);
	str = ft_strdup(env[i]);
	return (str);
}

char	**path_value(char *path)
{
	char	**path_2;

	if (ft_strchr(path, '='))
		path_2 = ft_split(ft_strchr(path, '=') + 1, ':');
	else
		path_2 = ft_split(path, ':');
	return (path_2);
}
