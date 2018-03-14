#pragma once

class Pot
{
public:
	Pot(unsigned capacity);

	bool TryPutHoneySip();
	bool IsEmpty()const;
	void PopHoneySip();
	unsigned GetHoneySipsCount()const;
	unsigned GetCapacity()const;

private:
	unsigned m_capacity;
	unsigned m_honeySipCount;
};
