/*Boda Norbert
511-es csoport
Lab8/06
Alejandro a hegyekben sétál és bejár 𝑛 tisztást, melyek 1-től 𝑛-ig vannak
megszámozva. Minden tisztáson gyöngyvirágok, tulipánok és liliomok nőnek.
Alejandro a tisztásokat számozásuk szerlong long növekvő sorrendben járja be, amíg
ki nem lép az 𝑛-edik tisztásról, ahol vár rá Stefani. A lány szeretne virágokat
kapni, nem számít hányat és milyent. Az első tisztáson Alejandro kiválaszt egy
virágfajtát és minden ilyen virágot magával visz. A következő tisztásokon leteszi
ezeket a virágokat, kiválaszt egy virágfajtát és magával visz minden virágot,
beleértve azokat is, amelyeket a tisztásra érve letett, ha ezeknek ugyanaz a
típusa, mlong long amit kiválasztott az aktuális tisztáson. Ismerve az egyes tisztásokon
található gyöngyvirágok, tulipánok és liliomok számát, határozzátok meg azt a
legkisebb számú virágot, amelyet Alejandronak szállítania kell.*/

#include <iostream>
#include <vector>

using namespace std;

struct viragok {
	long long gyongyvirag, tulipan, liliom;
};

void beolvas(short& tisztasok_szama, vector<viragok>& tisztas) {
	cin >> tisztasok_szama;
	tisztas.resize(tisztasok_szama);
	for (short i = 0; i < tisztasok_szama; i++) {
		cin >> tisztas[i].gyongyvirag >> tisztas[i].tulipan >> tisztas[i].liliom;
	}
}

//visszateriti 3 elem minimumat
long long minimum(long long a, long long b, long long c) {
	cerr << a << " " << b << " " << c << endl;
	if (a < b) {
		return (a < c) ? a : c;
	}
	else {
		return (b < c) ? b : c;
	}
}

vector<viragok> Viragok(short& tisztasok_szama, vector<viragok>& tiszas) {
	vector<viragok> szallitott_mennyiseg(tisztasok_szama);
	szallitott_mennyiseg[0].gyongyvirag = tiszas[0].gyongyvirag;
	szallitott_mennyiseg[0].tulipan = tiszas[0].tulipan;
	szallitott_mennyiseg[0].liliom = tiszas[0].liliom;
	//a PDF-ben szereplo Almak es Kortek feladat megoldasanak egy modosult valtozata a levezetes
	//a lenyeges kulonbseg, hogy 3 sort kell levezetni, illetve a minimum elemeket kell nezni maximum helyett
	for (short i = 1; i < tisztasok_szama; i++) {
		//gyongyvirag sora
		long long gyongyvirag_sora = tiszas[i].gyongyvirag;
		gyongyvirag_sora = min(gyongyvirag_sora + szallitott_mennyiseg[i - 1].tulipan, gyongyvirag_sora + szallitott_mennyiseg[i - 1].liliom);

		long long temp_gyongyvirag = tiszas[i].gyongyvirag;
		for (short j = i - 1; j > 0; j--) {
			temp_gyongyvirag += (tisztasok_szama - j) * tiszas[j].gyongyvirag;
			gyongyvirag_sora = minimum(gyongyvirag_sora, temp_gyongyvirag + szallitott_mennyiseg[j - 1].tulipan, temp_gyongyvirag + szallitott_mennyiseg[j - 1].liliom);
		}
		temp_gyongyvirag += tisztasok_szama * tiszas[0].gyongyvirag;
		gyongyvirag_sora = min(gyongyvirag_sora, temp_gyongyvirag);

		szallitott_mennyiseg[i].gyongyvirag = gyongyvirag_sora;

		//tulipan sora
		long long tulipan_sora = tiszas[i].tulipan;
		tulipan_sora = min(tulipan_sora + szallitott_mennyiseg[i - 1].gyongyvirag, tulipan_sora + szallitott_mennyiseg[i - 1].liliom);

		long long temp_tulipan = tiszas[i].tulipan;
		for (short j = i - 1; j > 0; j--) {
			temp_tulipan += (tisztasok_szama - j) * tiszas[j].tulipan;
			tulipan_sora = minimum(tulipan_sora, temp_tulipan + szallitott_mennyiseg[j - 1].gyongyvirag, temp_tulipan + szallitott_mennyiseg[j - 1].liliom);
		}
		temp_tulipan += tisztasok_szama * tiszas[0].tulipan;
		tulipan_sora = min(tulipan_sora, temp_tulipan);

		szallitott_mennyiseg[i].tulipan = tulipan_sora;

		//liliom sora
		long long liliom_sora = tiszas[i].liliom;
		liliom_sora = min(liliom_sora + szallitott_mennyiseg[i - 1].gyongyvirag, liliom_sora + szallitott_mennyiseg[i - 1].tulipan);

		long long temp_liliom = tiszas[i].liliom;
		for (short j = i - 1; j > 0; j--) {
			temp_liliom += (tisztasok_szama - j) * tiszas[j].liliom;
			liliom_sora = minimum(liliom_sora, temp_liliom + szallitott_mennyiseg[j - 1].gyongyvirag, temp_liliom + szallitott_mennyiseg[j - 1].tulipan);
		}
		temp_liliom += tisztasok_szama * tiszas[0].liliom;
		liliom_sora = min(liliom_sora, temp_liliom);

		szallitott_mennyiseg[i].liliom = liliom_sora;
	}

	return szallitott_mennyiseg;
}

void kiir(vector<viragok>& szallitott_mennyiseg) {
	//megnezi, hogy az utolso 3 elem kozul melyik a legkisebb es azt irja ki
	cout << minimum(szallitott_mennyiseg[szallitott_mennyiseg.size() - 1].gyongyvirag,
		szallitott_mennyiseg[szallitott_mennyiseg.size() - 1].tulipan, szallitott_mennyiseg[szallitott_mennyiseg.size() - 1].liliom);
}

int main() {
	short tisztasok_szama;
	vector<viragok> tisztas;
	beolvas(tisztasok_szama, tisztas);

	vector<viragok> szallitott_mennyiseg = Viragok(tisztasok_szama, tisztas);

	kiir(szallitott_mennyiseg);
	return 0;
}