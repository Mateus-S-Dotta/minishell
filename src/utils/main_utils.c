/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:21:51 by msalaibb          #+#    #+#             */
/*   Updated: 2025/05/11 00:39:07 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_new_error(char **cmd, char *message, int cod)
{
	if (dup2(get_t_min()->out_fd, 1) == -1)
		free_all("Dup2 Error\n", 1);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(message, 2);
	free_all(NULL, -1);
	close_all(get_t_min()->out_fd, get_t_min()->in_fd);
	free(cmd);
	exit(cod);
}

void	new_error(char **cmd)
{
	struct stat	statbuf;

	if (cmd[0] == NULL)
		return (free(cmd), free_all("Unexpected Error\n", 1));
	if (cmd[0][0] != '.' && cmd[0][0] != '/')
		print_new_error(cmd, ": command not found\n", 127);
	if (access(cmd[0], F_OK) == -1)
		print_new_error(cmd, ": No such file or directory\n", 127);
	if (access(cmd[0], X_OK) == -1)
		print_new_error(cmd, ": Permission denied\n", 126);
	if (stat(cmd[0], &statbuf) == -1)
		return (free(cmd), free_all("Verify Archive Error\n", 1));
	if (S_ISDIR(statbuf.st_mode) || cmd[0][0] == '/')
		print_new_error(cmd, ": Is a directory\n", 126);
	free_all("Unexpected Error\n", 1);
}

int	verify_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0' && ((input[i] >= 7
				&& input[i] <= 13) || input[i] == 32))
		i++;
	if (input[i] == '\0')
		return (1);
	return (0);
}

void	wait_last_status(void)
{
	int		i;
	t_min	*env;
	int		status;

	i = -1;
	env = get_t_min();
	status = -1;
	while (env->prc_pid[++i])
	{
		waitpid (env->prc_pid[i], &status, 0);
		if (WIFEXITED(status))
			env->sig = WEXITSTATUS(status);
	}
	while (i--)
		env->prc_pid[i] = 0;
}

char	**copy_env(char *env[])
{
	int		i;
	char	**env_cpy;

	env_cpy = (char **)malloc(sizeof(char *) * 1024);
	if (!env_cpy)
		return (NULL);
	i = 0;
	while (env[i] && i < 1023)
	{
		env_cpy[i] = strdup(env[i]);
		if (!env_cpy[i])
		{
			while (i > 0)
				free(env_cpy[--i]);
			free(env_cpy);
			return (NULL);
		}
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}
