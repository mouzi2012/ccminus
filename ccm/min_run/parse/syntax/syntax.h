#ifndef MIN_SYNTAX_H
#define MIN_SYNTAX_H

enum EMinTokenType{ENum,EID};
struct MinTokenRecord
{
	EMinTokenType k;
	char* name;
	char* vale;
};
EMinTokenType getToken();
#endif