/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 10:35:14 by abarteld      #+#    #+#                 */
/*   Updated: 2023/05/04 10:35:15 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

// cant start with a number
// cant have special characters
// += (dont need to handle)

bool	export_characters(char c, bool start)
{
	if (start == true)
	{
		if (!(c == '_') && !(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z'))
			return (false);
	}
	else if (!(c == '_') && !(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z') \
			&& !(c >= '0' && c <= '9'))
		return (false);
	return (true);
}

static char	*ft_export_validation(char *cmd) //change for error status
{
	int		i;
	char	*str;

	if (!export_characters(cmd[0], true))
		return (printf("minishell: export: `%s': not a valid identifier\n"
				, cmd), NULL);
	i = 1;
	while (cmd[i])
	{
		if (cmd[i] == '=')
		{
			str = ft_substr(cmd, 0, i); //prots
			// if (!str)
			// 	ft_exit_error("Malloc Failed", errno);
			printf("Export Target: %s\n", str);
			return (str);
		}
		if (!export_characters(cmd[i], false))
			return (printf("minishell: export: `%s': not a valid identifier\n"
					, cmd), NULL);
		i++;
	}
	return (NULL);
}

bool	export_targeted(char *cmd, char *target, t_envp *envp)
{
	int		len;

	if (target)
	{
		while (envp)
		{
			if (!ft_strcmp(target, envp->identifier))
			{
				free(envp->line);
				free(envp->string);
				envp->line = ft_strdup(cmd); //prots
				if (!envp->value)
					envp->value = check_envp_value(envp->line);
				envp->string = ft_substr(envp->line, envp->value + 1 \
				, ft_strlen(envp->line) - (envp->value + 1)); //prots
		printf("Envp #%d Line =\t%s\n", 666, envp->line);
		printf("Envp #%d ID =\t%s\n", 666, envp->identifier);
		printf("Envp #%d Str =\t%s\n", 666, envp->string);
				return (true);
			}
			envp = envp->next;
		}
	}
	return (false);
}

void	ft_export_cmd(char *cmd, char *target, t_envp *envp, int fd)
{
	t_envp	*hd;
	t_envp	*new;

	if (export_targeted(cmd, target, envp))
		return ;
	hd = envp;
	if (!target)
	{
		while (envp)
		{
			if (!ft_strcmp(cmd, envp->identifier))
				return ;
			envp = envp->next;
		}
	}
	new = ft_malloc(sizeof(t_envp));
	new->head = hd;
	new->prev = hd;
	new->next = hd->next;
	new->line = ft_strdup(cmd); // prots
	new->value = check_envp_value(new->line);
	if (new->value)
	{
		new->identifier = ft_substr(new->line, 0, new->value); //prots
		new->string = ft_substr(new->line, new->value + 1\
		, ft_strlen(new->line) - (new->value + 1)); //prots
		printf("Envp #%d Line =\t%s\n", 117, new->line);
		printf("Envp #%d ID =\t%s\n", 117, new->identifier);
		printf("Envp #%d Str =\t%s\n", 117, new->string);
	}
	else
	{
		new->identifier = ft_strdup(new->line); //prots
		new->string = NULL;
	}
	hd->next->prev = new;
	hd->next = new;
}

	// target, not present (make new)
	// target, present (free and set new string)
	// no target, present (keep old)
	// no target, not present (make new)

void	ft_export_argless(t_execute *cmd_struct, t_envp *envp, int fd)
{
	//sort?
	while (envp)
	{
		write(fd, "declare -x ", 11); 
		if (envp->value)
		{
			write(fd, envp->identifier, ft_strlen(envp->identifier));
			write(fd, "=\"", 2);
			write(fd, envp->string, ft_strlen(envp->string));
			write(fd, "\"\n", 2);
		}
		else
		{
			write(fd, envp->line, ft_strlen(envp->line));
			write(fd, "\n", 1);
		}
		envp = envp->next;
	}
}

void	ft_export(t_execute *cmd_struct, t_envp *envp, int fd)
{
	int		i;
	char	*target;

printf("Entered Export\n");
	if (!cmd_struct->cmd[1])
		ft_export_argless(cmd_struct, envp, fd);
	else
	{
		i = 1;
		while (cmd_struct->cmd[i])
		{
			target = ft_export_validation(cmd_struct->cmd[i]); // change for error states
			ft_export_cmd(cmd_struct->cmd[i], target, envp, fd);
			i++;
		}
	}
printf("Exiting Export\n");
}

	// int		i;

	// if (target)
	// {
	// 	ft_getenv_int(&i, target, envp);
	// 	free(target);
	// 	if (i >= 0)
	// 	{
	// 		envp[i] = ft_strdup(cmd); //prots
	// 		// if (!envp[i])
	// 		// 	ft_exit_error("Malloc Failed", errno);
	// 		return ;
	// 	}
	// }
	// i = 0;
	// while (envp[i])
	// 	i++;
	// envp[i] = ft_strdup(cmd);
	// if (!envp[i])
	// 	ft_exit_error("Malloc Failed", errno);
	// envp[i + 1] = NULL;