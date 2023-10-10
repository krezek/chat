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

Node* Node_init(const wchar_t* k, void* v, Node* l, Node* r);
void Node_free(Node* n);

#endif /* _UTIL_H_ */
