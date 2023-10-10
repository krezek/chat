#ifndef _UTIL_H_
#define _UTIL_H_

#include <wchar.h>

typedef struct _Node
{
	wchar_t* _key;
	void* _value;

	struct _Node* _left;
	struct _Node* _right;

} Node;

typedef struct _Map
{
	Node* _root;
} Map;

//Node* Node_init(const wchar_t* k, void* v, Node* l, Node* r);
//void Node_free(Node* n);

Map* Map_init();
void Map_free(Map* m);
void Map_insert(Map* m, const wchar_t* k, void* v);
void* Map_get(Map* m, const wchar_t* k);

#endif /* _UTIL_H_ */
