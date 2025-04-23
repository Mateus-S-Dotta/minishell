/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:03:42 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/22 22:02:21 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include <fcntl.h>
#include <string.h>
#include <readline/readline.h>

#define ENV_NAME "env_tmp"


int	open_file(char *file_name)
{
	int		file_fd;

	file_fd = open(file_name, O_RDWR | O_CREAT, 0666);
	if (file_fd == -1)
	{
		printf("Error in open\n");
		return (1);
	}
	return (file_fd);
}

void	print_env(char **env)
{
	int		i;

	i = -1;
	if (!env)
		return ;
	while (env[++i])
		printf("%s\n", env[i]);
	return ;
}

char	**env_cpy_f(char **env)
{
	int		i;
	int		count;
	char	**new_env;
	char	*tmp_env;

	count = 0;
	while (env[count])
		count++;
	new_env = (char **)malloc((count + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = strdup(env[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

//export NEW=new_value
//export NEW
//export NEW=
void	ft_export (char **env, char *input)
{

}

int main(int argc, char **argv, char **env)
{
	int		f_fd;
	char	**env_cpy;
	char	*input;

	if (!env || !*env)
	{
		printf("Env error\n");
		return (1);
	}
	env_cpy = env_cpy_f(env);
	f_fd = open_file(ENV_NAME);
	while (1)
	{
		input = readline("[log]>");
		if (!input)
			break ;
		if (!strcmp(input, "env"))
			print_env(env_cpy);
		else if(!strcmp(input, "env"))
			ft_export(env_cpy, input);
		free (input);
	}
	if (input)
		free (input);
	free (env_cpy);
	return (0);
}