#include "min_source.h"
#include <memory.h>
MinSource::MinSource()
{
	memset(m_name, 0, sizeof(m_name));
	m_p = 0;
	m_i = nullptr;
	m_n = 0;
	m_isLoad = false;
}

MinSource& MinSource::operator=(MinSource& s)
{
	memcpy(m_name, s.m_name, sizeof(m_name));
	m_p = 0;
	m_n = s.m_n;
	if (m_n > 0)
	{
		m_i = new char(m_n);
		memcpy(m_i, s.m_i, m_n);
	}
	m_isLoad = s.m_isLoad;
}
MinSource::~MinSource()
{
	if (m_i)
	{
		delete m_i;
	}
	memset(m_name, 0, sizeof(m_name));
	m_p = 0;
	m_i = nullptr;
	m_n = 0;
	m_isLoad = false;
}
void MinSource::ResetP()
{
	m_p = 0;
}
bool MinSource::ReadC(char& c)
{
	if (m_p < m_n)
	{
		c = m_i[m_p++];
		return true;
	}
	else
	{
		return false;
	}
}
void MinSource::Init(char* f)
{

}
