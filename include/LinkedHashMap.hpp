#ifndef LINKEDHASHMAP_HPP
# define LINKEDHASHMAP_HPP

#include <iostream>

#define HASHSIZE 50000


typedef struct		s_data
{
	char			*key;
	char			*value;
	struct s_data	*next;
	struct s_data	*prev;
}					t_data;


class LinkedHashMap
{
	public:
		t_data		**_hashtab;
		t_data		*_dictionnary;

		LinkedHashMap();
		~LinkedHashMap();

		bool	add_data(char *key, char *value);
		bool	delete_key(char *key, char **value);

		bool	find_value(char *key, char **value);

	private:
		unsigned int	hash(const char *s);
		t_data			*find_node_by_key(const char *s);
		bool			upsert(const char *key, const char *value);
		t_data			*create_new_node_with_key_and_value(const char *key, const char *value);
		t_data			*update_node_with_key_for_value(const char *key,const char *value);
		t_data			*install_new_node_in_hashtab(t_data *node, t_data *hashtab[HASHSIZE]);
};

#endif /* !LINKEDHASHMAP_HPP */
