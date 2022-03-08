#include <iostream>
using namespace std;

//Klasa reprezentujaca tablice dynamiczna
class DynamicArray {
private:
	//Wskaznik na dynamiczna tablice
	int* array;
	//Wielkosc tablicy
	long long size;
public:
	DynamicArray() {
		array = nullptr;
		size = 0;
	}
	~DynamicArray() {
		delete[] array;
	}

	//Dodawanie elementu na koncu tablicy
	void addElement(int value) {
		//Sprawdzenie czy tablica jest zainicjalizowana
		if (array == nullptr) {
			//Inicjalizacja tablicy i zwiekszenie rozmiaru
			size++;
			array = new int[size];
			array[0] = value;
			return;
		}

		//Zwiekszenie rozmiaru
		size++;
		//Stworzenie i wypelnienie buforu
		int* buff = new int[size];
		for (int i = 0; i < size-1; i++) {
			buff[i] = array[i];
		}
		buff[size-1] = value;
		
		//Zastapienie starej tablicy nowa, wieksza
		delete[] array;
		array = buff;
	}

	//Dodawanie elementu na okreslonym indeksie
	void addElementAtIndex(int index, int value) {
		//Sprawdzenie czy tablica jest zainicjalizowana
		if (array == nullptr && index == 0) {
			//Inicjalizacja tablicy i zwiekszenie rozmiaru
			size++;
			array = new int[size];
			array[0] = value;
			return;
		}
		//Sprawdzenie czy wybrany indeks jest poprawny
		if (index > size || index < 0) {
			cout << "Nie ma takiego indeksu w tablicy\n\n";
			return;
		}

		//Zwiêkszenie rozmiaru tablicy i utworzenie buforu
		size++;
		int* buff = new int[size];
		
		//Przepisanie tablicy do buforu z uwzglednieniem nowego elementu
		for (int i = 0; i < index; i++) {
			buff[i] = array[i];
		}
		buff[index] = value;
		for (int i = index + 1; i < size; i++) {
			buff[i] = array[i - 1];
		}

		//Usuniecie starej tablicy
		delete[] array;
		//Ustawienie wskaznika na bufor jako nowa tablica
		array = buff;
	}

	//Wyswietlanie tablicy
	void showElements() {
		cout << "Wartosci: ";
		for (int i = 0; i < size; i++) {
			cout << array[i] << ", ";
		}
		cout << "\n";
	}
};