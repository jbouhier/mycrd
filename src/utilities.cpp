#include <stdio.h>
#include <string.h>
#include "../include/LinkedHashMap.hpp"

void my_putchar (char c)
{
	std::cout << c;
}

void my_putNotFound ()
{
	std::cout << "-1\n";
}

int my_putstr(char *str)
{
  while (*str != 0)
    {
      my_putchar(*str);
      str++;
    }
  my_putchar('\n');
  return (0);
}

char *my_strcat (char *str1, char *str2)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (str1[i] != 0)
    {
      i++;
    }
  while (str2[j] != 0)
    {
      str1[i] = str2[j];
      i++;
      j++;
    }
  str1[i] = str2[j];
  return str1;
}

void add_cmd(LinkedHashMap **all_datas, char *key, char *value)
{
	(**all_datas).add_data(key, value);
	my_putstr(key);
}

void delete_cmd(LinkedHashMap **all_datas, char *key)
{
	char	*value;

	value = NULL;
	if ((**all_datas).delete_key(key, &value))
		my_putstr(value);
	else
		my_putNotFound();
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
			my_putstr(value);
		else
			my_putNotFound();
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
	printf("add_cmd            %s		and value %s\n", key, value);
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
