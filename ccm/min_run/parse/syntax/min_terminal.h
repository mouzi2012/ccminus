#ifndef MIN_TERMINAL_H
#define MIN_TERMINAL_H

#include <list>
using std::list;
#include <string>
using std::string;

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
private:
	string m_n;
	list<list<MinSymBlock>> m_ts;
};

#endif