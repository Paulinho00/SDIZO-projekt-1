#include <iostream>
using namespace std;

//Klasa reprezentuj�ca tablic� dynamiczn�
class DynamicArray {
private:
	//Wska�nik na tablic�
	int* array;
	//Rozmiar tablicy
	int* size = 0;
public:
	//Menu wyboru opcji
	void handleMenu();
	//Odczyt elementow z pliku
	void readFromFile();
	//Dodawanie elementu na ko�cu tablicy
	void addElementAtEnd();
	//Dodawanie elementu na pocz�tku tablicy
	void addElementAtBeginning();
	//Dodawanie elementu w okreslonym indeksie
	void addAtIndex(int index);
	//Usuni�cie elementu na ko�cu tablicy
	void deleteElementAtEnd();
	//Usuni�cie elementu na pocz�tku tablicy
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

