#ifndef HASH_POOL_MANAGER_h
#define HASH_POOL_MANAGER_h
class HashPoolManager
{
public:
	static HashPoolManager* Instance();
	static void Release();
private:
	HashPoolManager();
	static HashPoolManager *m_pInstance;
};
#endif