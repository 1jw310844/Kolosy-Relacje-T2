#pragma once
#include <vector>
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
	Zbior(const Zbior& org);
	Zbior& operator=(const Zbior& org) noexcept;
	bool operator==(const Zbior& org) const;
	friend void testKonstruktora();
	friend void testOperatora();
};

class Zbiory
{
	std::vector<Zbior> dane;
public:
	void dodajZbior(Zbior z);
	void usunZbior(size_t index);
	friend class Funktor;
	friend Zbiory nowKompozyt(const Zbiory& z1, const Zbiory& z2);
};

class Funktor
{
	const Zbiory& zbiory;
public:
	Funktor(const Zbiory& z)
		:zbiory(z)
	{
	}
	bool operator()(const Zbior& zbior) const
	{
		bool wystepuje = false;
		for (const auto& zbio : zbiory.dane)
		{
			if (zbio == zbior)
			{
				wystepuje = true;
				break;
			}
		}
		return wystepuje;
	} 

};
void testKonstruktora();
void testOperatora();

