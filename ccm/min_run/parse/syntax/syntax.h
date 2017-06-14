#ifndef MIN_SYNTAX_H
#define MIN_SYNTAX_H
#include "../../pool/string_pool.h"
#include "../../min_source.h"

enum EMinTokenType{ENum,EID,EErrorTrace};
enum ECharType{ EDigit, ELetter, ECharTypeEnd };

struct MinTokenRecord
{
	EMinTokenType k;
	StrNode* pn;	//the name if num the num string val
	int	  i;		//simple just int num~
};

class MinToken
{
public:
	MinToken(MinSource* rhs);
public:
	MinTokenRecord getToken();
public:
	static bool IsLetter(char c);
	static bool IsDigit(char c);
	static bool IsWhiteSpace(char c);
	static bool HandleStateChange(ECharType o, ECharType n );
private:
	MinToken& operator=(MinToken& rhs);
private:
	MinSource* pS;
};

#endif
