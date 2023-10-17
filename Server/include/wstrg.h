#ifndef _WSTRG_H_
#define _WSTRG_H_

#define EXPAND 100

typedef struct
{
	wchar_t* _str;
	size_t _len;
	size_t _capacity;
	size_t _index;
} WString;

WString* String_init();
void String_free(WString* s);
void String_cpy(WString* s, const wchar_t* ws);
void String_cat(WString* s, const wchar_t* ws);
void String_insert_s(WString* s, size_t idx, const wchar_t* ws);
void String_insert_c(WString* s, size_t idx, const wchar_t ch);
void String_delete_s(WString* s, size_t idx1, size_t idx2);
void String_delete_c(WString* s, size_t idx);

#endif /* _WSTRG_H_ */


