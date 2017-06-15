#include "syntax.h"
#include<iostream>
using namespace std;




MinToken::MinToken(MinSource* rhs) :pS(rhs)
{

}
MinTokenRecord MinToken::getToken()
{
	char buff[256] = { 0 };
	int pos = 0;
	ECharType last_acc = ECharTypeEnd;
	for (;;)
	{
		char c=0;
		if (!pS)
		{
			cout << "null ps" << endl;
			return MinTokenRecord { EErrorTrace, nullptr, 0 };
		}
		if (pS->ReadC(c))
		{
			
			if (c=='\r')
			{
				continue;
			}
			else if (IsLetter(c))
			{
				if (HandleStateChange(last_acc, ELetter))
				{
					buff[pos++] = c;
					last_acc = ELetter;
				}
				else
				{
					cout << "handle letter error not need letter now" << endl;
					MinTokenRecord r{ EErrorTrace, nullptr, 0 };
					return r;
				}
			}
			else if (IsDigit(c))
			{
				if (HandleStateChange(last_acc, EDigit))
				{
					buff[pos++] = c;
					last_acc = EDigit;
				}
				else
				{
					cout << "handle EDigit error not need EDigit now" << endl;
					MinTokenRecord r{ EErrorTrace, nullptr, 0 };
					return r;
				}
			}
			else if (IsWhiteSpace(c))
			{

			}

		}
		else
		{

		}
		
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