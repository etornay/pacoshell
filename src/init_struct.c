/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:01:33 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/01/30 18:04:56 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_paco *p)
{
	p->shell = NULL;
	p->act_dir = NULL;
	p->aux = NULL;
	p->l_env = NULL;
	p->line = NULL;
	p->path = NULL;
	p->lex = NULL;
	p->i = 0;
	p->c = 0;
}
