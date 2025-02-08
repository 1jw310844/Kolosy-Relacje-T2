#pragma once
#include <cstddef>
#include <iostream>
#include <vector>
#include <random>
#include <cassert>
#include <algorithm>
class Zbior
{
	size_t m_liczbaElementow = 0;
	double* m_elementy = nullptr;
	double m_dolnaGranica = 0;
	double m_gornaGranica = 0;
	void alokuj(int);
	void zwolnij();
public:
	Zbior(size_t liczElem, double dGran, double gGran);
	~Zbior() {}
	Zbior(const Zbior& org); //konstruktor kopiuj¹cy
	Zbior& operator=(const Zbior& org);
	//Zbior(Zbior&& org); konstruktor przenosz¹cy
	//Zbior& operator=(Zbior&& org); przenosz¹cy operator przypisania
	size_t liczbaElementow() const {
		return m_liczbaElementow;
	}
};

class Kompozyt
{
private:
	std::vector<Zbior> zbiory;
public:
	void dodajZbior(Zbior&& zbior);	
	void usunZbior(size_t indeks);
	size_t liczbaZbiorow() const;
	size_t zliczZbioryWZakresie(size_t dolna, size_t gorna) const;
};

class FunktorPredykat
{
private:
	size_t dolnaGranica, gornaGranica;
public:
	FunktorPredykat(size_t dolna, size_t gorna) :dolnaGranica(dolna), gornaGranica(gorna){}
	bool operator()(const Zbior& zbior) const; 
};
