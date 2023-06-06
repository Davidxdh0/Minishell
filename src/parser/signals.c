/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 20:17:07 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/06 15:14:34 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <termios.h>

// off voor fork command executer
void disable_ctrl_c_display()
{
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
//voor shell en na wifexit
void enable_ctrl_c_display()
{
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	redirect_signal(int signal)
{
	if (signal == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}
// Ctrl-C pressedin cat ^C laten zien, heredoc: > en nieuw line
void signal_int(int signal)
{

    if (signal == SIGINT)
    {
		g_exitcode = 1;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
    }
}
// Ctrl-C pressedin cat ^C laten zien, heredoc: > en nieuw line
void signal_int_heredoc(int signal)
{

    if (signal == SIGINT)
		exit(1);
}
// niet in heredoc - // Ctrl-\ pressed
void	signal_bs(int signal)
{
    if (signal == SIGQUIT)
    {
        printf("^\\Quit: 3\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
    }
}
	// else if (WIFSIGNALED(status) == true)
	// {
	// 	int exit_status;
	
	// 	exit_status = WTERMSIG(status);
	// 	if (exit_status == 2)
	// 		g_exitcode = 130;
	// 	else if (exit_status == 3)
	// 	{
	// 		g_exitcode = 131;
	// 		write(2, "Quit: 3", 8);
	// 	}
	// 	write(2, "\n", 2);
	// }
