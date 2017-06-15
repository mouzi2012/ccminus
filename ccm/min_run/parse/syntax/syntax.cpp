#include "syntax.h"
#include<iostream>
#include "../../pool/hash_pool_manager.h"
using namespace std;




MinToken::MinToken(MinSource* rhs) :pS(rhs)
{

}
MinTokenRecord MinToken::getToken()
{
	if (!pS)
	{
		cout << "null ps" << endl;
		return MinTokenRecord{ EErrorTrace, nullptr, 0 };
	}

	char buf[256] = { 0 };
	int pos = 0;

	ECharType last_acc = ECharTypeEnd;
	char c = 0;
	char o = 0;
	for (;;)
	{
		o = c;
		if (pS->ReadC(c))
		{
			if (c=='\r')
			{
				continue;
			}
			else if (c=='/')
			{
				if (o == '/')
				{
					char tmp = 0;
					while (pS->ReadC(tmp))
					{
						if (tmp == '\n')
						{
							return MinTokenRecord{ ECOMMIT, nullptr, 0 };
						}
					}
				}
				else
				{

				}
			}
			else if (IsLetter(c))
			{
				if (HandleStateChange(last_acc, ELetter))
				{
					buf[pos++] = c;
					last_acc = ELetter;
				}
				else
				{
					cout << "handle letter error not need letter now" << endl;
					return MinTokenRecord{ EErrorTrace, nullptr, 0 };
				}
			}
			else if (IsDigit(c))
			{
				if (HandleStateChange(last_acc, EDigit))
				{
					buf[pos++] = c;
					last_acc = EDigit;
				}
				else
				{
					cout << "handle EDigit error not need EDigit now" << endl;
					return MinTokenRecord{ EErrorTrace, nullptr, 0 };
				}
			}
			else if (IsWhiteSpace(c))
			{
				MinTokenRecord r;
				if (last_acc == EDigit)
				{
					r.k = ENum;
					r.i = atoi(buf);
				}
				else if (last_acc == ELetter)
				{
					r.k = EID;
				}
				r.pn = HashPoolManager::GetInstance()->GetTable("StrHashTable")->FindStr(buf);

				return r;
			}

		}
		else
		{
			if (pos > 0)
			{
				MinTokenRecord r;
				if (last_acc == EDigit)
				{
					r.k = ENum;
					r.i = atoi(buf);
				}
				else if (last_acc == ELetter)
				{
					r.k = EID;
				}
				r.pn = HashPoolManager::GetInstance()->GetTable("StrHashTable")->FindStr(buf);
			}
			else
			{
				return MinTokenRecord{ EErrorTrace, nullptr, 0 };
			}
		}
		
	}
	return MinTokenRecord{ EErrorTrace, nullptr, 0 };

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
bool MinToken::HandleStateChange(ECharType o, ECharType n)
{
	switch (o)
	{
	case EDigit:
	{
		if (n == EDigit)
		{
			return true;
		}
		return false;
	}
	case ELetter:
	{
		if (n == ELetter)
		{
			return true;
		}
		return false;
	}
	case ECharTypeEnd:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}