#ifndef MIN_SYNTAX_H
#define MIN_SYNTAX_H
#include "../../pool/string_pool.h"
#include "../../min_source.h"

enum EMinTokenType{ EEmpt,ENum, EID, EAnnotate,EErrorTrace };
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
	MinTokenRecord GetToken(); // need change

public:
	static bool IsLetter(char c);
	static bool IsDigit(char c);
	static bool IsWhiteSpace(char c);
	static bool HandleStateChange(ECharType o, ECharType n );

	static bool HandleChar(char o, char c);
	// not finish yet
	static bool ReadChar(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record);
	static bool GenRecord(char buf[256],int pos,MinTokenRecord& record);
	static bool HandleSlash(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record);
	static bool HandleLetter(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record);
	static bool handleDigit(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record);
private:
	MinToken& operator=(MinToken& rhs);
private:
	MinSource* pS;
};

#endif
