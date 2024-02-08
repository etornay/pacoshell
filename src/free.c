/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:18:17 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/08 14:49:51 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_paco *p)
{
	free_lex(p);
	ft_env_clear(&p->l_env);
	free(p);
}

void	free_path(t_paco *p)
{
	int	i;

	i = 0;
	if (p->path != NULL)
	{
		while (p->path[i])
			free(p->path[i++]);
		free(p->path);
	}
}

void	free_lex(t_paco *p)
{
	int	i;

	i = 0;
	if (p->lex != NULL)
	{
		while (p->lex[i])
			free(p->lex[i++]);
		free(p->lex);
	}
}

void	ft_lstdel_env(t_env *lst)
{
	if (!lst)
		return ;
	free(lst->name);
	lst->index = 0;
	free(lst->content);
	free(lst);
	lst = NULL;
}

void	ft_env_clear(t_env **lst)
{
	t_env	*aux;

	if (!*lst)
		return ;
	while (*lst)
	{
		aux = (*lst)->next_env;
		ft_lstdel_env(*lst);
		*lst = aux;
	}
	*lst = NULL;
}
