#include <iostream>
#include "DataStructures.h"
using namespace std;

//Wyswietlanie i zarzadzanie menu tablicy dynamicznej
void dynamicArrayMenu() {
	DynamicArray dynamicArray;
	while (1) {
		//Wyswietlenie opcji w menu
		cout << "\nWybierz opcje:\n";
		cout << "1. Odczytaj dane z pliku\n";
		cout << "2. Dodaj element na koncu tablicy\n";
		cout << "3. Dodaj element na wybranej pozycji\n";
		cout << "4. Usun element na koncu tablicy\n";
		cout << "5. Usun element na wybranej pozycji\n";
		cout << "6. Wyswietl wszystkie wartosci\n";
		cout << "7. Znajdz wartosc w tablicy\n";
		cout << "8. Wygeneruj wartosci losowe\n";
		cout << "0. Cofnij do menu glownego\n";
		cout << "Podaj odpowiednia liczbe\n";

		//Odczyt wyboru uzytkownika
		int userInput;
		cin >> userInput;

		//Wykrycie blednego typu wejscia
		if (cin.fail()) {
			cout << "Podales zla liczbe\n";
			//Wyczyszczenie buforu
			cin.clear();
			cin.ignore(100, '\n');
			continue;
		}

		//Uruchomienie odpowiedniej funkcji w zaleznosci od wyboru
		switch (userInput) {
		case 1: {
			string filename;
			cout << "Podaj nazwe pliku ";
			cin >> filename;
			dynamicArray.readFromFile(filename);
		}; break;
		case 2: {
			cout << "Podaj wartosc ";
			cin >> userInput;

			//Wykrycie blednych danych
			if (cin.fail()) {
				cout << "Podales zle dane\n";
				//Wyczyszczenie buforu
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}

			dynamicArray.addElement(userInput);
		}; break;
		case 3: {
			int index;
			cout << "Podaj wartosc ";
			cin >> userInput;
			cout << "Podaj indeks na ktory chcesz wstawic liczbe ";
			cin >> index;

			//Wykrycie blednych danych
			if (cin.fail()) {
				cout << "Podales zle dane\n";
				//Wyczyszczenie buforu
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}

			dynamicArray.addElementAtIndex(index, userInput);
		}; break;
		case 4: {
			dynamicArray.deleteElement();
		}; break;
		case 5: {
			cout << "Podaj indeks, z ktorego chcesz usunac wartosc ";
			cin >> userInput;

			//Wykrycie blednych danych
			if (cin.fail()) {
				cout << "Podales zle dane\n";
				//Wyczyszczenie buforu
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}
			dynamicArray.deleteElementAtIndex(userInput);
		}; break;
		case 6: dynamicArray.showElements(); break;
		case 7: {
			cout << "Podaj wartosc do wyszukania ";
			cin >> userInput;

			//Wykrycie blednych danych
			if (cin.fail()) {
				cout << "Podales zle dane \n";
				//Wyczyszczenie buforu
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}

			dynamicArray.findElement(userInput);

		}; break;
		case 8: {
			cout << "Podaj ilosc elementow ";
			cin >> userInput;

			//Wykrycie blednych danych
			if (cin.fail()) {
				cout << "Podales zle dane \n";
				//Wyczyszczenie buforu
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}
			dynamicArray.fillArray(userInput);
		}; break;
		case 0: return;
		default: cout << "Nie ma takiej oppcji\n"; break;
		};


	}
}

//Wyswietlenie i zarzadzanie menu dla listy dwukierunkowej
void doubleLinkedListMenu() {
	while (1) {
		//Wyswietlenie opcji w menu
		cout << "\nWybierz opcje:\n";
		cout << "1. Odczytaj dane z pliku\n";
		cout << "2. Dodaj element na koncu listy\n";
		cout << "3. Dodaj element na wybranej pozycji\n";
		cout << "4. Usun element na koncu listy\n";
		cout << "5. Usun element na wybranej pozycji\n";
		cout << "6. Wyswietl wszystkie wartosci\n";
		cout << "7. Znajdz wartosc w liscie\n";
		cout << "8. Wygeneruj wartosci losowe\n";
		cout << "0. Cofnij do menu glownego\n";
		cout << "Podaj odpowiednia liczbe\n";

		//Odczyt wyboru uzytkownika
		int userInput;
		cin >> userInput;

		//Wykrycie blednego typu wejscia
		if (cin.fail()) {
			cout << "Podales zla liczbe\n";
			//Wyczyszczenie buforu
			cin.clear();
			cin.ignore(100, '\n');
			continue;
		}

		//Uruchomienie odpowiedniej funkcji w zaleznosci od wyboru
		switch (userInput) {
		case 0: return;
		default: cout << "Nie ma takiej oppcji\n"; break;
		};
	}
}

//Funkcja wyswietlajaca menu i zarzadzajaca wyborem uzytkownika
void dataStructuresMenu() {
	while (1) {
		//Wyswietlenie opcji w menu
		cout << "\nWybierz strukture:\n";
		cout << "1. Tablica dynamiczna\n";
		cout << "2. Lista dwukierunkowa\n";
		cout << "3. Kopiec binarny\n";
		cout << "4. Drzewo poszukiwan binarny (BST)\n";
		cout << "5. Drzewo czerwono-czarne\n";
		cout << "0. Zakoncz program\n";
		cout << "Podaj odpowiednia liczbe: \n";
		

		//Odczyt wyboru uzytkownika
		int userInput;
		cin >> userInput;

		//Wykrycie blednego typu wejscia
		if (cin.fail()) {
			cout << "Podales zla liczbe\n ";
			//Wyczyszczenie buforu
			cin.clear();
			cin.ignore(100, '\n');
			continue;
		}

		//Uruchomienie odpowiedniej funkcji w zaleznosci od wyboru
		switch (userInput) {
		case 1: dynamicArrayMenu(); break;
		case 2: doubleLinkedListMenu(); break;
		case 0: exit(0);
		default: cout << "Nie ma takiej oppcji\n"; break;
		};

	}
}

int main() {
	dataStructuresMenu();
}


