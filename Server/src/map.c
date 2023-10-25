#include "platform.h"

#include "map.h"


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

void Node_free(Node* n, MValueFree freeFunc)
{
	if (n->_key)
		free(n->_key);

	if (n->_value)
		freeFunc(n->_value);

	free(n);
}

Map* Map_init()
{
	Map* m = (Map*)malloc(sizeof(Map));
	assert(m != NULL);

	m->_root = NULL;

	return m;
}

void Map_free(Map* m, MValueFree freeFunc)
{
	Map_remove_all(m, freeFunc);
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

void Map_remove_n(Node** pn, const wchar_t* k, MValueFree freeFunc)
{
	if (*pn == NULL)
		return;

	if (wcscmp((*pn)->_key, k) == 0)
	{
		if ((*pn)->_left == NULL &&
			(*pn)->_right == NULL)
		{
			Node_free(*pn, freeFunc);
			*pn = NULL;
		}
		else if ((*pn)->_right == NULL)
		{
			Node* temp = *pn;
			*pn = (*pn)->_left;
			temp->_left = NULL;
			Node_free((temp), freeFunc);
		}
		else if ((*pn)->_left == NULL)
		{
			Node* temp = *pn;
			*pn = (*pn)->_right;
			temp->_right = NULL;
			Node_free((temp), freeFunc);
		}
		else
		{
			Node** cur = &(*pn)->_right;

			while ((*cur)->_left)
				cur = &(*cur)->_left;

			free((*pn)->_key);
			freeFunc((*pn)->_value);

			(*pn)->_key = (wchar_t*)malloc((wcslen((*cur)->_key) + 1) * sizeof(wchar_t));
			assert((*pn)->_key != NULL);
			wcscpy_s((*pn)->_key, wcslen((*cur)->_key) + 1, (*cur)->_key);
			
			(*pn)->_value = (*cur)->_value;
			(*cur)->_value = NULL;
			
			Map_remove_n(cur, (*cur)->_key, freeFunc);
		}
	}
	else if (wcscmp((*pn)->_key, k) > 0)
		Map_remove_n(&((*pn)->_left), k, freeFunc);
	else
		Map_remove_n(&((*pn)->_right), k, freeFunc);
}

void Map_remove(Map* m, const wchar_t* k, MValueFree freeFunc)
{
	Map_remove_n(&m->_root, k, freeFunc);
}

void Map_traversal_n(Node* node) {
	if (node != NULL) 
	{
		Map_traversal_n(node->_left);
		printf("(%S, %llx) ", node->_key, (long long)node->_value);
		Map_traversal_n(node->_right);
	}
}

void Map_traversal(Map* m)
{
	Map_traversal_n(m->_root);
	printf("\n");
}

void Map_remove_all_n(Node* node, MValueFree freeFunc)
{
	if (node == NULL)
		return;

	Map_remove_all_n(node->_left, freeFunc);
	Map_remove_all_n(node->_right, freeFunc);

	Node_free(node, freeFunc);
}

void Map_remove_all(Map* m, MValueFree freeFunc)
{
	Map_remove_all_n(m->_root, freeFunc);
}
