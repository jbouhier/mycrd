#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/extract.hpp"
#include "include/parser.hpp"
#include "include/LinkedHashMap.hpp"

LinkedHashMap		*all_datas;


void add_cmd(char *key, char *value)
{
	all_datas->add_data(key, value);
	puts(key);
}

void delete_cmd(char *key)
{
	char	*value;

	if (all_datas->delete_key(key, &value))
		puts(value);
	else
		puts("-1");
}

void init(char **cmd_val, int nb_words)
{
	char	*key;
	char	*value;

	key = cmd_val[0];
	value = cmd_val[1];
	if (nb_words == 1)
	{
		if (all_datas->find_value(key, &value))
			puts(value);
		else
		{
			puts ("nothing found");
			puts("-1");
		}
	}
	else
	{
		if (!strcmp(cmd_val[1], "D"))
			delete_cmd(key);
		else
			add_cmd(key, value);
	}
}



int		main(void)
{
	char			*str;
	char			**cmd_val;
	int				nb_words;
	LinkedHashMap	*all_datas;

	all_datas = new LinkedHashMap();
	if (!isatty(fileno(stdin))) // Check if stdin is a terminal / tty
	{
		printf("Error: stdin is a terminal. File or a pipe expected\n");
		return (1);
	}
		
	// Read stdin (Pipe or file)
	while ((str = read_line(0)))
	{
		if (*str)
		{
			cmd_val = str_to_wtb(str, &nb_words);
			init(cmd_val, nb_words);
			free_cmd(cmd_val);
		}
		free(str);
		str = NULL;
	}

	while (all_datas->_dictionnary != NULL) 
	{
		printf("key  : %s => value : %s\n", all_datas->_dictionnary->key, all_datas->_dictionnary->value);
		all_datas->_dictionnary = all_datas->_dictionnary->next;
	}
	
	delete (all_datas);
	return (0);
}
