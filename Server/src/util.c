#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "util.h"


Node* Node_init(const wchar_t* k, void* v, Node* l, Node* r)
{
	Node* n = (Node*)malloc(sizeof(Node));
	assert(n != NULL);

	n->_key = (wchar_t*)malloc((wcslen(k) + 1) * sizeof(wchar_t));
	assert(n->_key != NULL);
	wcscpy_s(n->_key, wcslen(k) + 1, k);

	n->_value = v;
	n->_left = l;
	n->_right = r;

	return n;
}

void Node_free(Node* n)
{
	if (n->_key)
		free(n->_key);

	free(n);
}

Map* Map_init()
{
	Map* m = (Map*)malloc(sizeof(Map));
	assert(m != NULL);

	m->_root = NULL;

	return m;
}

void Map_free(Map* m)
{
	free(m);
}

void Map_insert_n(Node** pn, const wchar_t* k, void* v)
{
	if (*pn == NULL)
	{
		*pn = Node_init(k, v, NULL, NULL);
	}
	else
	{
		if (wcscmp((*pn)->_key, k) > 0)
		{
			Map_insert_n(&((*pn)->_left), k, v);
		}
		else if (wcscmp((*pn)->_key, k) < 0)
		{
			Map_insert_n(&((*pn)->_right), k, v);
		}
		else
		{
			printf("Map_insert_n: error\n");
		}
	}
}

void Map_insert(Map* m, const wchar_t* k, void* v)
{
	Map_insert_n(&m->_root, k, v);
}

void* Map_get_n(Node** pn, const wchar_t* k)
{
	if (*pn == NULL)
		return NULL;

	if (wcscmp((*pn)->_key, k) == 0)
		return (*pn)->_value;
	else if (wcscmp((*pn)->_key, k) > 0)
		return Map_get_n(&((*pn)->_left), k);
	else
		return Map_get_n(&((*pn)->_right), k);
}

void* Map_get(Map* m, const wchar_t* k)
{
	return Map_get_n(&m->_root, k);
}