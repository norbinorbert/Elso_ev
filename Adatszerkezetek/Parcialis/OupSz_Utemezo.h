#ifndef OupSz_Utemezo_h
#define OupSz_Utemezo_h

#include "OupSz_Sor.h"

class OupSz_Utemezo {
	int sorok_szama;
	int max_hossz;
	OupSz_Sor** a;
public:
	OupSz_Utemezo(int, int);
	~OupSz_Utemezo();
	void InsertProcess(int, int);
	int PickProcess();
	void PrintProcesses();
};

#endif // !OUPSZ_UTEMEZO_H
