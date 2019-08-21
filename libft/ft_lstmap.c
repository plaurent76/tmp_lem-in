/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 18:48:51 by plaurent          #+#    #+#             */
/*   Updated: 2019/05/29 18:48:53 by plaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*flst;
	t_list	*newlst;

	if (lst && f)
	{
		newlst = f(lst);
		flst = newlst;
		while (lst->next)
		{
			lst = lst->next;
			if (!(newlst->next = ft_lstnew(f(lst)->content,
							f(lst)->content_size)))
				return (NULL);
			newlst = newlst->next;
		}
		return (flst);
	}
	return (NULL);
}
