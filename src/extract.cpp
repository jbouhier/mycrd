#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#include "../include/extract.hpp"

static int	read_word(int fd, char *buffer, size_t const size)
{
	int		ret;

	if ((ret = (int)read(fd, buffer, size)) == -1)
		exit(EXIT_FAILURE);
	return (ret);
}

// Function resize puts the pointer on the next line and the resifines the size of the input
// This function is huge in performance because it loops through the huge input many times and not once
void	resize(char *str, int i, int *index)
{
	int		ind;

	ind = -1;
	while (++ind < (*index - i))
		str[ind] = str[i + ind];
	*index -= i;
}

// This function do the same as strndup and saves in a char* being malloc the string param
char	*my_strndup(char const *src, unsigned int i)
{
	char	*dest;

	dest = (char *)malloc(sizeof(*src) * (i + 1));
	strncpy(dest, src, i);
	return dest;
}

// This function is used to get the first lines of the input. it calls the resize file to alter the input content
char	*getnline(char *str, int *index, const int fd)
{
	int		i;
	char	*ret;

	i = 0;
	ret = 0;
	while (i < *index)
	{
		if (!str[i] || CHAR_IS_NEWLINE(*(str + i)))
		{
			ret = (char *)malloc((i + 1) * sizeof(*ret) + 1);
			ret = strncpy(ret, str, i);
			ret[i + 1] = '\0';
			resize(str, i + 1, index);
			return (ret);
		}
		i++;
	}
	if (i == *index && i != 0)
	{
		ret = my_strndup(str, i);
		resize(str, i, index);
		ret = strcat(ret, get_one_line(fd, index, str));
		return (ret);
	}
	return (0);
}

// This function construct all the input datas in a string variable before calling the getnline to have the first line input
char	*get_one_line(int fd, int *index, char *buff)
{
	char	*tmp;
	int		offset;

	tmp = getnline(buff, index, fd);
	offset = 1;
	while (tmp == 0 && offset > 0)
	{
		if ((*index) + READ_B > BUFFER)
			offset = read_word(fd, buff + (*index), BUFFER - (*index));
		else
			offset = read_word(fd, buff + (*index), READ_B);
		
		if (offset > 0)
			(*index) += offset;
		tmp = getnline(buff, index, fd);
	}

	if (offset == 0 && tmp == 0 && (*index) > 0)
	{
		tmp = my_strndup(buff, *index);
		(*index) = 0;
	}
	return (tmp);
}

char	*read_line(int fd)
{
	static int		index = 0;
	static char		buff[BUFFER + 1];

	if (fd == -1)
	{
		index = 0;
		buff[0] = 0;
	}
	else
		return (get_one_line(fd, &index, buff));
	
	return (0);
}
