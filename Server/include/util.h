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

Map* Map_init();
void Map_free(Map* m);
void Map_insert(Map* m, const wchar_t* k, void* v);
void* Map_get(Map* m, const wchar_t* k);
void Map_remove(Map* m, const wchar_t* k);
void Map_traversal(Map* m);

#endif /* _UTIL_H_ */
