/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:09:13 by msalaibb          #+#    #+#             */
/*   Updated: 2025/05/02 19:22:45 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	pipe_node(t_cmds *cmds, t_cmds *cmds2, int *p_fd)
{
	char	**cmd_w;

	if (cmds2 != NULL)
		redirect(p_fd[1], 1, cmds);
	else
		redirect(get_t_min()->out_fd, 1, cmds);
	close_all(p_fd[0], p_fd[1]);
	cmd_w = unify_flags(cmds);
	if (!cmds->cmd)
		exit (get_t_min()->sig);
	if (is_builtins(cmds->cmd, 7))
		exec_builtins(cmds);
	else
		if (execve(cmds->path, cmd_w, get_t_min()->env) == -1)
		{
			free_split(get_t_min()->env);
			new_error(cmd_w);
		}
	free_all(NULL, get_t_min()->sig);
	// exit (get_t_min()->sig);
}

static int	heredoc_counter(t_cmds *cmds)
{
	int		i;
	t_flags	*tmp_flag;

	i = 0;
	tmp_flag = cmds->flags;
	if (ft_strncmp(cmds->cmd, "<<", 2) == 0)
		i++;
	while (tmp_flag)
	{
		if (ft_strncmp(tmp_flag->flag, "<<", 2) == 0)
			i++;
		tmp_flag = tmp_flag->next;
	}
	return (i);
}

static int	pipe_comand(t_cmds *cmds, t_cmds *cmds2)
{
	int		p_fd[2];
	int		qnd_hd;
	pid_t	process;

	qnd_hd = heredoc_counter(cmds);
	if (!qnd_hd)
		set_std_cmd();
	else
		signal(SIGINT, SIG_IGN);
	if (pipe(p_fd) == -1)
		return (-1);
	if (is_builtins(cmds->cmd, 2) == 1)
	{
		if (get_t_min()->pipe_cnt == 1)
			exec_builtins(cmds);
		return (super_close(p_fd[0], p_fd[1], 0, qnd_hd), 0);
	}
	process = fork();
	if (process == 0)
		pipe_node(cmds, cmds2, p_fd);
	else
		super_close(p_fd[0], p_fd[1], 0, qnd_hd);
	return (process);
}

void	copy_verify(t_cmds *cmds, t_cmds *new_cmds, char **cmd_w, int d)
{
	int	i;
	int	type;

	i = -1;
	while (cmd_w[++i + d] != NULL && ft_strncmp(cmd_w[i + d], "|", 1) != 0)
	{
		type = unify(i + d - 1, cmd_w);
		if (new_flag(new_cmds, cmd_w[i + d], type) == 0)
		{
			free_split(cmd_w);
			free_all("Malloc Error", 1);
		}
	}
	if (get_t_min()->cmds == NULL)
		get_t_min()->cmds = new_cmds;
	else
		cmds->next = new_cmds;
	if (cmd_w[i + d] != NULL && ft_strncmp(cmd_w[i + d], "|", 1) == 0
		&& cmd_w[i + d + 1] != NULL
		&& ft_strncmp(cmd_w[i + d + 1], "|", 1) != 0)
		create_cmds(new_cmds, cmd_w, d + i + 1);
	else if (cmd_w[i + d] != NULL && ft_strncmp(cmd_w[i + d], "|", 1) == 0)
		free_all("Invalid pipe compare\n", 1);
}

void	normal_comand(char *cmd)
{
	char	**cmd_w;
	t_cmds	*cmds;
	int		i;

	i = -1;
	cmd_w = super_ft_split(cmd);
	create_cmds(get_t_min()->cmds, cmd_w, 0);
	free_split(cmd_w);
	count_pipe();
	cmds = get_t_min()->cmds;
	while (cmds != NULL)
	{
		(get_t_min()->prc_pid[++i]) = (pid_t)pipe_comand(cmds, cmds->next);
		cmds = cmds->next;
	}
}
