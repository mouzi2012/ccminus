#ifndef MIN_SYNTAX_H
#define MIN_SYNTAX_H
#include "../../pool/string_pool.h"

enum EMinTokenType
{ 
	EEmpty,
	ENum, 
	EID,
	//the key word
	EIF,
	EELSE,
	EINT,
	ERETURN,
	EVOID,
	EWHILE,
	//the special word
	EPLUS,
	EMINUS,
	EMULTI,
	EDIV,
	EL,
	ELEQ,
	EG,
	EGEQ,
	EEQ,
	ENEQ,
	EASIGN,
	ESEM,
	ECOMMA,
	ELBRAC,
	ERBRAC,
	ELINDEX,
	ERINDEX,
	ELBLOCK,
	ERBLOCK,
	//special word end
   	ETEnd,
	EErrorTrace
};
enum ECharType{ EDigit, ELetter,ESLASH, ECharTypeEnd };

struct MinTokenRecord
{
	EMinTokenType k;
	StrNode* pn;	//the name if num the num string val
	int	  i;		//simple just int num~
	MinTokenRecord()
	{
		k = EEmpty;
		pn = nullptr;
		i = -1;
	}
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
	static bool IsSpecial(char c);
	
	static bool IsSpecialRecord(const MinTokenRecord& r);
	static bool IsKeyWordRecord(const MinTokenRecord& r);
public:

	bool ReadChar(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record);
	bool GenRecord(char buf[256],int pos,MinTokenRecord& record);
	bool HandleLetter(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record);
	bool HandleDigit(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record);
	bool HandleSpecial(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record);
	
private:
	MinToken& operator=(MinToken& rhs);
private:
	MinSource* pS;
};

#endif
