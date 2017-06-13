#ifndef MIN_SYNTAX_H
#define MIN_SYNTAX_H
#include "../../pool/string_pool.h"
enum EMinTokenType{ENum,EID};
struct MinTokenRecord
{
	EMinTokenType k;
	StrNode* pn;	//the name if num the num string val
	int	  i;		//simple just int num~
};
MinTokenRecord getToken();
#endif
