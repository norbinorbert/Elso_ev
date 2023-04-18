#ifndef OupSz_Sor_h
#define OupSz_Sor_h

class OupSz_Sor {
	int meret;
	int utolso_elem;
	int* tomb;
public:
	OupSz_Sor(int);
	~OupSz_Sor();
	bool InsertElement(int);
	int PopElement();
	void PrintList();
};

#endif // !OUPSZ_SOR_H
