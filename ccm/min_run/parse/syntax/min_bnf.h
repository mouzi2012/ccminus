#ifndef MIN_BNF_H
#define MIN_BNF_H

#include<map>
using std::multimap;
#include<string>
using std::string;
class MinBNF
{
public:
	MinBNF(MinSource* rhs);
	void GetBNFMap();
	void PrintBNFMap();
private:
	MinSource* pS;
	multimap<string,string> m_bnf_map;
};
#endif