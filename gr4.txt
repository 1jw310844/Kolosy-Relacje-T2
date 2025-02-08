zbior.cpp

#include <iostream>
#include "zbior.h"
#include <new>
#include <random>
#include <cassert>
#include <stdexcept>
#include <algorithm>


// Alokacja pamięci
void Zbior::alokuj(int n)
{
    assert(n > 0);  // Sprawdzamy, że liczba elementów jest dodatnia
    m_elementy = new(std::nothrow) double[n] {};  // Alokacja pamięci dla tablicy
    m_liczbaElementow = n;
}

// Zwalnianie pamięci
void Zbior::zwolnij()
{
    delete[] m_elementy;  // Zwalniamy dynamicznie przydzieloną pamięć
    m_elementy = nullptr;  // Ustawiamy wskaźnik na nullptr
}

// Konstruktor z liczbą elementów i zakresem
Zbior::Zbior(size_t liczElem, double dGran, double gGran)
{
    alokuj(liczElem);  // Alokujemy pamięć dla elementów
    std::uniform_real_distribution<double> zakres(dGran, gGran);
    std::random_device generator;
    for (size_t elem = 0; elem < liczElem; ++elem) {
        m_elementy[elem] = zakres(generator);  // Generowanie losowych elementów
    }
}

// Konstruktor kopiujący
Zbior::Zbior(const Zbior& z)
    : m_liczbaElementow(z.m_liczbaElementow),
    m_dolnaGranica(z.m_dolnaGranica),
    m_gornaGranica(z.m_gornaGranica)
{
    if (z.m_elementy != nullptr) {
        alokuj(z.m_liczbaElementow);  // Alokujemy nową pamięć
        for (size_t i = 0; i < z.m_liczbaElementow; ++i) {
            m_elementy[i] = z.m_elementy[i];  // Kopiujemy dane
        }
    }
}
Zbior& Zbior::operator=(const Zbior& z) {
    if (this != &z) {
        bool roznyRozmiar = this->m_liczbaElementow != z.m_liczbaElementow; 
        bool roznaGorna = this->m_gornaGranica != z.m_gornaGranica;
        bool roznaDolna = this->m_dolnaGranica != z.m_dolnaGranica;
        if (this->m_elementy != nullptr&&roznyRozmiar&&roznaGorna&&roznaDolna)zwolnij();
        if (z.m_elementy != nullptr) {
            if (roznyRozmiar) alokuj(z.m_liczbaElementow);
            for (int i = 0; i < z.m_liczbaElementow; i++) {
                this->m_elementy[i] = z.m_elementy[i];

            }
            
        }
        this->m_dolnaGranica = z.m_dolnaGranica;
        this->m_gornaGranica = z.m_gornaGranica;
    }
    return *this;
}
Zbior::Zbior(Zbior&& z)
    : m_liczbaElementow(z.m_liczbaElementow),
    m_dolnaGranica(z.m_dolnaGranica),
    m_gornaGranica(z.m_gornaGranica)
{
    this->m_elementy = z.m_elementy;
    z.m_elementy = nullptr;
}
Zbior& Zbior:: operator=(Zbior&& z) {
    if (this != nullptr) {
        if (this->m_elementy != nullptr) zwolnij();
        this->m_elementy = z.m_elementy;
        this->m_liczbaElementow = z.m_liczbaElementow;
        this->m_dolnaGranica = z.m_dolnaGranica;
        this->m_gornaGranica = z.m_gornaGranica;
        z.m_elementy = nullptr;
    }
    return *this;
}
void Zbior::setRozmiar(size_t le) {
    if (le > 0) {
        zwolnij();
        alokuj(le);
        std::uniform_real_distribution<double> zakres(this->m_dolnaGranica, this->m_gornaGranica);
        std::random_device generator;
        for (size_t elem = 0; elem < le; ++elem) {
            m_elementy[elem] = zakres(generator);  // Generowanie losowych elementów
        }
    }
    else throw std::invalid_argument("Bledna liczba elementow");
}

// Destruktor
Zbior::~Zbior()
{
    zwolnij();  // Zwalniamy przydzieloną pamięć
}

void Zbior::TestKopii(Zbior& z) {
    Zbior z1(z);
    bool TakiSamRozmiar = z.m_liczbaElementow == z1.m_liczbaElementow;
    bool TakaSamaDGranica = z.m_dolnaGranica == z1.m_dolnaGranica;
    bool TakaSamaGGranica = z.m_gornaGranica == z1.m_gornaGranica;
    if (TakiSamRozmiar && TakaSamaDGranica && TakaSamaGGranica) {
        for (size_t i = 0; i < z.m_liczbaElementow; i++) {
            if (z1.m_elementy[i] != z.m_elementy[i]) {
                std::cerr << "Blad\n";
                break;
            }
            
        }
        z.m_elementy[0] = z.m_elementy[0] + 1;
        if (z1.m_elementy[0] != z.m_elementy[0]) std::cout << "OK" << std::endl;
    }
}

Zbiory::Zbiory() 
    :zbiory(),iter(zbiory.begin())
{}
void Zbiory::DodajZbior(Zbior& z) {
    
    zbiory.push_back(z);
    if (zbiory.size() == 1) iter = zbiory.begin();
    else iter = prev(zbiory.end());
    
}
void Zbiory::UsunZbior(Zbior& z) {
    if (zbiory.empty()) throw runtime_error("Lista jest pusta");
    iter = zbiory.begin();
    while (iter != zbiory.end()) {
        if (&(*iter) == &z) {
            iter = zbiory.erase(iter);
            return;
        }
        ++iter;
    }
    throw invalid_argument("Podany zbior nie istnieje w kolekcji");
}

size_t Zbior::getLiczbaElementow() {
    return m_liczbaElementow;
}
bool Predykat::operator()( Zbior& lz,  Zbior& pz)  {
    return lz.getLiczbaElementow() >= pz.getLiczbaElementow();
}
void Zbiory::SortujZbiory() {
    Predykat p;
    zbiory.sort(p);
}

zbior.h

#pragma once

#include <list>
#include <cstddef>  // Dla size_t
using namespace std;

class Zbior
{
    size_t m_liczbaElementow = 0;  // Liczba elementów w zbiorze
    double* m_elementy = nullptr;  // Wskaźnik na dynamicznie alokowaną tablicę
    double m_dolnaGranica = 0;     // Dolna granica dla generowania liczb
    double m_gornaGranica = 0;     // Górna granica dla generowania liczb

    void alokuj(int);  // Funkcja alokująca pamięć
    void zwolnij();    // Funkcja zwalniająca pamięć

public:
    // Konstruktor z liczbą elementów i zakresem
    Zbior(size_t liczElem, double dGran, double gGran);
    void setRozmiar(size_t le);

    // Konstruktor kopiujący (const Zbior&)
    Zbior(const Zbior& z);
    size_t getLiczbaElementow();

    Zbior& operator=(const Zbior& z);
    Zbior(Zbior&& z);
    Zbior& operator=(Zbior&& z);
    void TestKopii(Zbior& z);

    // Destruktor
    ~Zbior();
};

class Zbiory {

    list<Zbior> zbiory;
    list<Zbior>::iterator iter = zbiory.begin();

public:
    Zbiory();
    void DodajZbior(Zbior &z);
    void UsunZbior(Zbior &z);
    void SortujZbiory();
};

class Predykat {


public:
    bool operator()( Zbior& lz,  Zbior& pz) ;
};
