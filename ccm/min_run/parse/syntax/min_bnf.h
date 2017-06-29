#ifndef MIN_BNF_H
#define MIN_BNF_H

#include<list>
using std::list;

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
	void ParseNTerminal();
private:
	MinSource* pS;
	multimap<string,string> m_bnf_map;
	map<string,MinNTerminal*> m_nt;
};
#endif