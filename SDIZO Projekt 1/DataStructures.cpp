
//Klasa reprezentujaca tablice dynamiczna
class DynamicArray {
private:
	//Wskaznik na dynamiczna tablice
	int* array;
	//Wielkosc tablicy
	int size;
public:
	DynamicArray() {
		array = nullptr;
		size = 0;
	}
	~DynamicArray() {
		delete[] array;
	}

};