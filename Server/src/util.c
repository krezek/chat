#include <stdlib.h>
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
