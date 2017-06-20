#ifndef MIN_SYNTAX_H
#define MIN_SYNTAX_H
#include "min_token.h"
class MinSyntaxParser
{
public:
	MinSyntaxParser();
	~MinSyntaxParser();
	void ParseSyntax();
	void Clear();
private:
	MinToken* pT;
	tree_node<MinTokenRecord>* pParseRoot;
}
#endif
