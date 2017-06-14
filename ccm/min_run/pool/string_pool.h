#ifndef STRING_POOL_H
#define STRING_POOL_H
// this is a hash string pool for the parse to find the dict table word
#include "hash_table.h"
class StrHashTable:public HashTable
{
public:
	StrHashTable()
	{
		hash = nullptr;
		len = 0;
		use = 0;
	}

	StrNode** hash;
	int	   len;
	int	   use;

	static char* GetStr(const StrNode* pN);
	static StrNode* CreateStrNode(int l);
	static unsigned int Hash(const char *str);

	StrNode* FindStr(const char *str);
	void	RemoveStr(const char *str);
	void	Resize(int l);
	void	Clean();
};
#endif