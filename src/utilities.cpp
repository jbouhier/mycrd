#include <stdio.h>
#include <string.h>
#include "../include/LinkedHashMap.hpp"

void add_cmd(LinkedHashMap **all_datas, char *key, char *value)
{
	(**all_datas).add_data(key, value);
	printf("%s\n", key);
}

void delete_cmd(LinkedHashMap **all_datas, char *key)
{
	char	*value;

	value = NULL;
	if ((**all_datas).delete_key(key, &value))
		printf("%s\n", value);
	else
		printf("%d\n", -1);
}

void init(LinkedHashMap **all_datas, char **cmd_val, int nb_words)
{
	char	*key;
	char	*value;

	key = cmd_val[0];
	value = cmd_val[1];
	if (nb_words == 1)
	{
		if ((**all_datas).find_value(key, &value))
		{
			// This part is wrong on Debian
			printf("test %s\n", value);
		}
		else
			printf("%d\n", -1);
	}
	else
	{
		if (!strcmp(cmd_val[1], "D"))
			delete_cmd(all_datas, key);
		else
			add_cmd(all_datas, key, value);
	}
}

void debug_add_cmd(LinkedHashMap **all_datas, char *key, char *value)
{
	(**all_datas).add_data(key, value);
	printf("add_cmd            %s\n", key);
}

void debug_delete_cmd(LinkedHashMap **all_datas, char *key)
{
	char	*value;

	value = NULL;
	if ((**all_datas).delete_key(key, &value))
		printf("delete_cmd found    %s\n", value);
	else
		printf("delete_cmd nothing %d\n", -1);
}

void debug_init(LinkedHashMap **all_datas, char **cmd_val, int nb_words)
{
	char	*key;
	char	*value;

	key = cmd_val[0];
	value = cmd_val[1];
	if (nb_words == 1)
	{
		if ((**all_datas).find_value(key, &value))
			printf("init find_value     %s\n", value);
		else
			printf("init no value      %d\n", -1);
	}
	else
	{
		if (!strcmp(cmd_val[1], "D"))
			debug_delete_cmd(all_datas, key);
		else
			debug_add_cmd(all_datas, key, value);
	}
}