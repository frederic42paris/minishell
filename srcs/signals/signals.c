/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:19:25 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/24 18:26:44 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_not_blocking(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sigint_blocking_cmd(int signal)
{
	if (signal == SIGINT)
		ft_putchar_fd('\n', 1);

}

void	sigquit(int signal)
{
	if (signal == SIGQUIT)
		ft_putchar_fd('\n', 1);
}

void	disable_signal(void)
{
	signal(SIGINT, sigint_not_blocking);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	enable_signal(void)
{
	signal(SIGINT, sigint_blocking_cmd);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, sigquit);
	signal(SIGTSTP, SIG_DFL);
}
