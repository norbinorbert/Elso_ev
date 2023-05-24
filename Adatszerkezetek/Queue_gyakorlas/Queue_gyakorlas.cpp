#include <iostream>
#include "queue.h"

using namespace std;

int main()
{
	queue a;
	a.pop();
	cout << a.IsEmpty() << endl;
	a.push(3);
	a.push(1);
	cout << a.IsEmpty() << endl;
	a.push(5);
	a.ListQueue();
	cout << a.front() << " ";
	a.pop();
	cout << a.front();
	a.pop();
	return 0;
}
