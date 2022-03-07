#include "DynamicArray.h"

void DynamicArray::handleMenu() {
	while (1) {
		cout << "Wybierz odpowiednia opcje:\n";
		cout << "1. Wczytaj dane z pliku\n";
		cout << "2. Dodaj element na koncu tablicy\n";
		cout << "3. Dodaj element na poczatku tablicy\n";
		cout << "4. Dodaj element na wybranym indeksie\n";
		cout << "5. Usun element na koñcu tablicy\n";
		cout << "6. Usun element na poczatku tablicy\n";
		cout << "7. Usun element na wybranym indeksie tablicy\n";
		cout << "8. Wyswietl wszystkie elementy\n";
		cout << "9. Wyswietl element na podanym indeksie\n";
		cout << "10. Wyszukaj podana wartosc w tablicy\n";

		int* choice = new int;

		cin >> *choice;
		switch (*choice) {
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: break;
		case 6: break;
		case 7: break;
		case 8: break;
		case 9: break;
		case 10: break;
		default: cout << "Nie ma takiej opcji"; break;
		}
		delete choice;
		cin.clear();
		cin.ignore(100, '\n');
	}
};