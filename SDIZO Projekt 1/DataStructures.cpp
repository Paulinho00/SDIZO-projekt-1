#include <iostream>
#include <fstream>
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

	//Odczytuje do tablicy, dane z pliku
	void readFromFile(string filename) {
		//Otwarcie pliku
		fstream file;
		file.open(filename, ios::in);
		//Sprawdzenie poprawnosci otwarcia
		if (file.is_open()) {

			//Odczyt rozmiaru danych zawartych w pliku
			int size;
			file >> size;

			//Sprawdzenie poprawnosci odczytu rozmiaru danych
			if (file.fail()) {
				cout << "Blad odczytu dlugosci pliku";
			}
			else {
				
				//Odczyt wszystkich danych z pliku
				for (int i = 0; i < size; i++) {
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
		
		//Zastapienie starej tablicy nowa
		delete[] array;
		array = buff;
	}

	//Dodaje element do tablicy w okreslonym indeksie
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

		//Zastapienie starej tablicy nowa
		delete[] array;
		array = buff;
	}

	//Usuwa ostatni element w tablicy
	void deleteElement() {
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
	void deleteElementAtIndex(int index) {
		//Sprawdzenie czy tablica jest pusta
		if (array == nullptr) {
			cout << "Tablica jest pusta\n";
			return;
		}
		//Sprawdzenie czy wybrany indeks jest poprawny
		if (index >= size || index < 0) {
			cout << "Nie ma takiego indeksu w tablicy\n\n";
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
	void showElements() {
		cout << "Wartosci: ";
		for (int i = 0; i < size; i++) {
			cout << array[i] << ", ";
		}
		cout << "\n";
	}

	//Wyszukiwanie indeksow na ktorym znajduje sie podana wartosc
	void findElement(int value) {
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
};

