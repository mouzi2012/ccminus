#include "min_source.h"
#include <memory.h>
#include <stdio.h>
#include <assert.h>
#include <new>
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
	if (this == &s)
	{
		return *this;
	}
	memcpy(m_name, s.m_name, sizeof(m_name));
	m_p = 0;
	m_n = s.m_n;
	if (m_n > 0)
	{
		m_i = new(std::nothrow) char(m_n);
		if (m_i)
		{
			memcpy(m_i, s.m_i, m_n);
		}
		
	}
	m_isLoad = s.m_isLoad;
	return *this;
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
	if (m_isLoad)
	{
		return;
	}

	FILE *pFile = fopen(f, "r");
	if (!pFile)
	{
		return;
	}
	fseek(pFile, 0L, SEEK_END);
	int size = ftell(pFile);
	fseek(pFile, 0L, SEEK_END);
	m_i = new(std::nothrow) char[size];
	if (m_i)
	{
		int rs=fread(m_i,size,1,pFile);
		assert(rs == size);
		m_n = size;
		m_isLoad = true;
		memcpy(m_name, f, sizeof(m_name));
	}
	fclose(pFile);
}
