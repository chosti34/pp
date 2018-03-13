#pragma once

class Pot
{
public:
	Pot(unsigned capacity)
		: m_capacity(capacity)
		, m_honeySipCount(0u)
	{
	}

	bool TryPutHoneySip()
	{
		if (m_honeySipCount < m_capacity)
		{
			++m_honeySipCount;
			return true;
		}
		return false;
	}

	bool IsEmpty()const
	{
		return m_honeySipCount == 0u;
	}

	void PopHoneySip()
	{
		if (m_honeySipCount > 0)
		{
			--m_honeySipCount;
		}
	}

private:
	unsigned m_capacity;
	unsigned m_honeySipCount;
};
