/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:18:52 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/21 17:55:40 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static void	print_env(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
		printf("[i]: %d | [ENV]: %s\n", i, env[i]);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	size;
	unsigned int	aux;
	char			*c;

	aux = -1;
	size = 0;
	while (s1[++aux])
		size++;
	aux = -1;
	while (s2[++aux])
		size++;
	c = (char *)malloc((size + 1) * sizeof(char));
	if (!c)
		return (NULL);
	aux = -1;
	c[size] = '\0';
	while (s1[++aux])
		c[aux] = s1[aux];
	size = 0;
	while (s2[size])
		c[aux++] = s2[size++];
	return (c);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*c;

	i = 0;
	c = (char *)s;
	while (c[i])
		i++;
	c = (char *)malloc((i + 1) * sizeof(char));
	if (c == NULL)
		return (NULL);
	c[i] = '\0';
	while (i--)
		c[i] = s[i];
	return (c);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*c;

	i = 0;
	while (s[i] && i < n)
		i++;
	c = (char *)malloc((i + 1) * sizeof(char));
	if (c == NULL)
		return (NULL);
	c[i] = '\0';
	while (i--)
		c[i] = s[i];
	return (c);
}

static int	change_value(char **env, char *field, char *new_value_field)
{
	int		i;
	char	*tmp_env;
	char	*new_str;
	char	*tmp_new_str;
	
	i = -1;
	if (!new_value_field)
	{
		printf("Invalid value to change field");
		return (0);
	}
	while (env[++i])
	{
		if (strncmp(field, env[i], strlen(field)) == 0 && env[i][strlen(field)] == '=')
		{
			tmp_env = env[i];
			new_str = ft_strndup(env[i], strlen(field) + 1);
			tmp_new_str = new_str;
			new_str = ft_strjoin(tmp_new_str, new_value_field);
			free(tmp_new_str);
			if (!new_str)
				return (0);
			env[i] = new_str;
			free(tmp_env);
			return (1);
		}
	}
	printf("Field not found\n");
	return (0);
}

static char *take_field_value(char **env, char *field)
{
	int		i;
	int		fl_s;
	char	*field_value;

	i = -1;
	field_value = NULL;
	fl_s = strlen(field);
	while (env[++i])
	{
		if (strncmp(env[i], field, fl_s) == 0 && env[i][fl_s] == '=')
		{
			field_value = (char *)malloc(sizeof(char) * strlen(&env[i][fl_s + 1]) + 1);
			if (!field_value)
			{
				perror ("Malloc error\n");
				return (NULL);
			}
			strcpy(field_value, &env[i][fl_s + 1]);
			return (field_value);
		}
	}
	printf("Field not found\n");
	return (NULL);
}

static char	**copy_env(char **env)
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
		new_env[i] = ft_strdup(env[i]);
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

void clean_env_cpy(char **env)
{
	int		i;

	i = -1;
	if (!env || !*env)
		return ;
	while (env[++i])
		free(env[i]);
	free(env);
	return ;
}

int main(int argc, char **argv, char **env)
{
	char	*str_field = "BATATATATATATATATATATATATATA";
	char	**cpy_env = copy_env(env);
	char	*old_str_field;
	char	*new_str_field;

	old_str_field = take_field_value(cpy_env, "HOME");
	if (!old_str_field)
		return (-1);
	printf("OLD value from field HOME: %s\n", old_str_field);
	// print_env(cpy_env);
	if(!change_value(cpy_env, "HOME", str_field))
	{
		printf("Error in change value\n");
		return (-1);
	}
	// print_env(cpy_env);
	new_str_field = take_field_value(cpy_env, "HOME");
	printf("NEW value from field HOME: %s\n", new_str_field);
	free(new_str_field);
	free(old_str_field);
	clean_env_cpy(cpy_env);
	return (0);
}
