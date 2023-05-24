#ifndef BINOMIALIS_KUPAC_H
#define BINOMIALIS_KUPAC_H

class binomialis_kupac {
	struct node {
		node* szulo;
		int adat;
		unsigned int fokszam;
		node* gyerek;
		node* testver;
	};
	node* fej;

	//rekurzivan felszabaditja egy csomopont gyerekeit es testvereit, majd a csomopontot
	void destroy(node*);

	//osszefesuli ket binomialis kupac fejenek a lancolt listajat es visszateriti az uj listafejet
	node* osszefesul(node*, node*);

	//osszekapcsolja ket binomialis fa gyokeret, egyik a masik gyereke lesz
	void binomialis_osszekapcsolas(node*, node*);

	//visszaterit egy mutatot a minimum elemre
	node* minimum_node();

public:

	//letrehoz egy ures binomialis kupacot, aminek a fej mutatoja NULL
	binomialis_kupac();

	//felszabaditja a binomialis kupac osszes csomopontjat
	~binomialis_kupac();

	//beszur egy csomopontot a kupacba, aminek a kulcsat parameterkent kell megadni
	void beszur(int);

	//az elso binomialis kupacot egyesiti a parameterkent megadott kupaccal;
	//az elso kupac tartalmazni fogja az osszes csomopontot, a masodik ures marad
	void egyesit(binomialis_kupac*);

	//visszateriti a binomialis kupac minimum elemenek az erteket
	int minimum();

	//kitorli a binomialis kupac minimum elemet
	void torol_minimum();
};

#endif // !BINOMIALIS_KUPAC_H
