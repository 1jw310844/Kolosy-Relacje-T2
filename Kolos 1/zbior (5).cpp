#include "zbior.h"
#include <new>
#include <random>
#include <cassert>
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

Zbior::Zbior(Zbior&& org) 
	: m_liczbaElementow(org.m_liczbaElementow),
	m_elementy(org.m_elementy),
	m_dolnaGranica(org.m_dolnaGranica),
	m_gornaGranica(org.m_gornaGranica)
{
	std::cout << "Dzia³a konstruktor przenosz¹cy\n";

	org.m_liczbaElementow = 0;
	org.m_elementy = nullptr;
	org.m_dolnaGranica = 0;
	org.m_gornaGranica = 0;
}

/*
	size_t m_liczbaElementow = 0;
	double* m_elementy = nullptr;
	double m_dolnaGranica = 0;
	double m_gornaGranica = 0;
*/


Zbior& Zbior::operator=(Zbior& org)
{
	this->m_dolnaGranica = org.m_dolnaGranica;
	this->m_gornaGranica = org.m_gornaGranica;
	
	if (m_elementy != nullptr && m_liczbaElementow) zwolnij();

	alokuj(org.m_liczbaElementow);
	
	//Przesuniecie
	for (int element = 0; element < org.m_liczbaElementow; element++)
		this->m_elementy[(element+6)%m_liczbaElementow] = org.m_elementy[element];

	/*
	//Rotacja
	for (int element = 0; element < org.m_liczbaElementow; element++)
		this->m_elementy[element] = org.m_elementy[m_liczbaElementow - element -1];
	*/

	return *this;
};

size_t Zbior::getRozmiar()
{
	return m_liczbaElementow;
}