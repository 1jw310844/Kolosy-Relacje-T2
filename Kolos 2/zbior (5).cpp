#include "zbior.h"
#include <new>
#include <random>
#include <cassert>

void Zbior::alokuj(int n)
{
	assert(n > 0);
	m_elementy = new(std::nothrow) double[n] {};
	m_liczbaElementow = n;

}

void Zbior::zwolnij()
{
	delete[] m_elementy;
}

Zbior::Zbior(size_t liczElem, double dGran, double gGran)
{
	alokuj(liczElem);
	std::uniform_real_distribution<double> zakres(dGran, gGran);
	std::random_device generator;
	for (int elem = 0; elem < liczElem; elem++)
		m_elementy[elem] = zakres(generator);
}

Zbior::Zbior(Zbior&& org)
{
	this->m_dolnaGranica = org.m_dolnaGranica;
	this->m_gornaGranica = org.m_gornaGranica;
	this->m_liczbaElementow = org.m_liczbaElementow;
	this->m_elementy = org.m_elementy;

	org.m_dolnaGranica = 0;
	org.m_elementy = nullptr;
	org.m_gornaGranica = 0;
	org.m_liczbaElementow = 0;
};

Zbior& Zbior::operator=(Zbior&& org)
{
	this->m_dolnaGranica = org.m_dolnaGranica;
	this->m_gornaGranica = org.m_gornaGranica;
	this->m_liczbaElementow = org.m_liczbaElementow;
	this->m_elementy = org.m_elementy;

	org.m_dolnaGranica = 0;
	org.m_elementy = nullptr;
	org.m_gornaGranica = 0;
	org.m_liczbaElementow = 0;
	return *this;

};

double* Zbior::getElementy()
{
	return m_elementy;
}

int Zbior::getLiczbaElementow()
{
	return m_liczbaElementow;
}