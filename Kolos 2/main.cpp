#include <iostream>
#include "zbior.h"
#include <vector>
#include <algorithm>

class Agregat
{
	Zbior* tablica[10];
	int liczbaElementow = 0;
public:
	void dodajElement(Zbior& element)
	{
		tablica[liczbaElementow] = &element;
		liczbaElementow++;
	}

	void usunElement(int index)
	{
		tablica[index] = nullptr;
		
		for (int i = index; i < liczbaElementow; i++)
		{
			tablica[i] = tablica[i + 1];
		}
			liczbaElementow--;
			tablica[liczbaElementow] = nullptr;
	}

	Zbior** getTablica()
	{
		return tablica;
	}

	int getLiczbaElementow()
	{
		return liczbaElementow;
	}
};

class AgregatVector
{
	std::vector<Zbior*> tablica;
	int liczbaElementow = 0;
public:
	void dodajElement(Zbior& element)
	{
		if (liczbaElementow <= 10)
		{
			tablica.push_back(&element);
			liczbaElementow++;
		}
	}

	void usunElement(int index)
	{
		if (index >= 0 && index < 10)
		{
			tablica.erase(tablica.begin() + index);
			liczbaElementow--;
		}
	}

	std::vector<Zbior*>& getTablica()
	{
		return tablica;
	}
};

class Funktor
{
	int zakresGorny;
	int zakresDolny;
public:
	Funktor(int dol, int gora)
	{
		if (dol <= gora)
		{
			zakresDolny = dol;
			zakresGorny = gora;
		}
		else
		{
			zakresDolny = gora;
			zakresGorny = dol;
		}
	}

	bool operator()(Zbior* zbior)
	{
		if (zbior->getLiczbaElementow() >= zakresDolny && zbior->getLiczbaElementow() <= zakresGorny) return true;
		else return false;
	}
};

void TestUsuwanieDawcyZasobu()
{
	std::cout << "Test utraty zasoby przez dawce: ";
	Zbior FajnyZbior(10, 4, 4);
	Zbior Kopia = std::move(FajnyZbior);

	if (FajnyZbior.getElementy() == nullptr) std::cout << "OK!";
	else std::cout << "FAIL!";
	std::cout << std::endl;
};

void TestDodawaniaZasobuBiory()
{
	std::cout << "Test otrzymania zasobu przez odbiorce: ";
	Zbior FajnyZbior(10, 4, 4);
	Zbior Kopia(std::move(FajnyZbior));

	if (Kopia.getElementy() != nullptr) std::cout << "OK!";
	else std::cout << "FAIL!";
	std::cout << std::endl;
};

int main()
{
	TestDodawaniaZasobuBiory();
	TestUsuwanieDawcyZasobu();

	Zbior zbior1(10, 4, 4); // V
	Zbior zbior2(7, 4, 4);  // V
	Zbior zbior3(8, 4, 4);  // V
	Zbior zbior4(3, 4, 4);  // X
	Zbior zbior5(5, 4, 4);  // X
	Zbior zbior6(7, 4, 4);  // V
	Zbior zbior7(10, 4, 4); // V
	Zbior zbior8(3, 4, 4);  // X
	Zbior zbior9(5, 4, 4);  // X

	AgregatVector agregatV;
	agregatV.dodajElement(zbior1);
	agregatV.dodajElement(zbior2);
	agregatV.dodajElement(zbior3);
	agregatV.dodajElement(zbior4);
	agregatV.dodajElement(zbior5);
	agregatV.dodajElement(zbior6);
	agregatV.dodajElement(zbior7);
	agregatV.dodajElement(zbior8);
	agregatV.dodajElement(zbior9);
	
	Funktor funktor(6, 11);
	int wynikV = 0;
	for (int i = 0; i < 10; i++)
	{
		wynikV = std::count_if(agregatV.getTablica().begin(), agregatV.getTablica().end(), funktor);
	}

	std::cout << wynikV;

	Agregat agregat;
	agregat.dodajElement(zbior1);
	agregat.dodajElement(zbior2);
	agregat.dodajElement(zbior3);
	agregat.dodajElement(zbior4);
	agregat.dodajElement(zbior5);
	agregat.dodajElement(zbior6);
	agregat.dodajElement(zbior7);
	agregat.dodajElement(zbior8);
	agregat.dodajElement(zbior9);

	int wynik = 0;
	for (int i = 0; i < agregat.getLiczbaElementow(); i++)
	{
		if(funktor(agregat.getTablica()[i])) wynik++;
	}

	std::cout << std::endl << wynik;

}