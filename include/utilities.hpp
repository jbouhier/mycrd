#ifndef UTILITIES_HPP
# define UTILITIES_HPP

void	add_cmd(LinkedHashMap **all_datas, char *key, char *value);
void	delete_cmd(LinkedHashMap **all_datas, char *key);
void	init(LinkedHashMap **all_datas, char **cmd_val, int nb_words);

#endif /* !UTILITIES_HPP */