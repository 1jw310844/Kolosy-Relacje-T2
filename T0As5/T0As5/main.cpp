#include <iostream>
#include "Zbior.h"

int main()
{
	testKonstruktora();
	std::cout << std::endl;
	testOperatora();

	Zbior z1(10, 1.5, 2.5);
	Zbior z2(9, 2.5, 3.5);
	Zbior z3(20, 0.5, 2.5);
	Zbior z4(13, 4.5, 6.5);

	Zbiory zbiory1;
	zbiory1.dodajZbior(z1);
	zbiory1.dodajZbior(z2);
	zbiory1.dodajZbior(z3);
	zbiory1.dodajZbior(z4);

	Zbiory zbiory2;
	zbiory2.dodajZbior(z1);
	zbiory2.dodajZbior(z2);


	Funktor f(zbiory1);

	if (f(z1)) {
		std::cout << std::endl;
		std::cout << "Zbior wystepuje w kompozycie\n";
	}
	else {
		std::cout << std::endl;
		std::cout << "Zbior nie wystepuje w kompozycie\n";
	}

	Zbiory wspolne = nowKompozyt(zbiory1, zbiory2);

	Funktor sprawdz(wspolne);

	if (sprawdz(z1) && sprawdz(z2)) {
		std::cout << "Dziala";
	}
	else {
		std::cout << "Nie dziala";
	}
}