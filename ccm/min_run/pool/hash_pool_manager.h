#ifndef HASH_POOL_MANAGER_h
#define HASH_POOL_MANAGER_h
#include<string>
#include<map>
using std::string;
using std::map;
#include "../../../min_common/singleton.h"
class HashPoolManager:Singleton<HashPoolManager>
{
public:
	friend Singleton<HashPoolManger>;
	HashTable* GetTable(const string& key);
protected:
	HashPoolManager();
	~HashPoolManager();
	HashPoolManager& operator=(const HashPoolManager&){};
private:
	map<string,HashTable*> m_pool;
};

#endif
