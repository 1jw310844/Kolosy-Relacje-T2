#include "zbior.h"
#include <new>
#include <random>
#include <cassert>
#include <vector>
#include <iostream>

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

Zbior::Zbior(const Zbior& org)
	:m_liczbaElementow(org.m_liczbaElementow), 
	m_dolnaGranica(org.m_dolnaGranica), 
	m_gornaGranica(org.m_gornaGranica)
{
	alokuj(m_liczbaElementow);
	for (int i = 0; i < m_liczbaElementow; i++) {
		m_elementy[i] = org.m_elementy[i];
	}
}
Zbior& Zbior::operator=(const Zbior& org) noexcept
{
	if (this != &org)
	{
		bool roznyRozmiar = this->m_liczbaElementow != org.m_liczbaElementow;
		if (this->m_elementy != nullptr && roznyRozmiar) zwolnij();
		if (org.m_elementy != nullptr) {
			if (roznyRozmiar) alokuj(org.m_liczbaElementow);
			for (size_t i = 0; i < org.m_liczbaElementow; i++) {
				this->m_elementy[i] = org.m_elementy[i];
			}
		}
		this->m_liczbaElementow = org.m_liczbaElementow;
		this->m_dolnaGranica = org.m_dolnaGranica;
		this->m_gornaGranica = org.m_gornaGranica;
	}
	return *this;
}
bool Zbior::operator==(const Zbior& org) const
{
	bool iRozmiar = this->m_liczbaElementow == org.m_liczbaElementow;
	bool iDolna = this->m_dolnaGranica == org.m_dolnaGranica;
	bool iGorna = this->m_gornaGranica == org.m_gornaGranica;
	bool iElementy = true;

	for (size_t i = 0; i < m_liczbaElementow; i++)
	{
		if (this->m_elementy[i] != org.m_elementy[i])
		{
			iElementy = false;
			break;
		}
	}
	return (iRozmiar && iGorna && iDolna && iElementy);
}
void Zbiory::dodajZbior(Zbior z)
{
	dane.push_back(z);
}
void Zbiory::usunZbior(size_t index)
{
	if (index >= 0 && index < dane.size())
	{
		dane.erase(dane.begin() + index);
	}
}

void testKonstruktora()
{
	std::cerr << "Test konstruktora kopiujacego: ";
	Zbior z1(7, 1, 3);
	Zbior z2(z1);

	if (z1.m_elementy != z2.m_elementy)
	{
		std::cerr << "OK!";
	}
	else {
		std::cerr << "FAIL!";
	}
}

void testOperatora()
{
	std::cerr << "Test operatora kopiujacego: ";
	Zbior z1(7, 1.0, 3.0);
	Zbior z2 = z1;

	bool iRozmiar = z1.m_liczbaElementow == z2.m_liczbaElementow;
	bool iDolna = z1.m_dolnaGranica == z2.m_dolnaGranica;
	bool iGorna = z1.m_gornaGranica == z2.m_gornaGranica;
	bool iElementy = true;

	for (size_t i = 0; i < z1.m_liczbaElementow; i++)
	{
		if (z1.m_elementy[i] != z2.m_elementy[i])
		{
			iElementy = false;
			break;
		}
	}

	if (iRozmiar && iDolna && iGorna && iElementy)
	{
		std::cerr << "OK!";
	}
	else {
		std::cerr << "FAIL!";
	}
}

Zbiory nowKompozyt(const Zbiory& z1, const Zbiory& z2)
{
	Zbiory nowyKompozyt;
	Funktor f(z1);

	for (auto const& zb : z2.dane)
	{
		if (f(zb))
		{
			nowyKompozyt.dodajZbior(zb);
		}
	}
	return nowyKompozyt;
}