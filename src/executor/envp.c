/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 15:50:49 by abarteld      #+#    #+#                 */
/*   Updated: 2023/05/18 15:50:52 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

char	**envp_to_array(t_envp *envp)
{
	char	**envp_array;
	int		i;

	i = 1;
	while (envp->next)
	{
		envp = envp->next;
		i++;
	}
	envp = envp->head;
	envp_array = ft_malloc(sizeof(char *) * (i + 1));
	envp_array[i + 1] = NULL;
	i = 0;
	while (envp)
	{
		envp_array[i] = envp->line;
		envp = envp->next;
		i++;
	}
	return (envp_array);
}

int	check_envp_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

void	sort_envp(t_envp *envp) //for printing export argless
{
	while (envp)
	{

	}
}

void	increase_shlvl(t_envp *envp)
{
	char	*tmp;
	int		atoi; //technically need a seperate ft_atoi to reset SHLVL
	
	while (envp)
	{
		if (!ft_strcmp("SHLVL", envp->identifier))
		{
			// printf("Shell Level Alteration\n");
			tmp = envp->string;
			atoi = ft_atoi(envp->string); //
			envp->string = ft_itoa(atoi + 1); //prots
			free(tmp);
			free(envp->line);
			envp->line = ft_strjoin("SHLVL=", envp->string);
			// printf("NEW SHELL = %s\n", envp->line);
			return ;
		}
		envp = envp->next; 
	}
	// add SHLVL from scratch
}

t_envp	*copy_envp(char **original_envp)
{
	int		i;
	t_envp	*envp;
	t_envp	*tmp;

	envp = ft_malloc(sizeof(t_envp));
	envp->head = envp;
	envp->line = ft_strdup(original_envp[0]); // prots
	envp->value = check_envp_value(envp->line);
	if (envp->value)
	{
		envp->identifier = ft_substr(envp->line, 0, envp->value); //prots
		envp->string = ft_substr(envp->line, envp->value + 1 \
		, ft_strlen(envp->line) - (envp->value + 1)); //prots
	}
	else
	{
		envp->identifier = ft_strdup(envp->line); //prots
		envp->string = NULL;
	}
	envp->prev = NULL;
	i = 1;
	while (original_envp[i])
	{
		// printf("Envp #%d Line =\t%s\n", i, envp->line);
		// printf("Envp #%d ID =\t%s\n", i, envp->identifier);
		// printf("Envp #%d Str =\t%s\n", i, envp->string);
		tmp = envp;
		envp->next = ft_malloc(sizeof(t_envp));
		envp = envp->next;
		envp->head = tmp->head;
		envp->line = ft_strdup(original_envp[i]); // prots
		envp->value = check_envp_value(envp->line);
		if (envp->value)
		{
			envp->identifier = ft_substr(envp->line, 0, envp->value); //prots
			envp->string = ft_substr(envp->line, envp->value + 1 \
			, ft_strlen(envp->line) - (envp->value + 1)); //prots
		}
		else
		{
			envp->identifier = ft_strdup(envp->line); //prots
			envp->string = NULL;
		}
		envp->prev = tmp;
		i++;
	}
	// printf("Envp Str = %s\n", envp->string);
	envp->next = NULL;
	increase_shlvl(envp->head);
	return (envp->head);
}
