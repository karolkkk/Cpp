/* Karolina Krauze gr.3 zad.133 */


#include "iostream"
#include <conio.h>
#include <Windows.h>

using namespace std;
//umozliwienie uzycia strzalek
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


const int esc = 27;
void powitanie()
{
	cout << "Witaj w programie rysujacym figure w ksztalcie litery W." << endl<<endl;
	cout << "Do poruszania figura sluza strzalki" << endl<<endl << "Aby powiekszyc lub zmniejszyc figure uzyj odpowiednio przyciskow '+ ' lub ' - '";
	_getch();
}
void gotoxy(int x, int y)//umozliwienie ustawienia kursora consoli w wybranym miejscu
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void HideCursor()//ukrycie kursora
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = FALSE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}
void rysowanie(byte znak, int rozmiar, int szer, int dl)
{

	
	CONSOLE_SCREEN_BUFFER_INFO csbi;//zczytanie danych o dolnej krawedzi konsoli
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int b = csbi.srWindow.Bottom;
	int startY = 0, startX = 0;
	int y, x, i;
	char codalej;

	do {
			cout << "podaj rozmiar figury" << endl;
			cin >> rozmiar;
		if (cin.fail())//gdy uytkownik wpisze znak zamiast liczby-->prosba o ponowne wprowadzenie danych
			{
				do
					{
						cin.sync();
						cin.clear();
						cin.ignore();
						system("cls");
						cout << "Podales nieprawidlowy znak. Sproboj raz jeszcze" << endl;
						cout << "Podaj rozmiar figury: ";
						cin >> rozmiar;
					} while (cin.fail());
			}
				else
					{
						system("cls");
						cout << "zly rozmiar" << endl;
					}
	} while (rozmiar>b-7);//ograniczenie, aby uzytkownik nie wybral zbyt duzego rozmiaru
		

			for (int i = 0; i <= rozmiar; i++)//zmiana rozmiaru minimalnego figury
			{
				szer++;
				dl++;
			}
	


		do
		{

			CONSOLE_SCREEN_BUFFER_INFO csbi;//zczytanie informacji o kolumnach,rzedach,i pozycji kursora w konsoli
			int columns, rows, cursorx, cursory;

			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
			columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
			rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
			cursorx = csbi.dwCursorPosition.X;
			cursory = csbi.dwCursorPosition.Y;
			//informacje o konsoli

			int y = rows / 2, x = columns / 2;//zmienne ustawione na srodkowe wartosci konsoli
			system("cls");
			x = x + startX; y = y + startY;
			gotoxy(x, y);//start srodek konsoli
			cout << znak;

			for (int i = 1; i <= (szer / 2) - 1; i++)//lewy skos;poruszamy sie w lewo i w dol;
			{
				x--;//lewo
				y++;//dol
				gotoxy(x, y);//ustawienie kursora konsoli w odpowiednim miejscu
				cout << znak;
			}

			x--;//przesuwamy kursor o jedna kolumne w lewo i schodzmiy dwa rzedy w dol
			y = y + 2;
			for (int i = 1; i <= dl; i++)//lewy pion,wyswietlamy znak poruszajac sie po rzedach w gore
			{

				y--;
				gotoxy(x, y);
				cout << znak;
			}

			y = rows / 2, x = columns / 2;//wracamy do srodka konsoli
			x = x + startX; y = y + startY;
			for (int i = 1; i <= (szer / 2) - 1; i++)//prawy skos,po kolumnach w prawo i po rzedach w dol
			{

				x++;
				y++;
				gotoxy(x, y);
				cout << znak;
			}
			//ustwienie kursora o kolumne dalej i o dwa rzedy nizej
			x++; y = y + 2;
			for (int i = 1; i <= dl; i++)//prawy pion, po rzedach do gory
			{

				y--;
				gotoxy(x, y);
				cout << znak;
			}
			HideCursor();
			codalej = _getch();//pobranie klawisza od uytkownika

			switch (codalej)//uzytkownik wybiera co chce zrobic z figura
			{
				//powieksznie
			case'+':
			{////ograniczenie, aby z zadnej strony nie wyjsc za konsole
				if (csbi.srWindow.Top + cursory > 1 && csbi.srWindow.Bottom - cursory >= dl&&csbi.srWindow.Left + cursorx>szer&&csbi.srWindow.Right - cursorx>0)
				{
					szer = szer + 2;
					dl = dl + 2;
				}break;
			}
			//zmniejszenie
			case'-':
			{
				if (szer >= 7 && dl >= 6)
				{
					szer = szer - 2;
					dl = dl - 2;
				}
				else
				{
					cout << endl << "minimalny rozmiar." << endl;
					_getch();
				}break;
			}
			//przesuwanie w lewo

			case KEY_LEFT:
			{
				if (csbi.srWindow.Left + cursorx>szer+1)//ograniczenie aby nie wyjsc za konsole
					startX--;

				break;
			}
			//przesuwanie w prawo
			case KEY_RIGHT:
			{
				if (csbi.srWindow.Right - cursorx>0)//ograniczenie aby nie wyjsc za konsole
				startX++;

			break;
			}
			//przesuwanie do gory
			case KEY_UP:
			{
				if (csbi.srWindow.Top + cursory>1)//ograniczenie aby nie wyjsc za konsole
					startY--;

				break;
			}
			//przesuwanie w dol
			case KEY_DOWN:
			{
				if (csbi.srWindow.Bottom - cursory >= dl)//ograniczenie aby nie wyjsc za konsole
				startY++;

			break;
			}
			case esc: {break; }
			}
		} while (codalej != esc);
}
int wybor_znaku()//wybor znaku
{
	int znak;

	system("cls");
	cout << "Podaj numer znaku ASCII, ktorym ma byc rysowana figura" << endl;
	cin >> znak;

	if (cin.fail())//kontrola danych,jesli znak wpisany przez uzytkownika nie jest liczba,bedzie musial ponownie wpiasac dane
	{
		while (cin.fail())
		{
			cin.sync();
			cin.clear();
			cin.ignore();
			system("cls");
			cout << "Podales nieprawidlowy numer. Sproboj raz jeszcze" << endl;
			cout << "Podaj NUMER znaku: ";
			cin >> znak;
		}
	}
	else
	{ 
		if((0 > znak) || (znak > 256))//jesli liczba wybrana przez uzytkonia nie odpowiada zadnemy znaku z tablicy ASCII,uzytkownik bedzie musial ja ponownie wpisac
		while ((0 > znak) || (znak > 256))
		{
			cin.sync();
			cin.clear();
			cin.ignore();
			system("cls");
			cout << "Podales nieprawidlowy numer. Sproboj raz jeszcze" << endl;
			cout << "Podaj NUMER znaku: ";
			cin >> znak;

		}
		else
		{
			return znak;//jesli wartosc jest popawna funkcja zwroci znak
		}
	}
}
int main()
{

	int szer = 7;
	int dl = 6; 
	int rozmiar = 0;
	powitanie();
	byte znak = wybor_znaku();//przypisanie zwroconej wartosci do zmiennej byte
	rysowanie(znak, rozmiar, szer, dl);
	HideCursor();

	_getch();
}