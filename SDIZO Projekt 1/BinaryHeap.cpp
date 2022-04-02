#include "DataStructures.h"
#include <fstream>
using namespace std;

BinaryHeap::BinaryHeap() {
	dynArray = new DynamicArray();
}

BinaryHeap::~BinaryHeap() {
	dynArray->~DynamicArray();
}

//Odczytuje do kopca, dane z pliku
void BinaryHeap::readFromFile(std::string filename) {
	dynArray->readFromFile(filename);
	//Uporzadkowanie kopca
	heapCreateUp();
}

//Dodaje element do kopca
void BinaryHeap::addElement(int value) {
	//Dopisanie elementu do tablicy
	dynArray->addElement(value);

	//Odczyt indeksu nowego elementu
	int indexOfNewElement = dynArray->getSize() - 1;
	int* array = dynArray->getArray();

	//Sprawdzamy czy dodany element to korzen drzewa
	if (indexOfNewElement == 0) return;
	else {
		bool shouldContinueFixing = true;
		while (shouldContinueFixing) {
			int indexOfParent = (indexOfNewElement - 1) / 2;
			if (array[indexOfNewElement] > array[indexOfParent]) {
				//Zamiana miejsc z rodzicem nowego elementu
				int temp = array[indexOfParent];
				array[indexOfParent] = array[indexOfNewElement];
				array[indexOfNewElement] = temp;
				indexOfNewElement = indexOfParent;
				//Sprawdzenie czy algorytm doszedl do korzenia
				if (indexOfNewElement == 0) {
					shouldContinueFixing = false;
				}
			}
			else{
				//Zatrzymanie algorytmu
				shouldContinueFixing = false;
			}
		}
	}
}

//Usuwa element ze szczytu
void BinaryHeap::deleteElement() {
	//Pobranie tablicy w ktorej przechowywane sa elementy
	int* arr = dynArray->getArray();

	//Zmiana miejsca szczytu drzewa i ostatniego elementu w drzewie
	int root = arr[0];
	arr[0] = arr[(dynArray->getSize()) - 1];
	arr[(dynArray->getSize()) - 1] = root;

	//Usuniecie ostatniego elementu
	dynArray->deleteElement();
	
	//Wywolanie funkcji naprawiajacej w dol
	fixDown(0);

}

//Wyswietla zawartosc kopca
void BinaryHeap::showElements() {

	cout << "\n";
	//Wywolanie funkcji wypisujacej
	print("","",0);
}

//Wyszukuje elementy w drzewie
void BinaryHeap::findElement(int value) {
	//Zmienna przechowujaca informacje czy znaleziono taka wartosc
	bool foundValues = false;

	//Petla przeszukujaca
	for (int i = 0; i < dynArray->getSize(); i++) {
		if ((dynArray->getArray())[i] == value) {
			//Wyswietlenie odpowiedniego komunikatu
			cout <<" Element o wartosci: " << value << "\n";
			//Wyswietlenie informacji o rodzicu
			cout << "   Rodzic: ";
			if (i != 0) cout << (dynArray->getArray())[(i - 1) / 2] << "\n";
			else cout << "Brak\n";
			//Wyswietlenie informacji o lewym nastepniku
			cout << "   Lewy nastepnik: ";
			if ((2 * i + 1) < dynArray->getSize()) cout << (dynArray->getArray())[2 * i + 1] << "\n";
			else cout << "Brak\n";
			//Wyswietleie informacji o prawym nastepniku
			cout << "   Prawy nastepnik: ";
			if ((2 * i + 2) < dynArray->getSize()) cout << (dynArray->getArray())[2 * i + 2] << "\n";
			else cout << "Brak\n";
			cout << "\n";
			//Zapisanie informacji o znalezieniu wartosci
			foundValues = true;
		}
	}
	//Komunikat o braku takiej wartosci
	if (!foundValues) cout << "Nie ma takiej wartosci ";
	cout << "\n";
}

//Generowanie okreslonej liczby wartosci w strukturze
void BinaryHeap::fillHeap(int amount) {
	//Wypelnienie kopca elementami
	dynArray->fillArray(amount);

	//Uporzadkowanie kopca
	heapCreateUp();

}

//Funkcja wypisujaca dzieci danego elementu
void BinaryHeap::print(string prefix, string childrenPrefix, int position) {
	if (position < dynArray->getSize()) {
		cout << " " << prefix << "[" << dynArray->getArray()[position] << "]" << endl;
		int next;
		if ((2*position+1) < dynArray->getSize()) {
			next = 2*position+1;
			if (2 * position + 2 < dynArray->getSize()) {
				print(childrenPrefix + "  L--", childrenPrefix + "  |   ", (2 * position + 1));
			}
			else {
				print(childrenPrefix + "  L--", childrenPrefix + "      ", (2*position+1));
			}
		}
		if ((2 * position + 2) < dynArray->getSize()) {
			print(childrenPrefix + "  P--", childrenPrefix + "      ", (2*position+2));
		}
	}
}

//Naprawia kopiec algorytmem Floyda
void BinaryHeap::heapCreateUp() {

	//Wyszukanie pierwszego rodzica
	int firstParent = ((dynArray->getSize() - 2) / 2);
	for (int i = firstParent; i >= 0; i--) {
		//Wywolanie funkcji naprawiajacej
		fixDown(i);
	}
}

//Naprawia kopiec zaczynajac od danej pozycji
void BinaryHeap::fixDown(int index) {
	int* arr = dynArray->getArray();
	bool shouldContinueFixing = true;
	int currentIndex = index;
	while (shouldContinueFixing) {
		//Indeks lewego dziecka
		int leftChild = (2 * currentIndex) + 1;
		//Indeks prawego dziecka
		int rightChild = (2 * currentIndex) + 2;

		if (leftChild < dynArray->getSize() && (arr[leftChild] > arr[currentIndex])) {
			if (rightChild < dynArray->getSize() && (arr[rightChild] > arr[currentIndex])) {
				//Sprawdzenie ktory potomek jest wiekszy
				if (arr[leftChild] > arr[rightChild]) {
					//Zamiana miejsc z dzieckiem
					int temp = arr[leftChild];
					arr[leftChild] = arr[currentIndex];
					arr[currentIndex] = temp;
					currentIndex = leftChild;
				}
				else
				{
					//Zamiana miejsc z dzieckiem
					int temp = arr[rightChild];
					arr[rightChild] = arr[currentIndex];
					arr[currentIndex] = temp;
					currentIndex = rightChild;
				}
			}
			else {
				//Zamiana miejsc z dzieckiem
				int temp = arr[leftChild];
				arr[leftChild] = arr[currentIndex];
				arr[currentIndex] = temp;
				currentIndex = leftChild;
			}
		}
		else if (rightChild < dynArray->getSize() && (arr[rightChild] > arr[currentIndex])) {
			//Zamiana miejsc z dzieckiem
			int temp = arr[rightChild];
			arr[rightChild] = arr[currentIndex];
			arr[currentIndex] = temp;
			currentIndex = rightChild;
		}
		else {
			shouldContinueFixing = false;
		}
	}

}

