#include "binaris_keresofa.h"
#include <iostream>

using namespace std;

int main() {
	binaris_keresofa a;
	a.beszuras(13);
	a.beszuras(12.5);
	a.beszuras(15.3);
	a.beszuras(1);
	a.beszuras(123);
	a.beszuras(2);
	a.beszuras(14);
	cout << a.kereses(89) << endl;
	cout << a.kereses(13);
	a.torles(12.5);
	return 0;
}