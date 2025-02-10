#pragma once
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

	Zbior(Zbior&& org);
	Zbior& operator=(Zbior&& org);

	double* getElementy(); // w podpunkcie 3 trzeba dostac sie do elementow 
	int getLiczbaElementow(); // dla funktora
};


