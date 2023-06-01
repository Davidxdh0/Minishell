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

void	show_envp_node(t_envp *envp)
{
	if (envp)
		printf("Line: %s\nIdentifier: %s\tString: %s\n", envp->line, envp->identifier, envp->string);
}

void	show_envp_struct(t_envp *envp)
{
	int	i;

	i = 1;
	while (envp)
	{
		printf("Node #%d\nLine:\t\t%s\nIdentifier:\t%s\nString:\t\t%s\n\n", i, envp->line, envp->identifier, envp->string);
		envp = envp->next;
		i++;
	}
}

t_envp	*remove_envp_node(t_envp *node)
{
	t_envp	*head;

	head = NULL;
	if (node->prev)
		head = node->prev;
	else if (node->next)
		head = node->next;
	if (node)
	{
		if (node->next)
			node->next->prev = node->prev;
		if (node->prev)
			node->prev->next = node->next;
		free(node->line);
		free(node->identifier);
		free(node->string);
		free(node);
	}
	if (head)
		while (head->prev)
			head = head->prev;
	return (head);
}

char	**envp_to_array(t_envp *envp)
{
	char	**envp_array;
	t_envp	*head;
	int		i;

	if (!envp)
		return (NULL);
	head = envp;
	i = 1;
	while (envp->next)
	{
		envp = envp->next;
		i++;
	}
	envp_array = ft_malloc(sizeof(char *) * (i + 1));
	envp_array[i + 1] = NULL;
	i = 0;
	envp = head;
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

// void	sort_envp(t_envp *envp) //for printing export argless
// {
// 	while (envp)
// 	{

// 	}
// }


t_envp	*envp_start_list(char *str)
{
	t_envp	*envp;

 	envp = ft_malloc(sizeof(t_envp));
	envp->line = ft_strdup(str); // prots
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
	envp->next = NULL;
	return (envp);
}

void	envp_add_node(t_envp *envp, char *str)
{
	t_envp	*tmp;

	while (envp->next)
		envp = envp->next;
	envp->next = ft_malloc(sizeof(t_envp));
	tmp = envp;
	envp = envp->next;
	envp->line = ft_strdup(str); // prots
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
	envp->next = NULL;
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
	envp_add_node(envp, "SHLVL=1");
}

t_envp	*copy_envp(char **original_envp)
{
	int		i;
	t_envp	*envp;

	if (!original_envp)
		return (NULL);
	envp = envp_start_list(original_envp[0]); // possible error msg
	i = 1;
	while (original_envp[i])
	{
		envp_add_node(envp, original_envp[i]); // possible error msg
		i++;
	}
	increase_shlvl(envp);
	// show_envp_struct(envp);
	return (envp);
}

	// int		i;
	// t_envp	*envp;
	// t_envp	*tmp;

	// envp = ft_malloc(sizeof(t_envp));
	// // envp->head = envp;
	// envp->line = ft_strdup(original_envp[0]); // prots
	// envp->value = check_envp_value(envp->line);
	// if (envp->value)
	// {
	// 	envp->identifier = ft_substr(envp->line, 0, envp->value); //prots
	// 	envp->string = ft_substr(envp->line, envp->value + 1 \
	// 	, ft_strlen(envp->line) - (envp->value + 1)); //prots
	// }
	// else
	// {
	// 	envp->identifier = ft_strdup(envp->line); //prots
	// 	envp->string = NULL;
	// }
	// envp->prev = NULL;
	// i = 1;
	// while (original_envp[i])
	// {
	// 	tmp = envp;
	// 	envp->next = ft_malloc(sizeof(t_envp));
	// 	envp = envp->next;
	// 	// envp->head = tmp->head;
	// 	envp->line = ft_strdup(original_envp[i]); // prots
	// 	envp->value = check_envp_value(envp->line);
	// 	if (envp->value)
	// 	{
	// 		envp->identifier = ft_substr(envp->line, 0, envp->value); //prots
	// 		envp->string = ft_substr(envp->line, envp->value + 1 \
	// 		, ft_strlen(envp->line) - (envp->value + 1)); //prots
	// 	}
	// 	else
	// 	{
	// 		envp->identifier = ft_strdup(envp->line); //prots
	// 		envp->string = NULL;
	// 	}
	// 	envp->prev = tmp;
	// 	i++;
	// }
	// printf("Envp Str = %s\n", envp->string);
	// envp->next = NULL;
	// increase_shlvl(envp->head);
	// return (envp->head);
