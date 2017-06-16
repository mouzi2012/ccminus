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
	virtual void	RemoveStr(const char *str) = 0;
	virtual void	Resize(int l) = 0;
	virtual void	Clean() = 0;
};
#endif
