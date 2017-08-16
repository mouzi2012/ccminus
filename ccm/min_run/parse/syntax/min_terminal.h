#ifndef MIN_TERMINAL_H
#define MIN_TERMINAL_H

#include <list>
using std::list;
#include <string>
using std::string;
#include<set>
using std::set;

#include "min_token.h"


class MinNTerminal;
struct MinSymBlock
{
	enum class ESymType{EEmpty,EToken,ENTerminal};
	ESymType t;
	union {
		MinNTerminal* pMinNT;
		MinTokenRecord* pMinT;
	}data;
};

class MinNTerminal
{
public:
	MinNTerminal();
	void AddListSymBlock(list<MinSymBlock>& lb);
	void SetName(const string& n);
	const string& GetName();
	bool HasEmpty();
	const set<MinTokenRecord*>& GetFirstSet(MinNTerminal* pR);
	const set<MinTokenRecord*>& GetFollowSet(MinNTerminal* pR);
	void AddFollowSet(MinTokenRecord* r);
private:
	string m_n;
	list<list<MinSymBlock>> m_ts;
	set<MinTokenRecord*> m_first;
	set<MinTokenRecord*> m_follow;
};

#endif