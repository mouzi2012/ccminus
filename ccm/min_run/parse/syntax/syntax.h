#ifndef MIN_SYNTAX_H
#define MIN_SYNTAX_H

enum ETokenKind{ENum,EName};
struct MinToken
{
	ETokenKind k;
	char* name;
};

#endif