#include <iostream>
#include "DataStructures.h"
using namespace std;

//Funkcja odczytujaca i sprawdzajaca dane wprowadzone przez uzytkownika
int readUserInput() {
	//Odczyt wyboru uzytkownika
	int userInput;
	cin >> userInput;

	//Wykrycie blednego typu wejscia
	if (cin.fail()) {
		cout << "Podales zla liczbe\n";
		//Wyczyszczenie buforu
		cin.clear();
		cin.ignore(100, '\n');
		return -1;
	}
	else {
		return userInput;
	}
}

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
		userInput = readUserInput();
		if (userInput == -1) {
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
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}

			dynamicArray.addElement(userInput);
		}; break;
		case 3: {
			

			cout << "Podaj wartosc ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}

			int index;
			cout << "Podaj indeks na ktory chcesz wstawic liczbe ";
			//Odczyt wyboru uzytkownika
			index = readUserInput();
			if (index == -1) {
				break;
			}

			dynamicArray.addElementAtIndex(index, userInput);
		}; break;
		case 4: {
			dynamicArray.deleteElement();
		}; break;
		case 5: {
			cout << "Podaj indeks, z ktorego chcesz usunac wartosc ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}
			dynamicArray.deleteElementAtIndex(userInput);
		}; break;
		case 6: dynamicArray.showElements(); break;
		case 7: {
			cout << "Podaj wartosc do wyszukania ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}

			dynamicArray.findElement(userInput);

		}; break;
		case 8: {
			cout << "Podaj ilosc elementow ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}
			if (userInput <= 0) {
				cout << "Nieprawidlowa ilosc\n";
				break;
			}

			dynamicArray.fillArray(userInput);
		}; break;
		case 0: return;
		default: cout << "Nie ma takiej opcji\n"; break;
		};


	}
}

//Wyswietlenie i zarzadzanie menu dla listy dwukierunkowej
void doubleLinkedListMenu() {
	DoubleLinkedList doubleLinkedList;
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
		userInput = readUserInput();
		if (userInput == -1) {
			continue;
		}

		//Uruchomienie odpowiedniej funkcji w zaleznosci od wyboru
		switch (userInput) {
		case 1: {
			string filename;
			cout << "Podaj nazwe pliku ";
			cin >> filename;
			doubleLinkedList.readFromFile(filename);
		}; break;
		case 2: {
			cout << "Podaj wartosc ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}
			doubleLinkedList.addElement(userInput);
		}; break;
		case 3: {
			cout << "Podaj wartosc ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}

			int position;
			cout << "Podaj pozycje na ktorej chcesz dodac element ";
			//Odczyt wyboru uzytkownika
			position= readUserInput();
			if (position == -1) {
				break;
			}
			
			doubleLinkedList.addElementAtPosition(position, userInput);
		}
		case 4: {
			doubleLinkedList.deleteElement();
		}; break;
		case 5: {
			cout << "Podaj pozycje usuwanego elementu ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}
			doubleLinkedList.deleteElementAtPosition(userInput);
		}; break;
		case 6: {
			doubleLinkedList.showElements();
		}; break;
		case 7: {
			cout << "Podaj wartosc do wyszukania ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}

			doubleLinkedList.findElement(userInput);
		}; break;
		case 8: {
			cout << "Podaj ilosc elementow ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}
			if (userInput <= 0) {
				cout << "Nieprawidlowa ilosc\n";
				break;
			}

			doubleLinkedList.fillList(userInput);
		}; break;
		case 0: return;
		default: cout << "Nie ma takiej opcji\n"; break;
		};
	}
}

//Wyswietlenie i zarzadzanie menu dla listy dwukierunkowej
void binaryHeapMenu() {
	BinaryHeap binaryHeap;
	while (1) {
		//Wyswietlenie opcji w menu
		cout << "\nWybierz opcje:\n";
		cout << "1. Odczytaj dane z pliku\n";
		cout << "2. Dodaj element do kopca\n";
		cout << "3. Usun element ze szczytu kopca\n";
		cout << "4. Wyswietl wszystkie wartosci\n";
		cout << "5. Znajdz wartosc w kopcu\n";
		cout << "6. Wygeneruj wartosci losowe\n";
		cout << "0. Cofnij do menu glownego\n";
		cout << "Podaj odpowiednia liczbe\n";

		//Odczyt wyboru uzytkownika
		int userInput;
		userInput = readUserInput();
		if (userInput == -1) {
			continue;
		}

		//Uruchomienie odpowiedniej funkcji w zaleznosci od wyboru
		switch (userInput) {
		case 1: {
			string filename;
			cout << "Podaj nazwe pliku ";
			cin >> filename;
			binaryHeap.readFromFile(filename);
		}; break;
		case 2: {
			cout << "Podaj wartosc ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}
			binaryHeap.addElement(userInput);
		}; break;
		case 3: {
			binaryHeap.deleteElement();
		}; break;
		case 4: {
			binaryHeap.showElements();
		}; break;
		case 5: {
			cout << "Podaj wartosc wyszukiwanego elementu ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}
			binaryHeap.findElement(userInput);
		}; break;
		case 6: {
			cout << "Podaj ilosc elementow ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}
			if (userInput <= 0) {
				cout << "Nieprawidlowa ilosc\n";
				break;
			}

			binaryHeap.fillHeap(userInput);
		}; break;
		case 0: return;
		default: cout << "Nie ma takiej opcji\n"; break;
		}
	}
}

//Menu wyboru do BST
void bstStructureMenu() {
	Bst bst;
	while (1) {
		//Wyswietlenie opcji w menu
		cout << "\nWybierz opcje:\n";
		cout << "1. Odczytaj dane z pliku\n";
		cout << "2. Dodaj element do drzewa\n";
		cout << "3. Usun wybrany element\n";
		cout << "4. Wyswietl wszystkie wartosci\n";
		cout << "5. Znajdz wartosc w drzewie\n";
		cout << "6. Wygeneruj wartosci losowe\n";
		cout << "7. Wykonaj rownowazenie algorytmem DSW\n";
		cout << "8. Wykonaj rotacje w prawo dla wybranego elementu\n";
		cout << "9. Wykonaj rotacje w lewo dla wybranego elementu\n";
		cout << "0. Cofnij do menu glownego\n";
		cout << "Podaj odpowiednia liczbe\n";

		//Odczyt wyboru uzytkownika
		int userInput;
		userInput = readUserInput();
		if (userInput == -1) {
			continue;
		}

		//Uruchomienie odpowiedniej funkcji w zaleznosci od wyboru
		switch (userInput) {
		case 1: {
			string filename;
			cout << "Podaj nazwe pliku ";
			cin >> filename;
			bst.readFromFile(filename);
		}; break;
		case 2: {
			cout << "Podaj wartosc ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}
			bst.addElement(userInput);
		}; break;
		case 3: {
			cout << "Podaj wartosc ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}
			bst.deleteElement(userInput);
		}; break;
		case 4: {
			bst.showElements();
		}; break;
		case 5: {
			cout << "Podaj wartosc wyszukiwanego elementu ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}
			bst.findElement(userInput);
		}; break;
		case 6: {
			cout << "Podaj ilosc elementow ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}
			if (userInput <= 0) {
				cout << "Nieprawidlowa ilosc\n";
				break;
			}

			bst.fillBst(userInput);
		}; break;
		case 7: {
			bst.dswBalance();
		}; break;
		case 8: {
			cout << "Podaj wartosc elementu, na ktorym chcesz wykonac rotacje w prawo: ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}
			bst.rotateRight(userInput);
		}; break;
		case 9: {
			cout << "Podaj wartosc elementu, na ktorym chcesz wykonac rotacje w lewo: ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}
			bst.rotateLeft(userInput);
		}; break;
		case 0: return;
		default: cout << "Nie ma takiej opcji\n"; break;
		}
	}
}

//Menu wyboru do RBT
void redBlackTreeMenu() {
	RedBlackTree rbt;
	while (1) {
		//Wyswietlenie opcji w menu
		cout << "\nWybierz opcje:\n";
		cout << "1. Odczytaj dane z pliku\n";
		cout << "2. Dodaj element do drzewa\n";
		cout << "3. Usun element z drzewa\n";
		cout << "4. Wyswietl wszystkie wartosci\n";
		cout << "5. Znajdz wartosc w drzewie\n";
		cout << "6. Wygeneruj wartosci losowe\n";
		cout << "0. Cofnij do menu glownego\n";
		cout << "Podaj odpowiednia liczbe\n";

		//Odczyt wyboru uzytkownika
		int userInput;
		userInput = readUserInput();
		if (userInput == -1) {
			continue;
		}

		//Uruchomienie odpowiedniej funkcji w zaleznosci od wyboru
		switch (userInput) {
		case 1: {
			string filename;
			cout << "Podaj nazwe pliku ";
			cin >> filename;
			rbt.readFromFile(filename);
		}; break;
		case 2: {
			cout << "Podaj wartosc ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}
			rbt.addElement(userInput);
		}; break;
		case 3: {
			cout << "Podaj wartosc ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}
			rbt.deleteElement(userInput);
		}; break;
		case 4: {
			rbt.showElements();
		}; break;
		case 5: {
			cout << "Podaj wartosc wyszukiwanego elementu ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}
			rbt.findElement(userInput);
		}; break;
		case 6: {
			cout << "Podaj ilosc elementow ";
			//Odczyt wyboru uzytkownika
			userInput = readUserInput();
			if (userInput == -1) {
				break;
			}
			if (userInput <= 0) {
				cout << "Nieprawidlowa ilosc\n";
				break;
			}

			rbt.fillRbt(userInput);
		}; break;
		case 0: return;
		default: cout << "Nie ma takiej opcji\n"; break;
		}
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
		userInput = readUserInput();
		if (userInput == -1) {
			continue;
		}

		//Uruchomienie odpowiedniej funkcji w zaleznosci od wyboru
		switch (userInput) {
		case 1: dynamicArrayMenu(); break;
		case 2: doubleLinkedListMenu(); break;
		case 3: binaryHeapMenu(); break;
		case 4: bstStructureMenu(); break;
		case 5: redBlackTreeMenu(); break;
		case 0: exit(0);
		default: cout << "Nie ma takiej opcji\n"; break;
		};

	}
}

int main() {
	system("color f0");
	dataStructuresMenu();
}


