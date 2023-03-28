#include "halasto.h"
#include <iostream>

using namespace std;

int main() {
	Init();
	Halasto* to = CreateFromFile("pelda.txt");
	PrintH(to);
	FajtaElofordulasa(to);
	Destroy(to);
	return 0;
}