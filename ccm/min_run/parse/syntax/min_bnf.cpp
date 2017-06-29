#include "MinBNF.h"
#include "../../../min_common/utils.h"
#include<iostream>

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
	while(!pS->ReadLine(s))
	{
		if (s.size() > 0)
		{
			cout<<s;
			std::vector<std::string> out;
			Utils::SplitString(s,out,"->");
			if(out.size() == 2)
			{
				std::vector<std::string> sub_out;
				Utils::SplitString(out[1],sub_out,"|");
				for(auto& d:sub_out)
				{
					 m_bnf_map.insert(out[0],d);
				}
			}
		}
	}
}

void MinBNF::PrintBNFMap()
{
	for(auto& d: m_bnf_map)
	{
		cout<<d->first<<" =>";
		ret =  m_bnf_map.equal_range(d->first);
		for(auto p_map = ret.first; p_map != ret.second; ++p_map)
			cout<<" "<< (*p_map).second;
		cout<<endl;
	}
}

void MinBNF::ParseNTerminal()
{
	
}