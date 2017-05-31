#include "string_pool.h"
#include <string.h>

unsigned int StrHashTable::Hash(const char *str)
{
	unsigned int h = 0;
	size_t l = strlen(str);
	size_t step = (l >> 5) + 1;
	for (; l >= step; l -= step)
		h ^= ((h << 5) + (h >> 2) + str[l - 1]);
	return h;
}

StrNode* StrHashTable::CreateStrNode(int l)
{
	size_t tl = l + 1 + sizeof(StrNode);
	void* pD = new char[tl];
	memset(pD,0,tl);

	StrNode* pN = (StrNode*)pD;
	pN->len = l;
	return pN;
}
char* StrHashTable::GetStr(const StrNode* pN)
{
	return ((char*)pN) + sizeof(StrNode);
}

StrNode* StrHashTable::FindStr(const char *str)
{
	unsigned int h = Hash(str);
	StrNode** list = &hash[h%len];
	for (StrNode* ts = *list; ts != nullptr; ts = ts->next)
	{
		if (strcmp(GetStr(ts), str) == 0)
		{
			return ts;
		}
	}
	if (use > len)
	{
		Resize(2 * len);
		list = &hash[h%len];
	}
	StrNode* pN = CreateStrNode(strlen(str));
	strcpy(GetStr(pN), str);
	pN->next = *list;
	*list = pN;
	use++;
	return pN;
}
