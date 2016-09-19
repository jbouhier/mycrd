#include "../include/parser.hpp"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

# define CHAR_IS_WHITE(c)		(c == '\t' || c == ' ')
# define CHAR_NOT_WHITE(c)		(c != '\t' && c != ' ')

static char	*skip_whitechar(char *s)
{
	while (*s && CHAR_IS_WHITE(*s))
		s++;
	return (s);
}

static char		*skip_word(char *s)
{
	while (*s && CHAR_NOT_WHITE(*s))
		s++;
	return (s);
}

static int		count_word_len(char *s)
{
	char	*p;

	p = s;
	while (*s && CHAR_NOT_WHITE(*s))
		s++;
	return ((int)((long)s - (long)p));
}

static int	count_words(char *s)
{
	int		nb_words;

	nb_words = 0;
	while (*s)
	{
		s = skip_whitechar(s);
		if (*s)
		{
			nb_words++;
			s = skip_word(s);
		}
	}
	return (nb_words);
}

static char		*my_strndup(char *src, int len)
{
	int		i;
	char	*dest;

	dest = (char *)malloc(sizeof(*src) * (len + 1));
	for (i = 0; i < len; ++i)
		dest[i] = src[i];
	dest[i] = 0;
	return (dest);
}

static char		*get_next_word(char **src)
{
	char	*ret;
	int		len;

	*src = skip_whitechar(*src);

	len = count_word_len(*src);
	if (len)
	{
		ret = my_strndup(*src, len);
		*src = *src + len;
		return (ret);
	}
	return (0);
}

void	free_cmd(char **wtb)
{
	int i;

	i = 0;
	while (wtb[i])
	{
		free(wtb[i]);
		i++;
	}
	free(wtb[i]);
	free(wtb);
}

char		**str_to_wtb(char *src, int *nb_words)
{
	char	**wtb;
	char	*str;
	int		i;

	wtb = 0;
	i = 0;
	*nb_words = count_words(src);
	wtb = (char **)malloc(sizeof(*wtb) * (*nb_words + sizeof(*wtb)));
	while ((str = get_next_word(&src)))
		wtb[i++] = str;
	wtb[i] = 0;
	return (wtb);
}

