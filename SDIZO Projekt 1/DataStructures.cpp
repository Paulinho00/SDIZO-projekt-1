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
		memcpy_s(buff, size * sizeof(int), array, (size - 1) * sizeof(int));
		buff[size-1] = value;
		
		//Zastapienie starej tablicy nowa, wieksza
		delete[] array;
		array = buff;
	}

	//Wyswietlanie tablicy
	void showElements() {
		cout << "Wartosci: ";
		for (int i = 0; i < size; i++) {
			cout << array[i] << ", ";
		}
	}
};