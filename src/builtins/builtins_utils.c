/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:20:20 by etornay-          #+#    #+#             */
/*   Updated: 2024/02/05 09:04:22 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env_size(t_env *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next_env;
		size++;
	}
	return (size);
}
