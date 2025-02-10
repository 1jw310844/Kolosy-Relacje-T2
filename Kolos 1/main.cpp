#include <iostream>
#include <cmath>
#include "zbior.h"
using namespace std;

class Agregat
{
public:
	void dodajElement(Zbior& element)
	{
		if (liczba_elementow < 10)
		{
			tablica[liczba_elementow] = &element;
			liczba_elementow++;
		}
		else cout << "Tablica jest pelna" << endl;
	}

	void usunElement(int ktory)
	{
		if (ktory >= 0 && ktory < 10)
		{
			tablica[ktory] = nullptr;
			liczba_elementow--;

			for (int i = ktory; i < liczba_elementow; i++)
				tablica[ktory] = tablica[ktory + 1];
		}
		//else cout << "index poza tablica" << endl;
	}

private:
	Zbior* tablica[10] = {};
	int liczba_elementow = 0;
};

class Funktor
{
	double liczba;
public:
	Funktor(double liczba)
		:liczba(liczba)
	{};

	bool operator()(Zbior& zbior)
	{
		double suma = 0;
		for (int i = 0; i < zbior.getRozmiar(); i++)
			suma += zbior.getZbior()[i];
		
		if (suma > liczba) return true;
		else return false;
	}
};


void Test()
{
	cout << "Test operatora przenoszenia z przesunieciem o 6: ";
	const int rozmiar = 8;
	Zbior testowy(rozmiar, -2, 7);
	Zbior nowy(1, 1, 1);
	nowy = testowy;

	for (int i = 0; i < rozmiar; i++)
	{
		if (abs(testowy.getZbior()[i] - nowy.getZbior()[(i + 6) % rozmiar]) > 0.0001)
		{
			cout << "FAIL";
			return;
		}
	}

	cout << "OK!";
	cout << endl;
}

void TestFunktoraTrue()
{
	cout << "Test funktora true: ";
	Zbior zbior(10, 1, 5);
	Funktor funktor(4);

	bool wynik = funktor(zbior);
	if (wynik == true) cout << "OK!";
	else cout << "FAIL!";
	cout << endl;
}

void TestFunktoraFalse()
{
	cout << "Test funktora false: ";
	Zbior zbior(10, 1, 5);
	Funktor funktor(60);

	bool wynik = funktor(zbior);
	if (wynik == false) cout << "OK!";
	else cout << "FAIL!";
	cout << endl;
}

int main()
{
	const int rozmiar = 5;
	Zbior typ(rozmiar, 0, 7);
	Zbior dwa(1, 2, 3);
	dwa = typ;
	/*
	for (int i = 0; i < rozmiar; i++)
		cout << typ.getZbior()[i] << " ";
	cout << endl;

	for (int i = 0; i < rozmiar; i++)
		cout << dwa.getZbior()[i] << " ";
	*/

	cout << endl;
	Test();

	Agregat agregat;
	agregat.dodajElement(typ);
	agregat.dodajElement(typ);
	agregat.dodajElement(typ);
	agregat.dodajElement(typ);
	agregat.dodajElement(typ);
	agregat.dodajElement(typ);
	agregat.dodajElement(typ);
	agregat.dodajElement(typ);
	agregat.dodajElement(typ);
	agregat.dodajElement(typ);


	agregat.usunElement(10);
	agregat.dodajElement(typ);

	Funktor mojUlubionyFunktor(100000);
	//cout << mojUlubionyFunktor(typ);

	TestFunktoraFalse();
	TestFunktoraTrue();
}
