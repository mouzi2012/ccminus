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
			return true;	
		}
		else if(IsLetter(buf[0]))
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
		if (c=='\r')
		{
			continue;
		}
		else if (c=='/')
		{
			return HandleSlash(c,o,buf,pos,record)
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
			record.k= ErrorTrace;
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
		record.k = ErrorTrace;
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
	if ((c == ' ') || (c == '\n') || (c == '\t'))
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
	record.k = ErrorTrace;
	return false;
	
}
bool MinToken::handleDigit(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record)
{
	if(IsDigit(o) || (o==0))
	{
		buf[pos++] = c;
		return ReadChar(c,o,buf,pos,record);
	}
	record.k = ErrorTrace;
	return false;

}
bool MinToken::HandleSlash(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record)
{
	if(o == '/')
	{
		for(;;)
		{
			char tmp = 0;
			if(pS->Read(tmp))
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
