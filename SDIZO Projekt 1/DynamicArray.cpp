#include <iostream>
#include <fstream>
#include <time.h>
#include "DataStructures.h"
using namespace std;

DynamicArray::DynamicArray() {
	array = nullptr;
	size = 0;
}
DynamicArray::~DynamicArray() {
	delete[] array;
}

//Odczytuje do tablicy, dane z pliku
void DynamicArray::readFromFile(string filename) {
	//Usuniecie struktury
	if (array != nullptr) {
		delete[] array;
		size = 0;
	}
	//Otwarcie pliku
	fstream file;
	file.open(filename, ios::in);
	//Sprawdzenie poprawnosci otwarcia
	if (file.is_open()) {

		//Odczyt rozmiaru danych zawartych w pliku
		int sizeOfData;
		file >> sizeOfData;

		//Sprawdzenie poprawnosci odczytu rozmiaru danych
		if (file.fail()) {
			cout << "Blad odczytu dlugosci pliku";
		}
		else {

			//Odczyt wszystkich danych z pliku
			for (int i = 0; i < sizeOfData; i++) {
				int value;
				file >> value;
				//Sprawdzanie czy ka¿dy element zostal poprawnie odczytany
				if (file.fail()) {
					cout << "Blad odczytu danych";
				}
				else {
					//Dodanie danej do tablicy
					addElement(value);
				}
				//Zamkniêcie pliku

			}
			file.close();
		}

	}
	else {
		cout << "Blad otwarcia pliku\n";
	}
}

//Dodaje element na koncu tablicy
void DynamicArray::addElement(int value) {
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
	for (int i = 0; i < size - 1; i++) {
		buff[i] = array[i];
	}
	buff[size - 1] = value;

	//Zastapienie starej tablicy nowa
	delete[] array;
	array = buff;
}

//Dodaje element do tablicy w okreslonym indeksie
void DynamicArray::addElementAtIndex(int index, int value) {
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

	//Sprawdzenie czy element ma zostac dodany na koncu
	if (index == size) {
		addElement(value);
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

	//Zastapienie starej tablicy nowa
	delete[] array;
	array = buff;
}

//Usuwa ostatni element w tablicy
void DynamicArray::deleteElement() {
	//Sprawdzenie czy tablica jest pusta
	if (array == nullptr) {
		cout << "Tablica jest pusta\n";
		return;
	}
	//Sprawdzenie czy tablica ma tylko jeden element
	if (size == 1) {
		//Usuniecie tablicy
		size--;
		delete[] array;
		array = nullptr;
		return;
	}

	//Zmniejszenie rozmiaru i utworzenie buforu
	size--;
	int* buff = new int[size];

	//Przepisanie tablicy bez ostatniego elementu
	for (int i = 0; i < size; i++) {
		buff[i] = array[i];
	}

	//Zastapienie starej tablicy nowa
	delete[] array;
	array = buff;

}

//Usuwa element na podanym indeksie
void DynamicArray::deleteElementAtIndex(int index) {
	//Sprawdzenie czy wybrany indeks jest poprawny
	if (index >= size || index < 0) {
		cout << "Nie ma takiego indeksu w tablicy\n\n";
		return;
	}

	//Sprawdzenie czy tablica jest pusta
	if (array == nullptr) {
		cout << "Tablica jest pusta\n";
		return;
	}

	//Zmniejszenie rozmiaru i utworzenie buforu
	size--;
	int* buff = new int[size];

	//Przepisanie tablicy bez usuwanego elementu
	for (int i = 0; i < index; i++) {
		buff[i] = array[i];
	}
	for (int i = index; i < size; i++) {
		buff[i] = array[i + 1];
	}

	//Zastapienie starej tablicy nowa
	delete[] array;
	array = buff;

}

//Wyswietla zawartosc tablicy
void DynamicArray::showElements() {

	//Wypisywanie tablicy
	cout << "Wartosci: ";
	for (int i = 0; i < size; i++) {
		cout << array[i] << ", ";
	}
	cout << "\n";
	
	//Wypisywanie w odwrotnej kolejnosci
	cout << "Odwrocona kolejnosc: ";
	for (int i = size - 1; i >= 0; i--) {
		cout << array[i] << ", ";
	}
	cout << "\n";

}

//Wyszukiwanie indeksow na ktorym znajduje sie podana wartosc
void DynamicArray::findElement(int value) {
	//Zmienna przechowujaca informacje czy znaleziono taka wartosc
	bool foundValues = false;

	cout << "\nLiczby o zadanej wartosci znajduja sie na indeksach: ";

	//Petla przeszukujaca
	for (int i = 0; i < size; i++) {
		if (array[i] == value) {
			//Wyswietlenie odpowiedniego indeksu
			cout << i << " ";
			//Zapisanie informacji o znalezieniu wartosci
			foundValues = true;
		}
	}
	//Komunikat o braku takiej wartosci
	if (!foundValues) cout << "Nie ma takiej wartosci ";
	cout << "\n";
}

//Generowanie okreslonej liczby wartosci w strukturze
void DynamicArray::fillArray(int amount) {
	//Usuniecie istniejacej tablicy
	if (array != nullptr) {
		delete[] array;
		size = 0;
	}

	//Alokacja nowej tablicy
	array = new int[amount];

	//Wypelnienie tablicy losowymi elementami
	for (int i = 0; i < amount; i++) {
		int value = randomValue();
		array[i] = value;
		size++;
	}
}








