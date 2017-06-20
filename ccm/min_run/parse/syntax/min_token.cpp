#include "syntax.h"
#include<iostream>
#include "../../pool/hash_pool_manager.h"
#include "../../min_source.h"
using namespace std;




MinToken::MinToken(MinSource* rhs) :pS(rhs)
{
	
}
MinTokenRecord MinToken::GetToken()
{
	if (!pS)
	{
		cout << "null ps" << endl;
		return MinTokenRecord{ EErrorTrace, nullptr, 0 };
	}
	char buf[256] = { 0 };
	int pos=0;
	char c = 0;
	char o = 0;
	MinTokenRecord r{ EEmpty, nullptr, 0 };
	if(ReadChar(c,o,buf,pos,r))
	{
		cout<<"pasre ok"<<endl; 
	}
	else
	{
		cout<<"parse error"<<endl;
	}
	return r;
}

bool MinToken::GenRecord(char buf[256],int pos,MinTokenRecord& record)
{
	
	if(pos>0)
	{
		if(IsLetter(buf[0]))
		{
			record.k = EID;
			record.pn = HashPoolManager::GetInstance()->GetTable("StrHashTable")->FindStr(buf);
			//the key word
			if(strcmp("if",buf)==0)
			{
				record.k = EIF;
			}
			else if(strcmp("else",buf)==0)
			{
				record.k = EELSE;
			}
			else if(strcmp("int",buf)==0)
			{
				record.k = EINT;
			}
			else if(strcmp("return",buf)==0)
			{
				record.k = ERETURN;
			}
			else if(strcmp("void",buf)==0)
			{
				record.k = EVOID;
			}
			else if(strcmp("while",buf)==0)
			{
				record.k = EWHILE;
			}
			// the special word
			else if(strcmp("+",buf)==0)
			{
				record.k = EPLUS;
			}
			else if(strcmp("-",buf)==0)
			{
				record.k = EMINUS;
			}
			else if(strcmp("*",buf)==0)
			{
				record.k = EMULTI;
			}
			else if(strcmp("/",buf)==0)
			{
				record.k = EDIV;
			}
			else if(strcmp("<",buf)==0)
			{
				record.k = EL;
			}
			else if(strcmp("<=",buf)==0)
			{
				record.k = ELEQ;
			}
			else if(strcmp(">",buf)==0)
			{
				record.k = EG;
			}
			else if(strcmp(">=",buf)==0)
			{
				record.k = EGEQ;
			}
			else if(strcmp("==",buf)==0)
			{
				record.k = EEQ;
			}
			else if(strcmp("!=",buf)==0)
			{
				record.k = ENEQ;
			}
			else if(strcmp("=",buf)==0)
			{
				record.k = EASIGN;
			}
			else if(strcmp(";",buf)==0)
			{
				record.k = ESEM;
			}
			else if(strcmp(",",buf)==0)
			{
				record.k = ECOMMA;
			}
			else if(strcmp("(",buf)==0)
			{
				record.k = ELBRAC;
			}
			else if(strcmp(")",buf)==0)
			{
				record.k = ERBRAC;
			}
			else if(strcmp("[",buf)==0)
			{
				record.k = ELINDEX;
			}
			else if(strcmp("]",buf)==0)
			{
				record.k = ERINDEX;
			}
			else if(strcmp("{",buf)==0)
			{
				record.k = ELBLOCK;
			}
			else if(strcmp("}",buf)==0)
			{
				record.k = ERBLOCK;
			}
			return true;	
		}
		else if(IsDigit(buf[0]))
		{
			record.k = ENum;
			record.i = atoi(buf);
			record.pn = HashPoolManager::GetInstance()->GetTable("StrHashTable")->FindStr(buf);
				
			return true;
		}
	}
	return false;
}
bool MinToken::ReadChar(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record)
{
	o = c;
	if(pS->ReadC(c))
	{
		if (c=='/')
		{
			return HandleSlash(c, o, buf, pos, record);
		}
		else if (IsLetter(c))
		{
			return HandleLetter(c,o,buf,pos,record);	
		}
		else if(IsDigit(c))
		{
			return HandleDigit(c,o,buf,pos,record);
		}
		else if(IsWhiteSpace(c))
		{
			if(pos>0)
			{
				return GenRecord(buf,pos,record);
			}
			else
			{
				return true;
			}
		}
		else
		{
			record.k= EErrorTrace;
			return false;
		}
	}
	//do not parse annotation
	if(pos>0)
	{
		GenRecord(buf,pos,record);
		return true;
	}	
	if(o == 0)
	{
		return true;	
	}
	else
	{
		record.k = EErrorTrace;
		return false;
	}
}

bool MinToken::IsLetter(char c)
{
	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
	{
		return true;
	}
	return false;
}
bool MinToken::IsDigit(char c)
{
	if ('0' <= c && c <= '9')
	{
		return true;
	}
	return false;
}
bool MinToken::IsWhiteSpace(char c)
{
	if ((c == ' ') || (c == '\n') || (c == '\t') || (c == '\r'))
	{
		return true;
	}
	return false;
}

bool MinToken::HandleLetter(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record)
{
	if(IsLetter(o) || (o==0))
	{
		buf[pos++] = c;
		return ReadChar(c,o,buf,pos,record);
	}
	record.k = EErrorTrace;
	return false;
	
}
bool MinToken::HandleDigit(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record)
{
	if(IsDigit(o) || (o==0))
	{
		buf[pos++] = c;
		return ReadChar(c,o,buf,pos,record);
	}
	record.k = EErrorTrace;
	return false;

}
bool MinToken::HandleSlash(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record)
{
	if(o == '/')
	{
		for(;;)
		{
			char tmp = 0;
			if(pS->ReadC(tmp))
			{
				if(tmp=='\n')
				{
					break;
				}
			}
			else
			{
				break;
			}	
			
		}
		return true; // some time empty record~
	}
	else if(IsLetter(o) || IsDigit(o))
	{
		pS->BackP();		
		return GenRecord(buf,pos,record);
	}
	else if(o == 0)
	{
		return ReadChar(c,o,buf,pos,record);
	}
	else 
	{
		record.k = EErrorTrace ;
		return false;
	}

}
