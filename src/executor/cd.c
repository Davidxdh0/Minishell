/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 11:51:52 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/11/09 14:54:54 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

/*
int chdir(const char *path); 	
Used to change the current working directory.
On some systems, this command is used as an alias for the shell command cd. 
chdir changes the current working directory of the calling process to the directory
specified in path.
*/

/* char *getcwd(char *buf, size_t size); 	
Gets the path name of the current working directory. 
If a buffer is specified, the path name is placed in that buffer,
and the address of the buffer is returned. 
Otherwise, 
getcwd() allocates space for the path name and returns a pointer to that buffer. 
In that instance, the user is responsible for deleting the storage when it is 
no longer needed by calling free() with the pointer returned by getcwd(). 
Copies an absolute pathname of the current working directory to the array 
pointed to by buf, which is of length size.
*/
void	update_old_pwd(t_line_lst *stack, char *oldpath)
{
	
}

void	cd_home(t_line_lst *stack, char **cmd)
{

}

int		check_valid_path(t_line_lst *stack, char *path)
{

}

void	change_dir(t_line_lst *stack, char *path)
{
	
}

void	execute_cd(t_line_lst *stack, char **cmd)
{
	char 	*cwd;
	char 	*path;
	char 	*oldpath;
	int		status;
	
	status = 0;
	oldpath = getwd(NULL);
	if (cmd[1] == NULL || (cmd[1][0] == '~' && cmd[1][1] == '\0'))
		;//ga home directory en change old pwd
	else if (cmd[1][0] == '.' && cmd[1][1] == '\0')
		;//update_old_pwd
	else if (cmd[1][0] == '.' && cmd[1][1] == '.')
		;//check if valid -> remove last word from cwd en chdir, update oldpwd
	else
		status = change_dir();//check if valid dir en change (if not valid return 1)
	if (status == 0)
		;// change oldpwd
	// message(cwd);
	// path = ft_strjoin(cwd, "/obj");
	// message(path);
	// chdir(path);
	// message(cwd);
	// stack++;
}