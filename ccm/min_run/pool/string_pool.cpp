#include "string_pool.h"
#include <string.h>
#include <stdlib.h>

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
	void* pD = malloc(tl);
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
	pN->h = h;
	*list = pN;
	use++;
	return pN;
}

void StrHashTable::Resize(int l)
{
	if (l > len)
	{
		//StrNode** list = malloc(sizeof(StrNode*)*l);
		void* pD = malloc(sizeof(StrNode*)*l);
		memset(pD, 0, sizeof(StrNode*)*l);
		StrNode** list = (StrNode** )pD;
		for (int i = 0; i < len; ++ i)
		{
			StrNode* p = hash[i];
			hash[i] = nullptr;
			while (p)
			{
				StrNode* next = p->next;
				unsigned int h = p->h % l;
				p->next = list[h];
				list[h] = p;
				p = next;
			}
		}
		free(hash);
		hash = list;
		len = l;
	}
	//not handle memory reduce !!!
}

void	StrHashTable::Clean()
{
	for (int i = 0; i < len; ++i)
	{
		StrNode* p = hash[i];
		hash[i] = nullptr;
		while (p)
		{
			StrNode* next = p->next;
			free(p);
			p = next;
		}
	}
	free(hash);

}

void StrHashTable::RemoveStr(const char *str)
{
	//not need yet
}
