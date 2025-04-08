/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:09:13 by msalaibb          #+#    #+#             */
/*   Updated: 2025/04/07 21:49:48 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void pipe_node(t_cmds *cmds, t_cmds *cmds2, int *p_fd)
{
	char	**cmd_w;

	if (cmds2 != NULL)
		redirect(p_fd[1], 1, cmds);
	else
		redirect(get_t_min()->out_fd, 1, cmds);
	close_all(p_fd[0], p_fd[1]);
	cmd_w = unify_flags(cmds);
	if (cmds->path != NULL)
		execve(cmds->path, cmd_w, get_t_min()->env);
	new_error(cmd_w);
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
	if (pipe(p_fd) == -1)
		return (-1);
	process = fork();
	sig_cmd();
	if (process == -1)
		return (-1);
	if (process == 0)
		pipe_node(cmds, cmds2, p_fd);
	else
		super_close(p_fd[0], p_fd[1], 0, qnd_hd);
	return (process);
}

static void	copy_verify(t_cmds *cmds, t_cmds *new_cmds, char **cmd_w, int d)
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
		free_all("Palindromo\n", 1);
}

void	free_normal_comand(t_cmds *new_cmds, char **cmd_w)
{
	t_flags	*flags;
	t_flags	*temp;

	if (new_cmds == NULL)
		return ;
	flags = new_cmds->flags;
	while (flags != NULL)
	{
		temp = flags->next;
		if (flags->flag != NULL)
			free(flags->flag);
		free(flags);
	}
	if (new_cmds->cmd != NULL)
		free(new_cmds->cmd);
	if (new_cmds->path != NULL)
		free(new_cmds->path);
	free_split(cmd_w);
	free_all("Comand Not Found\n", 1);
}

void	create_cmds(t_cmds *cmds, char **cmd_w, int d)
{
	int		i;
	t_cmds	*new_cmds;

	if (ft_strncmp(cmd_w[d], "|", 1) == 0)
	{
		free_split(cmd_w);
		free_all("Start Pipe\n", 1);
	}
	i = 0;
	while (cmd_w[i + d] != NULL && ft_strncmp(cmd_w[i + d], "|", 1) != 0)
		i++;
	new_cmds = (t_cmds *)malloc(sizeof(t_cmds));
	if (new_cmds == NULL)
		exit_error_minishell("Malloc Error\n", 1);
	new_cmds->quote = unify(d - 1, cmd_w);
	new_cmds->cmd = ft_strdup(cmd_w[d]);
	if (new_cmds->cmd == NULL)
		free_normal_comand(new_cmds, cmd_w);
	new_cmds->path = NULL;
	new_cmds->next = NULL;
	new_cmds->flags = NULL;
	copy_verify(cmds, new_cmds, cmd_w, d + 1);
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
	cmds = get_t_min()->cmds;
	print_cmds();
	while (cmds != NULL)
	{
		(get_t_min()->prc_pid[++i]) = (pid_t)pipe_comand(cmds, cmds->next);
		cmds = cmds->next;
	}
}
