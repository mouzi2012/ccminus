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
		list<MinSymBlock> lb;
		for (auto iter = ret.first; iter != ret.second; ++iter)
		{
			for (auto& v:iter->second)
			{
				/*if ()
				{
				}*/
			}
		}

		if (lb.size() > 0)
		{
			p.second->AddListSymBlock(lb);
		}
			
	}
	
}