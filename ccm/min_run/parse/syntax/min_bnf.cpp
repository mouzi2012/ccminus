#include "min_bnf.h"


#include "../../../min_common/utils.h"
#include "../../min_source.h"
#include "min_terminal.h"

#include<iostream>

using std::cout;
using std::endl;

MinBNF::MinBNF(MinSource* rhs)
{
	 pS = rhs;
}

void MinBNF::GetBNFMap()
{
	if(!pS)
	{
		return;
	}
	string s;
	while(pS->ReadLine(s))
	{
		
		if (s.size() > 0)
		{
			if (s[0] == '#')
			{
				continue;
			}
			//cout<<s;
			std::vector<std::string> out;
			Utils::SplitString(s,out,"->");
			if(out.size() == 2)
			{
				std::vector<std::string> sub_out;
				Utils::SplitString(out[1],sub_out,"|");
				auto func = [](const string& s)
				{
					while (true)
					{
						auto iter=find(s.begin(), s.end(), '\"');
					}
				};
				for(auto& d:sub_out)
				{
					list<string> ls;
					std::vector<std::string> sub_sub_out;
					Utils::SplitString(d, sub_sub_out, "\"");
					for (auto& d : sub_sub_out)
					{
						if (d.size() > 0)
						{
							std::vector<std::string> sub_sub_sub_out;
							Utils::SplitString(d, sub_sub_sub_out, " ");
							for (auto& d : sub_sub_sub_out)
							{
								if (d.size() > 0)
								{
									ls.push_back(d);
								}

							}
						}
						
					}
					m_bnf_map.insert(make_pair(out[0],ls));
				}
			}
		}
	}
}

void MinBNF::PrintBNFMap()
{
	for(auto& d: m_bnf_map)
	{
		cout<<d.first<<" => ";
		for (auto& ld:d.second)
		{
			cout << ld<< "^";
		}
		
		cout<<endl;
	}
}

void MinBNF::ParseNTerminal()
{
	for (auto& d : m_bnf_map)
	{
		auto iter = m_nt.find(d.first);
		if (iter == m_nt.end())
		{
			m_nt[d.first] = new MinNTerminal;
		}
	}

	for (auto& p : m_nt)
	{
		auto ret = m_bnf_map.equal_range(p.first);
		
		for (auto iter = ret.first; iter != ret.second; ++iter)
		{
			list<MinSymBlock> lb;
			for (auto& v:iter->second)
			{
				if (m_nt.find(v) == m_nt.end())
				{
					MinSymBlock b;
					b.t = MinSymBlock::ESymType::EToken;
					b.data.pMinT = new MinTokenRecord;
					lb.push_back(b);

					if (v == "ID")
					{
						b.data.pMinT->k = EMinTokenType::EID;
					}
					else if (v == "NUM")
					{
						b.data.pMinT->k = EMinTokenType::ENum;
					}
					else if (v =="+")
					{
						b.data.pMinT->k = EMinTokenType::EPLUS;
					}
					else if (v == "-")
					{
						b.data.pMinT->k = EMinTokenType::EMINUS;
					}
					else if (v == "*")
					{
						b.data.pMinT->k = EMinTokenType::EMULTI;
					}
					else if (v == "/")
					{
						b.data.pMinT->k = EMinTokenType::EDIV;
					}
					else if (v == "<")
					{
						b.data.pMinT->k = EMinTokenType::EL;
					}
					else if (v == "<=")
					{
						b.data.pMinT->k = EMinTokenType::ELEQ;
					}
					else if (v == ">")
					{
						b.data.pMinT->k = EMinTokenType::EG;
					}
					else if (v == ">=")
					{
						b.data.pMinT->k = EMinTokenType::EGEQ;
					}
					else if (v == "==")
					{
						b.data.pMinT->k = EMinTokenType::EEQ;
					}
					else if (v == "=")
					{
						b.data.pMinT->k = EMinTokenType::EASIGN;
					}
					else if (v == "!=")
					{
						b.data.pMinT->k = EMinTokenType::ENEQ;
					}
					else if (v == ";")
					{
						b.data.pMinT->k = EMinTokenType::ESEM;
					}
					else if (v == ",")
					{
						b.data.pMinT->k = EMinTokenType::ECOMMA;
					}
					else if (v == "(")
					{
						b.data.pMinT->k = EMinTokenType::ELBRAC;

					}
					else if (v == ")")
					{
						b.data.pMinT->k = EMinTokenType::ELBRAC;
					}
					else if (v == "[")
					{
						b.data.pMinT->k = EMinTokenType::ELINDEX;

					}
					else if (v == "]")
					{
						b.data.pMinT->k = EMinTokenType::ERINDEX;

					}
					else if (v == "{")
					{
						b.data.pMinT->k = EMinTokenType::ELBLOCK;

					}
					else if (v == "}")
					{
						b.data.pMinT->k = EMinTokenType::ERBLOCK;

					}
					else if (v == "if")
					{
						b.data.pMinT->k = EMinTokenType::EIF;
					}
					else if (v == "else")
					{
						b.data.pMinT->k = EMinTokenType::EELSE;
					}
					else if (v == "while")
					{
						b.data.pMinT->k = EMinTokenType::EWHILE;
					}
					else if (v == "int")
					{
						b.data.pMinT->k = EMinTokenType::EINT;
					}
					else if (v == "void")
					{
						b.data.pMinT->k = EMinTokenType::EVOID;
					}
					else if (v == "return")
					{
						b.data.pMinT->k = EMinTokenType::ERETURN;
					}
					else if (v == "empty")
					{
						b.t = MinSymBlock::ESymType::EEmpty;
						delete b.data.pMinT;
						b.data.pMinT = nullptr;
					}
					else
					{
						cout << "bad parse: "<< v << endl;
					}
				}
				else
				{
					MinSymBlock b;
					b.t = MinSymBlock::ESymType::ENTerminal;
					b.data.pMinNT = m_nt[v];
					lb.push_back(b);
				}
			}
			if (lb.size() > 0)
			{
				p.second->AddListSymBlock(lb);
			}
		}
	}
	
}
void MinBNF::GetTableSets()
{
	for (auto& v : m_nt)
	{
		v.second->GetFirstSet(nullptr);
	}
	MinTokenRecord* pM = new MinTokenRecord;
	pM->k = ETEnd;
	//the bnf start from program
	m_nt["program"]->AddFollowSet(pM);
	
	for (auto& v : m_nt)
	{
		v.second->GetFollowSet(nullptr);
	}
}
