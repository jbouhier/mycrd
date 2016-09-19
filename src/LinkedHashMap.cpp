#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <exception>
#include <stdexcept>
#include "../include/LinkedHashMap.hpp"

LinkedHashMap::LinkedHashMap()
{
	this->_hashtab = (t_data **) malloc( sizeof(*_hashtab) * HASHSIZE );
	if (!this->_hashtab)
		throw 2323;
}

LinkedHashMap::~LinkedHashMap()
{
	t_data	*old;

	while (_dictionnary)
	{
		old = _dictionnary;
		free(_dictionnary->key);
		free(_dictionnary->value);
		_dictionnary = _dictionnary->next;
		free(old);
	}
}

bool	LinkedHashMap::add_data(char *key, char *value)
{
	return (this->upsert(key, value));
}

bool	LinkedHashMap::delete_key(char *key, char **value)
{
	t_data			*node;
	unsigned int	hashval;

	if (!(node = find_node_by_key(key)))
		return (false);

	hashval = hash(key);
	assert(_hashtab[hashval]);
	*value = _hashtab[hashval]->value;
	_hashtab[hashval] = NULL;
	return (true);
}

bool	LinkedHashMap::find_value(char *key, char **value)
{
	t_data	*node;

	if ((node = find_node_by_key(key)) == NULL)
	{
		return (false);
	}
	*value = node->value;
	return (true);
}

unsigned int	LinkedHashMap::hash(const char *s)
{
	unsigned hashval;

	for (hashval = 0; *s; ++s)
		hashval = *s + 31 * hashval;
	return (hashval % HASHSIZE);
}

t_data		*LinkedHashMap::find_node_by_key(const char *key)
{
	t_data *node;

	assert(this->_hashtab);
	assert(key);
	printf(" the key to find is %s\n", key);
	for (node = this->_hashtab[hash(key)]; node; node = node->next)
	{

		printf(" the key %s => %s\n", key, node->key);
		if (!strcmp(key, node->key))
		{
			return (node);
		}
	}
	return (NULL);
}

bool	LinkedHashMap::upsert(const char *key, const char *value)
{
	t_data	*node;
	bool	action_is_insert;

	assert(key);
	assert(value);
	action_is_insert = false;
	if (!(node = update_node_with_key_for_value(key, value)))
	{
		node = this->create_new_node_with_key_and_value(key, value);
		if (node)
		{
			this->install_new_node_in_hashtab(node, this->_hashtab);
			action_is_insert = true;
		}
	}
	return (action_is_insert);
}

t_data	*LinkedHashMap::create_new_node_with_key_and_value(const char *key, const char *value)
{
	t_data		*new_node;
	static int	i;

	if ((new_node = (t_data *)malloc(sizeof(*new_node))))
	{
		if (i++ == 0)
			_dictionnary = new_node;
		new_node->key = strdup(key);
		new_node->value = strdup(value);
		if (!new_node->key || !new_node->value)
			return (NULL);
		return (new_node);
	}
	return (NULL);
}

t_data	*LinkedHashMap::install_new_node_in_hashtab(t_data *node, t_data **hashtab)
{
	unsigned int	uniq_key;

	assert(hashtab);
	uniq_key = hash(node->key);
	node->next = hashtab[uniq_key];
	hashtab[uniq_key] = node;
	return (node);
}

t_data	*LinkedHashMap::update_node_with_key_for_value(const char *key,const char *value)
{
	t_data	*node;

	if (!(node = find_node_by_key(key)))
		return (NULL);
	assert(key);
	free(node->value);
	if (!(node->value = strdup(value)))
		return (NULL);
	return (node);
}