#ifndef MIN_SYNTAX_H
#define MIN_SYNTAX_H
#include "../../pool/string_pool.h"
#include "../../min_source.h"

enum EMinTokenType{ ENum, EID, ECOMMIT,EErrorTrace };
enum ECharType{ EDigit, ELetter,ESLASH, ECharTypeEnd };

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
	MinTokenRecord getToken(); // need change
public:
	static bool IsLetter(char c);
	static bool IsDigit(char c);
	static bool IsWhiteSpace(char c);
	static bool HandleStateChange(ECharType o, ECharType n );

	static bool HandleChar(char o, char c);
	// not finish yet
	static bool HandleSlash();
	static bool HandleLetter();
	static bool handleDigit();
private:
	MinToken& operator=(MinToken& rhs);
private:
	MinSource* pS;
};

#endif
