/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:39:33 by abouchfa          #+#    #+#             */
/*   Updated: 2022/03/28 23:22:35 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (!*needle)
		return ((char *) haystack);
	while (*haystack && len--)
	{
		i = 0;
		while (needle[i] == haystack[i] && i <= len)
		{
			if (!needle[i + 1])
				return ((char *) haystack);
			i++;
		}
		haystack++;
	}
	return (NULL);
}
