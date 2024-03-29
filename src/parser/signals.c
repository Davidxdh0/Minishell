/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 20:17:07 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/22 21:37:30 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

//flag 0 
// enable_ctrl_c_display();
// disable_ctrl_c_display();??
//ctrl + c new line exitcode = 1
//flag 1
// ctrl c in heredoc - new line exit code 1
//flag 2
// ctrl c in child - 130 en newline
//flag 3
// ctrl + \ in child Quit: 3  exitcode 131
//flag 4
// ctrl + \ in heredoc - niets
// ctrl + \ - niets
void	sig_controller(int flag)
{
	if (flag == 0)
		signal(SIGINT, siginthandler);
	if (flag == 1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, siginthandlerheredoc);
	}
	if (flag == 2)
	{
		signal(SIGQUIT, signal_bs);
		signal(SIGINT, signal_bs);
	}
	if (flag == 3)
		signal(SIGQUIT, signal_bs);
}

void	siginthandler(int sig)
{
	g_exitcode = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	sig++;
}

void	siginthandlerheredoc(int sig)
{
	rl_replace_line("Press enter to continue...", 0);
	g_exitcode = 1000;
	rl_on_new_line();
	rl_redisplay();
	sig++;
}

void	signal_bs(int sig)
{
	sig++;
}

	// if (flag == 2)
	// 	signal(SIGINT, siginthandlerchild);
	// if (flag == 3)
	// 	signal(SIGQUIT, signal_bs);
	// if (flag == 4)
	// {
	// 	signal(SIGQUIT, signal_bs1);
	// }
	// if (flag == 5)
	// {
	// 	signal(SIGQUIT, signal_bs1);
	// 	signal(SIGINT, signal_bs1);
	// }