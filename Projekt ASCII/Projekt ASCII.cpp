#include "stdafx.h"
#include <iostream>
#include "conio.h"
#include "windows.h"

using namespace std;

void HideCursor();
void ShowCursor();
void Wstep();
void legenda();
void dane_wym(int &l);
void wspol(int x, int y);

/********************************************************/
/*  Utworzenie klasy Punkt, wewnatrz klasy zastosowano  */
/*	   metode rys_pkt ktora wyswietla podany znak	    */
/********************************************************/
class Punkt
{
public:
	int x, y;
	char znak, temp;
	void rys_pkt()
	{
		cout << znak;
	}
};
/**************************************************************************************/
/* Utworzenie klasy Odcinek z dziedziczeniem klasy Punkt, wewnatrz klasy zastosowano  */
/*	    metody ktore pozwola rysowac poszczegolne odcinki aby narysowac figure	      */
/**************************************************************************************/
class Odcinek : public Punkt
{
public:
	int l;
	bool end;
	void rys_poziom()
	{
		for (int i = 0; i <= l; i++)
		{
			wspol(x, y);
			Punkt::rys_pkt();
			x--;
		}
	}
	void rys_poziom1()
	{
		for (int i = 0; i <= l; i++)
		{
			wspol(x, y);
			Punkt::rys_pkt();
			x++;
		}
	}
	void rys_skos_dol()
	{
		for (int i = 0; i <= l / 2; i++)
		{
			wspol(x, y);
			Punkt::rys_pkt();
			y--; x++;
		}
	}
	void rys_skos_dol1()
	{
		for (int i = 0; i <= l / 2; i++)
		{
			wspol(x, y);
			Punkt::rys_pkt();
			y++; x--;
		}
	}
	void rys_skos_gora()
	{
		for (int i = 0; i <= l / 2; i++)
		{
			wspol(x, y);
			Punkt::rys_pkt();
			y++; x--;
		}
	}
	void rys_skos_gora1()
	{
		for (int i = 0; i <= l / 2; i++)
		{
			wspol(x, y);
			Punkt::rys_pkt();
			y--; x++;
		}
	}
};
/***********************************************************************/
/*	Utworzenie klasy Figura z dziedziczeniem klasy Odcinek,			   */
/*	wewnatrz klasy zastosowano metode ktora rysuje figure oraz		   */
/*	kolejna metode dzieki ktorej mozemy dokonywac operacji na figurze  */
/***********************************************************************/
class Figura : public Odcinek
{
public:
	void rys_fig()
	{
		rys_skos_dol(); x--; y++;
		rys_poziom(); x++;
		rys_poziom1(); x--;
		rys_skos_dol1(); x++; y--;
		rys_skos_gora(); x++; y--;
		rys_poziom1(); x--;
		rys_poziom(); x++;
		rys_skos_gora1(); x--; y++;		
	}
	void ruch_fig()
	{
		znak = temp;
		rys_fig();
		while (end == false)
		{
			unsigned char kierunek = _getch();
			switch (kierunek)
			{
			case 27:
				exit(0);
				break;
			case 43:	//powiekszenie
				znak = ' ';
				rys_fig();
				if ((y + l) < 31 && (y - l) > 1 && (x - (2 * l) > 1)) l = l + 2;	//ograniczenie
				znak = temp;
				rys_fig();
				break;
			case 45:	//pomniejszenie
				znak = ' ';
				rys_fig();
				if (l > 2) l = l - 2;	//ograniczenie
				znak = temp;
				rys_fig();
				break;
			case 0:
			case 224:	//strzalki
				kierunek = _getch();
				switch (kierunek)
				{
				case 75: //lewo
					znak = ' ';
					rys_fig();
					if (x >= l) x--;	//ograniczenie
					znak = temp;
					rys_fig();
					break;
				case 77:	//prawo
					znak = ' ';
					rys_fig();
					if (x <= (99-l)) x++;	//ograniczenie
					znak = temp;
					rys_fig();
					break;
				case 72:	//gora
					znak = ' ';
					rys_fig();
					if (y > l-1) y--;	//ograniczenie
					znak = temp;
					rys_fig();
					break;
				case 80:	//dol
					znak = ' ';
					rys_fig();
					if (y <(35-(l+1))) y++;	//ograniczenie
					znak = temp;
					rys_fig();
					break;
				}
			}
		}
	}
};
int main()
{
	COORD c;					//rozmiar konsoli
	c.X = 100;
	c.Y = 35;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), c);

	Figura zetka;
	zetka.x = c.X - 50;
	zetka.y = c.Y / 2;
	zetka.temp = '*';
	zetka.l = 8;			
	zetka.end = 0;		
	
	Wstep();
	HideCursor();
	
	unsigned char wybor = _getch();
	switch (wybor)			//pozwala nam dokonac wyboru czy chcemy podac znak z klawiatury oraz wymiary 
							//czy moze zostajemy przy domyslnych ustawieniach
	{
	case 49:	//opcja pierwsza
		system("cls");
		HideCursor();
		legenda();
		zetka.ruch_fig();

		ShowCursor();
		break;

	case 50:	//opcja druga
		system("cls");

		cout << "Podaj znak jaki ma rysowac figure: ";
		cin >> zetka.temp;
		cout << "Podaj rozmiar figury (parzyste) <4;12>: ";
		dane_wym(zetka.l);

		system("cls");
		HideCursor();
		legenda();
		zetka.ruch_fig();
		ShowCursor();
		break;
	}	
	system("pause");	
}

/**************************************************/
/*   Funkcja pozwalająca ukryć kursor w konsoli   */
/**************************************************/
void HideCursor()
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = FALSE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}
/**************************************************/
/*  Funkcja pozwalająca pokazac kursor w konsoli  */
/**************************************************/
void ShowCursor()
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = TRUE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}
/**************************************************/
/*  Funkcja Wstep wyswietla w konsoli informacje  */
/*odnośnie funkcji jakie będzie umożliwiać program*/
/**************************************************/
void Wstep() {

	cout << "Maciej Dzieciuch\n"
		<< "Zadanie 66.\n"
		<< "Program rysujacy znakiem ASCII figure, ktory umozliwia:\n"
		<< "-wybor znaku kodu ASCII przez uzytkownika,\n"
		<< "-wczytanie poczatkowego rozmiaru figury,\n"
		<< "-przesuwanie figury klawiszami strzalek,\n"
		<< "-powiekszanie oraz zmniejszanie rozmiaru figury za pomoca klawiszy plus i minus,\n"
		<< "Uwaga: punkt poczatkowy znajduje sie w srodku ekranu.\n\n"
		<< "Nacisnij dowolny klawisz aby kontynuowac . . .";
	_getch();
	system("cls");
	cout << "MENU\n"
		<< "WYBIERZ OPCJE:\n"
		<< "1.USTAWIENIA DOMYSLNE\n"
		<< "2.USTAWIENIA INDYWIDUALNE";
}
/**************************************************/
/*	  Funkcja legenda wyswietla nam opcje		  */
/*		jakie mozemy wykonac w programie		  */
/**************************************************/
void legenda()
{
	wspol(1, 34);
	cout << char(24) << " w gore";
	wspol(15, 34);
	cout << char(25) << " w dol";
	wspol(30, 34);
	cout << char(27) << " w lewo";
	wspol(45, 34);
	cout << char(26) << " w prawo";
	wspol(60, 34);
	cout << char(43) << " powieksz";
	wspol(75, 34);
	cout << char(45) << " pomniejsz";
	wspol(89, 34);
	cout << "[Esc] wyjdz";
}
/**************************************************/
/*	  Funkcja ta jest kontrola danych dzieki      */
/*  czemu program uwaza na blednie podane dane	  */
/**************************************************/
void dane_wym(int &l)
{
	do {
		cin >> l;

		if (cin.fail() || l < 4 || l > 12 || l % 2 != 0)
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
	COORD c;					//rozmiar konsoli