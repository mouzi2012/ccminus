#include "min_terminal.h"

MinNTerminal::MinNTerminal()
{
	
}
void MinNTerminal::AddListSymBlock(list<MinSymBlock>& lb)
{
	m_ts.push_back(lb);
}

void MinNTerminal::SetName(const string& n)
{
	m_n = n;
}
const string& MinNTerminal::GetName()
{
	return m_n;
}
bool MinNTerminal::HasEmpty()
{
	for (auto& l: m_ts)
	{
		for (auto& d:l)
		{
			if (d.t == MinSymBlock::ESymType::EEmpty)
			{
				return true;
			}
		}
	}
	return false;
}
const set<MinTokenRecord*>& MinNTerminal::GetFirstSet(MinNTerminal* pR)
{
	if (m_first.empty())
	{
		for (auto& l:m_ts)
		{
			for (auto& d : l)
			{
				if (d.t == MinSymBlock::ESymType::EEmpty)
				{
				}
				else if (d.t == MinSymBlock::ESymType::EToken)
				{
					m_first.insert(d.data.pMinT);
				}
				else if (d.t == MinSymBlock::ESymType::ENTerminal)
				{
					auto& v = d.data.pMinNT->GetFirstSet(pR);
					for (auto& r:v)
					{
						m_first.insert(r);
					}
					if (d.data.pMinNT->HasEmpty())
					{
						continue;
					}
				}
				else
				{
					
				}
				break;
			}
		}
	}
	return m_first;
}

const set<MinTokenRecord*>& MinNTerminal::GetFollowSet(MinNTerminal* pR)
{

}
