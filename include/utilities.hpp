#ifndef UTILITIES_HPP
# define UTILITIES_HPP

void	add_cmd(LinkedHashMap **all_datas, char *key, char *value);
void	delete_cmd(LinkedHashMap **all_datas, char *key);
void	init(LinkedHashMap **all_datas, char **cmd_val, int nb_words);
void	debug_add_cmd(LinkedHashMap **all_datas, char *key, char *value);
void	debug_delete_cmd(LinkedHashMap **all_datas, char *key);
void	debug_init(LinkedHashMap **all_datas, char **cmd_val, int nb_words);


using namespace std;

#endif /* !UTILITIES_HPP */
