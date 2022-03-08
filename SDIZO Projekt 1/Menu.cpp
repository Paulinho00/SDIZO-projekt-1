#include <iostream>
using namespace std;

//Wyswietlanie i zarzadzanie menu tablicy dynamicznej
void dynamicArrayMenu() {
	while (1) {
		//Wyswietlenie opcji w menu
		cout << "\nWybierz opcje:\n";
		cout << "1. Odczytaj dane z pliku\n";
		cout << "2. Dodaj element na koncu tablicy\n";
		cout << "3. Dodaj element na wybranej pozycji\n";
		cout << "5. Usun element na koncu tablicy\n";
		cout << "6. Usun element na wybranej pozycji\n";
		cout << "7. Wyswietl wszystkie wartosci\n";
		cout << "8. Znajdz wartosc w tablicy\n";
		cout << "0. Cofnif do menu glownego\n";
		cout << "Podaj odpowiednia liczbe\n";

		//Odczyt wyboru uzytkownika
		int userInput;
		cin >> userInput;

		//Uruchomienie odpowiedniej funkcji w zaleznosci od wyboru
		switch (userInput) {
		case 0: return;
		default: cout << "Nie ma takiej oppcji\n"; break;
		};

		//Wyczyszczenie buforu
		cin.clear();
		cin.ignore(100, '\n');
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

		//Uruchomienie odpowiedniej funkcji w zaleznosci od wyboru
		switch (userInput) {
		case 1: dynamicArrayMenu(); break;
		case 0: exit(0);
		default: cout << "Nie ma takiej oppcji\n"; break;
		};

		//Wyczyszczenie buforu
		cin.clear();
		cin.ignore(100, '\n');
	}
}

int main() {
	dataStructuresMenu();
}


