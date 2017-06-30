#ifndef MIN_BNF_H
#define MIN_BNF_H

#include<list>
using std::list;

#include<map>
using std::multimap;
using std::map;

#include<string>
using std::string;

class MinNTerminal;
class MinSource;
class MinBNF
{
public:
	MinBNF(MinSource* rhs);
	void GetBNFMap();
	void PrintBNFMap();
	void ParseNTerminal();

private:
	MinSource* pS;
	multimap<string,list<string>> m_bnf_map;
	map<string,MinNTerminal*> m_nt;
};
#endif