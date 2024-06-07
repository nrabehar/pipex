/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:42:12 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/08 22:24:21 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
	Count the words in a string to allocate the exact size of the split array.
	This function tests if the current character being iterated in `str` is
	not equal to the separator character `c`.
	If true,it increments the `count` and consumes all characters of
	the current word to find the next word.
	Return the `count` of words in `str`.
*/

size_t	ft_words_count(char const *str, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

/*
	Get the next index of the next word by adding the `start` index and
	the length `len` of the current word. If the character at the `start`
	index of `str` is equal to the separator `c`,then increment `start`
	to the next word, as it is not part of the current word.
	Get the exact length of the word by checking from the `start`
	index of `str` up to the next occurrence of `c`.
*/

static size_t	ft_get_next_id(char const *str, char c, size_t start)
{
	size_t	len;

	len = 0;
	while (str[start] && str[start] == c)
		start++;
	len = 0;
	while (str[start + len] && str[start + len] != c)
		len++;
	return (start + len);
}

/*
	Get the word. Use the same process as the `ft_get_next_id` function
	to obtain the exact `start` index and the `len`.
	Use the `start` index and the `len` to extract a substring from `str`,
	starting at the `start` index and with a length of `len`,
	using the `ft_substr` function.
*/

static char	*ft_get_word(char const *str, char c, size_t start)
{
	size_t	len;
	char	*word;

	while (str[start] && str[start] == c)
		start++;
	len = 0;
	while (str[start + len] && str[start + len] != c)
		len++;
	word = ft_substr(str, start, len);
	if (!word)
		return (NULL);
	return (word);
}

/* Free all when occure any problem */

static void	*ft_free_all(char **splitted, size_t last_id)
{
	size_t	i;

	i = 0;
	while (i < last_id)
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
	splitted = NULL;
	return (NULL);
}
/*
	get all word in `s` splitted by `c`.
*/

char	**ft_split(char const *s, char c)
{
	size_t	size;
	size_t	i;
	size_t	w_id;
	char	**splitted;

	if (!s)
		return (NULL);
	size = ft_words_count(s, c);
	splitted = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!splitted)
		return (NULL);
	splitted[size] = NULL;
	i = 0;
	w_id = 0;
	while (i < size)
	{
		splitted[i] = ft_get_word(s, c, w_id);
		if (!splitted[i])
			return (ft_free_all(splitted, i));
		w_id = ft_get_next_id(s, c, w_id);
		i++;
	}
	return (splitted);
}
