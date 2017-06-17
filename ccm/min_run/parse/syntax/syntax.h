#ifndef MIN_SYNTAX_H
#define MIN_SYNTAX_H
#include "../../pool/string_pool.h"

enum EMinTokenType{ EEmpt,ENum, EID, EAnnotate,EErrorTrace };
enum ECharType{ EDigit, ELetter,ESLASH, ECharTypeEnd };

struct MinTokenRecord
{
	EMinTokenType k;
	StrNode* pn;	//the name if num the num string val
	int	  i;		//simple just int num~
};
class MinSource;

class MinToken
{
public:
	MinToken(MinSource* rhs);
public:
	MinTokenRecord GetToken(); // need change

public:
	static bool IsLetter(char c);
	static bool IsDigit(char c);
	static bool IsWhiteSpace(char c);
public:

	bool ReadChar(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record);
	bool GenRecord(char buf[256],int pos,MinTokenRecord& record);
	bool HandleSlash(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record);
	bool HandleLetter(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record);
	bool handleDigit(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record);
private:
	MinToken& operator=(MinToken& rhs);
private:
	MinSource* pS;
};

#endif
