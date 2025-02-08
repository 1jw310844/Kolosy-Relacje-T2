#include "zbiory.h"
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

Zbior::Zbior(const Zbior& org) // konstruktor kopiujący elementy 
	:m_liczbaElementow(org.m_liczbaElementow)
{
	if (org.m_elementy != nullptr)
	{
		alokuj(org.m_liczbaElementow);
		for (int i = 0; i < org.m_liczbaElementow; i++)
		{
			this->m_elementy[i] = org.m_elementy[i];
		}
	}
}
Zbior& Zbior::operator=(const Zbior& org)  // kopiujący operator przypisania
{
	if (this != &org)
	{
		bool roznyRozmiar = this->m_liczbaElementow != org.m_liczbaElementow;
		if (this->m_elementy != nullptr && roznyRozmiar)
			zwolnij();
		if (org.m_elementy != nullptr)
		{
			if (roznyRozmiar) alokuj(org.m_liczbaElementow);
			for (int i = 0; i < org.m_liczbaElementow; i++)
			{
				this->m_elementy[i] = org.m_elementy[i];
			}
		}
		this->m_liczbaElementow = org.m_liczbaElementow;
	}
	return *this;
}
//Funktor pełniący role predykata
bool FunktorPredykat::operator()(const Zbior& zbior) const {
	return zbior.liczbaElementow() >= dolnaGranica && zbior.liczbaElementow() <= gornaGranica;
}
//Kompozyt zbiorów
void Kompozyt::dodajZbior(Zbior&& zbior)
{
	zbiory.push_back(std::move(zbior));
}
void Kompozyt::usunZbior(size_t indeks)
{
	if (indeks < zbiory.size())
	{
		zbiory.erase(zbiory.begin() + indeks);
	}
}
size_t Kompozyt::liczbaZbiorow() const
{
	return zbiory.size();
}
size_t Kompozyt::zliczZbioryWZakresie(size_t dolna, size_t gorna) const {
	return std::count_if(zbiory.begin(), zbiory.end(),FunktorPredykat(dolna, gorna));
}

//Konstruktor przenoszący i przenoszący operator przypisania
/*
Zbior::Zbior(Zbior&& org) //konstruktor przenoszący
	:m_liczbaElementow(org.m_liczbaElementow)
{
	this->m_elementy = org.m_elementy;
	org.m_elementy = nullptr;
}
Zbior& Zbior::operator=(Zbior&& org)Zbior& Zbior::operator=(Zbior&& org) // przenoszący operator przypisania
{
	if (this != &org)
	{
		if (this->m_elementy != nullptr)
			zwolnij();
		this->m_elementy = org.m_elementy;
		this->m_liczbaElementow = org.m_liczbaElementow;
		org.m_elementy = nullptr;
	}
	return *this;
}
*/