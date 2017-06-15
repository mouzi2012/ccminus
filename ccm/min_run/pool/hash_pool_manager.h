#ifndef HASH_POOL_MANAGER_h
#define HASH_POOL_MANAGER_h
#include<string>
#include<map>
using std::string;
using std::map;
#include "../../min_common/singleton.h"

class HashTable;
class HashPoolManager:public Singleton<HashPoolManager>
{
public:
	friend Singleton<HashPoolManager>;
	HashTable* GetTable(const string& key);
protected:
	HashPoolManager();
	~HashPoolManager();
	HashPoolManager& operator=(const HashPoolManager&){};
private:
	map<string,HashTable*> m_pool;
};

#endif
