//Boda Norbert, 511

#include <iostream>

using namespace std;

class buvos_negyzet {
protected:
	int lehetseges[9];
	bool volt[9];
	int negyzet[9];
public:
	buvos_negyzet();
	virtual bool isOk();
	int backtrack();
	void backtracking(int, int, int&);
};

buvos_negyzet::buvos_negyzet() {
	for (int i = 0; i < 9; i++) {
		lehetseges[i] = (i + 1) * (i + 1);
		volt[i] = false;
		negyzet[i] = 0;
	}
}

int buvos_negyzet::backtrack() {
	int db = 0;
	backtracking(0, 0, db);
	return db;
}

void buvos_negyzet::backtracking(int lepes, int index, int& db) {
	if (lepes == 9) {
		if (isOk()) {
			db++;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					cout << negyzet[i * 3 + j] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		return;
	}

	for (int i = 0; i < 9; i++) {
		if (!volt[i]) {
			negyzet[index] = i + 1;
			volt[i] = true;
			backtracking(lepes + 1, index + 1, db);
			volt[i] = false;
		}
	}
}

bool buvos_negyzet::isOk() {
	int osszeg = 15;
	for (int i = 0; i < 3; i++) {
		int tmp_sor = 0, tmp_oszlop = 0;
		for (int j = 0; j < 3; j++) {
			tmp_sor += negyzet[i * 3 + j];
			tmp_oszlop += negyzet[j * 3 + i];
		}
		if (osszeg != tmp_sor || osszeg != tmp_oszlop) {
			return false;
		}
	}
	return true;
}

//------------------------------------------------------------
class atlok_egyenlok : virtual public buvos_negyzet {
	bool isOk();
};

bool atlok_egyenlok::isOk() {
	if (!buvos_negyzet::isOk()) {
		return false;
	}
	int osszeg = 15;
	int foatlo = negyzet[0] + negyzet[4] + negyzet[8];
	if (foatlo != osszeg) {
		return false;
	}
	int mellekatlo = negyzet[2] + negyzet[4] + negyzet[6];
	if (mellekatlo != osszeg) {
		return false;
	}
	return true;
}

//------------------------------------------------------------
class atlok_kulonboznek : virtual public buvos_negyzet {
	bool isOk();
};

bool atlok_kulonboznek::isOk() {
	if (!buvos_negyzet::isOk()) {
		return false;
	}
	int foatlo = negyzet[0] + negyzet[4] + negyzet[8];
	int mellekatlo = negyzet[2] + negyzet[4] + negyzet[6];
	if (foatlo - mellekatlo != 3) {
		return false;
	}
	return true;
}

//------------------------------------------------------------
int main()
{
	buvos_negyzet a;
	int db_a = a.backtrack();
	cout << db_a << " buvos negyzet" << endl << "----------------------------------------" << endl;

	atlok_egyenlok b;
	int db_b = b.backtrack();
	cout << db_b << " buvos negyzet, ahol az atlok egyenlok" << endl << "----------------------------------------" << endl;

	atlok_kulonboznek c;
	int db_c = c.backtrack();
	cout << db_c << " buvos negyzet, ahol a foatlo 3-mal nagyobb, mint a mellekatlo" << endl;
	return 0;
}
