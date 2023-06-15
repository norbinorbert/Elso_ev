//Boda Norbert, 511

#include <iostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

template <typename A, typename B>
class HashTable {
	vector<list<pair<A, B>>> tabla;

	int HashFunction(A);

public:
	HashTable(int);
	B& operator [](A);
};

template <typename A, typename B>
HashTable<A, B>::HashTable(int meret) {
	tabla.resize(meret);
}

template <typename A, typename B>
int HashTable<A, B>::HashFunction(A kulcs) {
	unsigned char index = 0;
	memcpy(&index, &kulcs, sizeof(unsigned char));
	return index % tabla.size();
}

template <typename A, typename B>
B& HashTable<A, B>::operator [](A kulcs) {
	int index = HashFunction(kulcs);
	for (auto i : tabla[index]) {
		if (i.first == kulcs) {
			return i.second;
		}
	}
	tabla[index].push_back({ kulcs, NULL });
	return tabla[index].back().second;
}

int main() {
	HashTable<int, int> A(11);
	string a;
	A[15] = 100;
	cout << A[15] << endl;

	A[100] = 14;
	cout << A[12] << endl;
	return 0;
}