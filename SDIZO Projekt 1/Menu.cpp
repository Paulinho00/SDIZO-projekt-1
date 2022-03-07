#include <iostream>
#include "DynamicArray.h"
using namespace std;

//Funkcja odczytujaca wybor uzytkownika i uruchamiajaca odpowiednie funkcje
void handleMainMenu() {
	while (true) {
		cout << "\nWybierz strukture:\n";
		cout << "1. Tablica dynamiczna\n";
		cout << "2. Lista dwukierunkowa\n";
		cout << "3. Kopiec binarny\n";
		cout << "4. Drzewo poszukiwan binarny (BST)\n";
		cout << "5. Drzewo czerwono-czarne\n";
		cout << "6. Zakoncz program\n";
		cout << "Podaj odpowiednia liczbe: \n";

		int* userInput = new int;
		cin >> *userInput;

		switch (*userInput) {
		case 1: {
			DynamicArray dynamicArray;
			dynamicArray.handleMenu();

		} break;
		case 6: exit(0);
		default: cout << "Nie ma takiej oppcji\n"; break;
		};

		delete userInput;
		cin.clear();
		cin.ignore(100, '\n');
	}
}

int main() {
		handleMainMenu();
}


