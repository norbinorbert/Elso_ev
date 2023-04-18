#include <iostream>
#include "OupSz_Sor.h"
#include "OupSz_Utemezo.h"

using namespace std;

int main()
{
	cout << "Sor tesztelese: " << endl;
	OupSz_Sor a(5);
	cout << a.PopElement() << endl;

	a.InsertElement(-1000000000);
	cout << a.PopElement() << endl;

	a.InsertElement(-1000000);
	a.InsertElement(15);
	cout << a.PopElement() << endl;

	a.InsertElement(20);
	a.InsertElement(1);
	a.InsertElement(12);
	a.InsertElement(8);
	a.InsertElement(5);
	a.InsertElement(15);
	cout << a.PopElement() << endl;
	a.InsertElement(123);

	a.PrintList();

	cout << "Utemezo tesztelese: " << endl;
	OupSz_Utemezo b(5, 5);
	cout << b.PickProcess() << endl;

	b.InsertProcess(0, 12);
	b.InsertProcess(1, 15);
	b.InsertProcess(2, -1000000);
	b.InsertProcess(3, 4);
	b.InsertProcess(4, -1000000000);
	cout << b.PickProcess() << endl;
	
	b.InsertProcess(2, 5);
	b.InsertProcess(2, 6);
	cout << "Az utemezo tartalma: " << endl;
	
	b.PrintProcesses();

	OupSz_Utemezo c(3, 1);
	c.InsertProcess(1, 2);
	c.InsertProcess(1, 3);
	c.InsertProcess(1, 10);
	cout << "c tartalma: " << endl;
	c.PrintProcesses();
	return 0;
}