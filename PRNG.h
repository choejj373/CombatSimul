#pragma once
class PRNG
{
	unsigned int m_seed;
public:
	PRNG() : m_seed(0) {}
	void setSeed(unsigned int seed) { m_seed = seed; }
	unsigned int rand()
	{
		m_seed = 8253729 * m_seed + 2396403;
		return (m_seed % 32768);
	}
};

