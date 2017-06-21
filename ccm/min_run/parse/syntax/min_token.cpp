#include "min_token.h"
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
		MinTokenRecord r;
		r.k = EErrorTrace;
		return r;
	}
	char buf[256] = { 0 };
	int pos=0;
	char c = 0;
	char o = 0;
	MinTokenRecord r;
	if(ReadChar(c,o,buf,pos,r))
	{
		//cout<<"pasre ok"<<endl; 
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
		else if(IsDigit(buf[0]))
		{
			record.k = ENum;
			record.i = atoi(buf);
			record.pn = HashPoolManager::GetInstance()->GetTable("StrHashTable")->FindStr(buf);
				
			return true;
		}
		else
		{
			//the key word
			
			record.pn = HashPoolManager::GetInstance()->GetTable("StrHashTable")->FindStr(buf);
			if (strcmp("if", buf) == 0)
			{
				record.k = EIF;
				return true;
			}
			else if (strcmp("else", buf) == 0)
			{
				record.k = EELSE;
				return true;
			}
			else if (strcmp("int", buf) == 0)
			{
				record.k = EINT;
				return true;
			}
			else if (strcmp("return", buf) == 0)
			{
				record.k = ERETURN;
				return true;
			}
			else if (strcmp("void", buf) == 0)
			{
				record.k = EVOID;
				return true;
			}
			else if (strcmp("while", buf) == 0)
			{
				record.k = EWHILE;
				return true;
			}
			// the special word
			else if (strcmp("+", buf) == 0)
			{
				record.k = EPLUS;
				return true;
			}
			else if (strcmp("-", buf) == 0)
			{
				record.k = EMINUS;
				return true;
			}
			else if (strcmp("*", buf) == 0)
			{
				record.k = EMULTI;
				return true;
			}
			else if (strcmp("/", buf) == 0)
			{
				record.k = EDIV;
				return true;
			}
			else if (strcmp("<", buf) == 0)
			{
				record.k = EL;
				return true;
			}
			else if (strcmp("<=", buf) == 0)
			{
				record.k = ELEQ;
				return true;
			}
			else if (strcmp(">", buf) == 0)
			{
				record.k = EG;
				return true;
			}
			else if (strcmp(">=", buf) == 0)
			{
				record.k = EGEQ;
				return true;
			}
			else if (strcmp("==", buf) == 0)
			{
				record.k = EEQ;
				return true;
			}
			else if (strcmp("!=", buf) == 0)
			{
				record.k = ENEQ;
				return true;
			}
			else if (strcmp("=", buf) == 0)
			{
				record.k = EASIGN;
				return true;
			}
			else if (strcmp(";", buf) == 0)
			{
				record.k = ESEM;
				return true;
			}
			else if (strcmp(",", buf) == 0)
			{
				record.k = ECOMMA;
				return true;
			}
			else if (strcmp("(", buf) == 0)
			{
				record.k = ELBRAC;
				return true;
			}
			else if (strcmp(")", buf) == 0)
			{
				record.k = ERBRAC;
				return true;
			}
			else if (strcmp("[", buf) == 0)
			{
				record.k = ELINDEX;
				return true;
			}
			else if (strcmp("]", buf) == 0)
			{
				record.k = ERINDEX;
				return true;
			}
			else if (strcmp("{", buf) == 0)
			{
				record.k = ELBLOCK;
				return true;
			}
			else if (strcmp("}", buf) == 0)
			{
				record.k = ERBLOCK;
				return true;
			}
		}
	}
	return false;
}
bool MinToken::ReadChar(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record)
{
	o = c;
	if(pS->ReadC(c))
	{
		if(IsSpecial(c))
		{
			return HandleSpecial(c, o, buf, pos, record);
		}
		else
		{
			if (IsLetter(c))
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
				record.k = EErrorTrace;
				return false;
			}
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
		record.k = ETEnd;
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

bool MinToken::IsSpecial(char c)
{
	switch(c)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '<':
	case '>':
	case '=':
	case '!':
	case ';':
	case ',':
	case '(':
	case ')':
	case '[':
	case ']':
	case '{':
	case '}':
		return true;
	default:
		return false;
	}
	return false;
}

bool MinToken::HandleSpecial(char& c,char& o,char buf[256],int& pos,MinTokenRecord& record)
{
	if (IsLetter(o) || IsDigit(o))
	{
		pS->BackP();
		return GenRecord(buf, pos, record);
	}
	else
	{
		if (c == '+' ||
			c == '-' ||
			c == '*' ||
			c == '-' ||
			c == '(' ||
			c == ')' ||
			c == '[' ||
			c == ']' ||
			c == '{' ||
			c == '}' ||
			c == ';'||
			c == ',')
		{
			buf[pos++] = c;
			return GenRecord(buf, pos, record);
		}
		else
		{
			if (c == '>' || c == '<')
			{
				buf[pos++] = c;
				return ReadChar(c, o, buf, pos, record);
			}
			else if (c == '=')
			{
				if (o == '>' || o == '<' || o == '=' || o == '!')
				{
					buf[pos++] = c;
					return GenRecord(buf, pos, record);
				}
				else if (o == 0)
				{
					buf[pos++] = c;
					return ReadChar(c, o, buf, pos, record);
				}
				else if (IsLetter(o) || IsDigit(o))
				{
					pS->BackP();
					return GenRecord(buf, pos, record);
				}
			}
			else if (c == '!')
			{
				if (o == 0)
				{
					buf[pos++] = c;
					return ReadChar(c, o, buf, pos, record);
				}
			}
			else if (c == '/')
			{
				if (o == 0)
				{
					buf[pos++] = c;
					return ReadChar(c, o, buf, pos, record);
				}
				
				else if (o == '/')
				{
					for (;;)
					{
						char tmp = 0;
						if (pS->ReadC(tmp))
						{
							if (tmp == '\n')
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
			}
		}
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
	else if(IsSpecial(o))
	{
		pS->BackP();
		return GenRecord(buf,pos,record);
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
	else if(IsSpecial(o))
	{
		pS->BackP();
		return GenRecord(buf,pos,record);
	}
	record.k = EErrorTrace;
	return false;

}

