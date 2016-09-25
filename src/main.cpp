#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/extract.hpp"
#include "../include/parser.hpp"
#include "../include/LinkedHashMap.hpp"
#include "../include/utilities.hpp"

int		main(void)
{
	char			*str;
	char			**cmd_val;
	int				nb_words;
	LinkedHashMap	*all_datas;

	all_datas = new LinkedHashMap();

	if (isatty(fileno(stdin)))
	{
		printf("Error: stdin is a terminal. Expected File or Pipe.\n");
		return (1);
	}
	
	puts("--------- start --------\n");

	while ((str = read_line(0)))
	{
		if (*str)
		{
			printf("Line: %s\n", str);
			cmd_val = str_to_wtb(str, &nb_words);
			init(&all_datas, cmd_val, nb_words);
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
