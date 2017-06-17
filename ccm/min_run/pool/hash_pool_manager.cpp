#include "hash_pool_manager.h"
#include "string_pool.h"
HashPoolManager::HashPoolManager()
{
}
HashPoolManager::~HashPoolManager()
{
	for (auto& p : m_pool)
	{
		delete p.second;
	}
}
HashTable* HashPoolManager::GetTable(const string &key)
{
	auto iter = m_pool.find(key);
	if(iter != m_pool.end())
	{
		return iter->second;
	}
	if(key == "StrHashTable")
	{
		StrHashTable* pt = new StrHashTable;
		pt->Resize(256);

	
		m_pool["StrHashTable"] = pt;
	}
	return m_pool[key];
}
