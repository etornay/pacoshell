/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:19:31 by etornay-          #+#    #+#             */
/*   Updated: 2024/02/05 18:59:44 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_unset(t_paco *p, char *name)
{
	t_env	*aux;
	t_env	*del;
	t_env	*prev;

	if (!name)
		return ;
	aux = p->l_env;
	prev = NULL;
	while (aux != NULL)
	{
		if (!ft_strncmp(aux->name, name, ft_strlen(name)))
		{
			del = aux;
			if (prev)
				prev->next_env = aux->next_env;
			else
				p->l_env = aux->next_env;
			free(del->name);
			free(del->content);
			free(del);
			break ;
		}
		prev = aux;
		aux = aux->next_env;
	}
}

void	pwd(t_paco *p)
{
	char	dir[500];

	p->act_dir = getcwd(dir, 500);
	if (p->act_dir == NULL)
		return ;
	ft_printf("%s\n", p->act_dir);
}