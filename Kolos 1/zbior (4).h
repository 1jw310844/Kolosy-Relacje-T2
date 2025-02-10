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

	Zbior(const Zbior& org) = delete;
	Zbior(Zbior&& org);
	Zbior& operator=(Zbior& org);
	Zbior& operator=(Zbior&& org) = delete;

	double* getZbior() //w celu zweryfikowana danych, potrzebujemy dostepu do elementow
	{
		return m_elementy;
	}

	size_t getRozmiar(); //w funktorze jest potrzeba uzyskania dostepu do roziaru
	
};

