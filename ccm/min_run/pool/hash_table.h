#ifndef MIN_HASH_TABLE_H
#define MIN_HASH_TABLE_H


struct StrNode
{
	StrNode()
	{
		next = nullptr;
		len = 0;
		h = 0;
	}
	StrNode* next;
	unsigned int h;
	int len;
};

class HashTable
{
public:
	virtual StrNode* FindStr(const char *str) = 0;
}
#endif