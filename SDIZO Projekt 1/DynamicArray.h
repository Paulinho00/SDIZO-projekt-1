#include <iostream>
using namespace std;

//Klasa reprezentuj¹ca tablicê dynamiczn¹
class DynamicArray {
private:
	//WskaŸnik na tablicê
	int* array;
	//Rozmiar tablicy
	int* size = 0;
public:
	//Menu wyboru opcji
	void handleMenu();
	//Odczyt elementow z pliku
	void readFromFile();
	//Dodawanie elementu na koñcu tablicy
	void addElementAtEnd();
	//Dodawanie elementu na pocz¹tku tablicy
	void addElementAtBeginning();
	//Dodawanie elementu w okreslonym indeksie
	void addAtIndex(int index);
	//Usuniêcie elementu na koñcu tablicy
	void deleteElementAtEnd();
	//Usuniêcie elementu na pocz¹tku tablicy
	void deleteElementAtBeginning();
	//Usuwanie elementu na podanym indeksie
	void deleteElementByIndex(int index);
	//Wyswietlenie wszystkich elementow
	void showAllElements();
	//Wyswietlenie elementu na podanym indeksie
	void showElementAtIndex(int index);
	//Wyswietlenie elementow o danej wartosci
	void findElementByValue(int value);
};

