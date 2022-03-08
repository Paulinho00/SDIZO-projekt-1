#include <iostream>
using namespace std;

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


