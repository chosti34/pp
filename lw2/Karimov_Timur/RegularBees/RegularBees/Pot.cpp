#include "stdafx.h"
#include "Pot.h"

Pot::Pot(unsigned capacity)
	: m_capacity(capacity)
	, m_honeySipCount(0u)
{
}

bool Pot::TryPutHoneySip()
{
	if (m_honeySipCount < m_capacity)
	{
		++m_honeySipCount;
		return true;
	}
	return false;
}

bool Pot::IsEmpty()const
{
	return m_honeySipCount == 0u;
}

void Pot::PopHoneySip()
{
	if (m_honeySipCount > 0)
	{
		--m_honeySipCount;
	}
}

unsigned Pot::GetHoneySipsCount()const
{
	return m_honeySipCount;
}

unsigned Pot::GetCapacity()const
{
	return m_capacity;
}
