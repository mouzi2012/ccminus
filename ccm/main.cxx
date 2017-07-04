#include<iostream>
#include "min_run/min_source.h"
#include "min_run/parse/syntax/min_token.h"
#include "min_run/parse/syntax/min_bnf.h"
using namespace std;

void testToken()
{
	MinSource source;
	source.Init("ccmin/basic.cm");
	MinToken token(&source);
	while(true)
	{
		MinTokenRecord r= token.GetToken();
		
		bool needStop = false;
		switch (r.k)
		{
		case ETEnd:
			needStop = true;
			break;
		case ENum:
			cout << r.i << endl;
			break;
		case EEmpty:
			break;
		default:
			cout << StrHashTable::GetStr(r.pn) << endl;
			break;
		}
		if (needStop)
		{
			break;
		}
	}
}
void testBNF()
{
	MinSource source;
	source.Init("ccmin/BNF_convert.txt");
	MinBNF bnf(&source);
	
	bnf.GetBNFMap();
	bnf.PrintBNFMap();
}
#include <ctime>
int main()
{
	//std::locale::global(std::locale("ja_JP.utf8"));
	//std::time_t t = std::time(NULL);
	/*std::time_t t = 1499101261;
	char mbstr[100];
	if (std::strftime(mbstr, sizeof(mbstr), "%Y", std::localtime(&t))) {
	std::cout << mbstr << '\n';
	}*/
	//testToken();
	//testBNF();
	system("pause");
	return 0;
}
