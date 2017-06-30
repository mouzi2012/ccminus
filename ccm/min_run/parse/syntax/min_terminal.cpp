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