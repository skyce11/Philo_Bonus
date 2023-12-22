/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:54:18 by migonzal          #+#    #+#             */
/*   Updated: 2022/07/19 11:34:31 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_lstlast(t_philo *lst)
{
	if (!lst)
		return (0);
	while (lst -> right)
		lst = lst -> right;
	return (lst);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	last = ft_lstlast(*lst);
	last -> right = new;
}

t_philo	*ft_lstnew(int index)
{
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new -> index = index;
	new -> right = NULL;
	return (new);
}

void	ft_link_list(t_philo *lst_philo)
{
	t_philo	*aux;

	aux = lst_philo;
	while (aux)
	{
		if (aux -> right)
			aux -> right -> left = aux;
		else
		{
			lst_philo->left = aux;
			aux -> right = lst_philo;
			break ;
		}
		aux = aux -> right;
	}
}
