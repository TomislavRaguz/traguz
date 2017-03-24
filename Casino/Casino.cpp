// Casino.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

int g_pare=1000;
int g_cip=0;

void glavni_izbornik();

bool wayToSort(int i, int j) { return i > j; }

struct Karta {
	Karta(int a, int b) {
		vrijednost = a; switch (b) {
		case 1:
			tip = "pik";
			break;
		case 2:
			tip = "herc";
			break;
		case 3:
			tip = "tref";
			break;
		case 4:
			tip = "Kara";
			break;
		};
		switch (a) {
		case 1:
			lice = "as";
			break;
		case 2:
			lice = "dvica";
			break;
		case 3:
			lice = "trica";
			break;
		case 4:
			lice = "èetvorka";
			break;
		case 5:
			lice = "petica";
			break;
		case 6:
			lice = "šestica";
			break;
		case 7:
			lice = "sedmica";
			break;
		case 8:
			lice = "osmica";
			break;
		case 9:
			lice = "devetka";
			break;
		case 10:
			lice = "desetka";
			break;
		case 11:
			lice = "decko";
			break;
		case 12:
			lice = "dama";
			break;
		case 13:
			lice = "kralj";
			break;
		};
	}
	Karta() { vrijednost = 0; tip = 1; lice = 1; };
	int vrijednost;
	string tip;
	string lice;
};

void uplata() {
	int broj;
	cout << "\nKoliko novca zelite uloziti?(jedan cip je 5 kuna):";
	cin >> broj;
	int bcip = broj / 5;
	g_cip += bcip;
	g_pare -= bcip*5;
	cout << "\nImate " << g_pare << " kuna i " << g_cip << " cipova.";
	glavni_izbornik();
}

int isplata() {
	int broj;
	cout << "\nZelite zamjeniti za novac?Trenutno imate " << g_cip << " cipova.\nZa te cipove mozete dobiti"<<g_cip*5<<" kuna. Za odustajanje upisite 0:";
	cin >> broj;
	if (broj == 0) { return 0; }
	g_pare += g_cip * 5;
	ofstream dobitak("cdobitak.txt", ios::app);
	dobitak << "Korisnik je osvojio " << g_cip * 5 << " kuna.";
	dobitak.close();
	g_cip = 0;
	return 0;
	glavni_izbornik();
}

void jack() {
	int bet;
	int skor1 = 0, skor2 = 0, skor3 = 0;
	ifstream hiskor("higghscorejack.txt");
	hiskor >> skor1 >> skor2 >> skor3;
	vector<int> hiskore = { skor1,skor2,skor3 };
	hiskor.close();
	vector<char> polja = { '+', 'X', 'O', '*'};
	srand(time(NULL));
	cout << "One armed Jack!Enter a bet to pull, 0 to exit;";
	cin >> bet;
	while (bet != 0) {
		g_cip -= bet;
		int prvi = rand() % 4;
		int drugi = rand() % 4;
		int treci = rand() % 4;
		cout << polja[prvi] << polja[drugi] << polja[treci] << endl;
		if (prvi == drugi && drugi == treci) { cout << "Bingo!Osvojili ste" << bet * 20 << " zetona."; g_cip += bet * 15; hiskore.push_back((bet * 15)); sort(hiskore.begin(), (hiskore.begin() + 4),wayToSort); hiskore.pop_back();  }
		cout << "Trenutni balans: " << g_cip << endl;
		cin >> bet;
	}
	ofstream pisi("higghscorejack.txt");
	for (int i = 0; i < 3; i++) {
		pisi << hiskore[i] << endl;
	}
	pisi.close();
	glavni_izbornik();
}

void dice() {
	int skor1 = 0, skor2 = 0, skor3 = 0;
	ifstream hiskor("highscoredice.txt");
	hiskor >> skor1 >> skor2 >> skor3;
	vector<int> hiskore = { skor1,skor2,skor3 };
	hiskor.close();
	srand(time(NULL));
	cout << "--------------Dice----------------";
	int bet,prvi,drugi;
	cout << "\nKoliko zelite uloziti?";
	cin >> bet;
	while (bet != 0) {
	int sum_korisnik = 0;
	int sum_kuca = 0;
		g_cip -= bet;
		prvi = rand()% 6 + 1;
		drugi = rand() % 6 + 1;
		cout << "\nBacili ste " << prvi << " a dealer " << drugi<<endl;
		system("PAUSE");
		sum_korisnik += prvi;
		sum_kuca += drugi;
		prvi = rand() % 6 + 1;
		drugi = rand() % 6 + 1;
		cout << "\nBacili ste " << prvi << " a dealer " << drugi;
		sum_korisnik += prvi;
		sum_kuca += drugi;
		cout << "\nUkupno ste bacili " << sum_korisnik << " a kuca " << sum_kuca;
		if (sum_korisnik > sum_kuca) { cout << "\nCestitam! Pobjedili ste, uzivajte u dobitku"; g_cip += bet * 2; hiskore.push_back((bet * 2)); sort(hiskore.begin(), (hiskore.begin() + 4), wayToSort); hiskore.pop_back();}
		if (sum_kuca > sum_korisnik) { cout << "\nVise srece sljedeci puta."; }
		if (sum_kuca == sum_korisnik) { cout << "\nSkoro!Sljedeci put sigurno."; }
		cout << "\nZelite opet uloziti?0 ce vas vratiti u izbornik\n";
		cin >> bet;
	}
	ofstream pisi("highscoredice.txt");
	for (int i = 0; i < 3; i++) {
		pisi << hiskore[i] << endl;
	}
	pisi.close();
	glavni_izbornik();
}

void double_or() {
	int skor1 = 0, skor2 = 0, skor3 = 0;
	ifstream hiskor("highscoredouble.txt");
	hiskor >> skor1 >> skor2 >> skor3;
	vector<int> hiskore = { skor1,skor2,skor3 };
	hiskor.close();
	std::srand(time(NULL));
	int bet,prvi,drugi,izv_kart;
	Karta pkarta, dkarta;
	string input;
	std::cout << "\nKoliko zelite da vam bude pocetni ulog?";
	std::cin >> bet;
	g_cip -= bet;
		vector<Karta> deck;
		izv_kart = 0;
            for (int i = 1; i < 5; i++) {
		       for (int j = 1; j < 14; j++) {
			          deck.push_back(Karta(j,i));
		}
	}
			prvi = rand() % (52 - izv_kart);
			pkarta = deck[prvi]; deck.erase(deck.begin() + prvi);
			izv_kart++;
			drugi = rand() % (52 - izv_kart);
			dkarta = deck[drugi]; deck.erase(deck.begin() + drugi);
			izv_kart++;
			std::cout << "\nIzvlacimo karte!Vi ste izvukli " << pkarta.tip<< " " << pkarta.lice << " a kuca " << dkarta.tip << " " << dkarta.lice;
			if (pkarta.vrijednost > dkarta.vrijednost) {
				bet *= 2;
				std::cout << "\nDobitak!Dobio si "<< bet<< ".Za duplo ili nista upisite duplo!";
				std::cin >> input;
				while (input == "duplo") {
					bet *= 2;
					prvi = rand() % (52 - izv_kart);
					pkarta = deck[prvi]; deck.erase(deck.begin() + prvi);
					izv_kart++;
					drugi = rand() % (52 - izv_kart);
					dkarta = deck[drugi]; deck.erase(deck.begin() + drugi);
					izv_kart++;
					std::cout << "\nIzvlacimo karte!Vi ste izvukli " << pkarta.tip << " " << pkarta.lice << " a kuca " << dkarta.tip << " " << dkarta.lice;
					if (pkarta.vrijednost > dkarta.vrijednost) { std::cout << "C C C Cooombo!Trenutni dobitak je" << bet << " ,za duplo ili nista upisite duplo!"; cin >> input; }
					else {std:: cout << "Odeeeee!"; bet = 0; break; }
				}
			}
			else { std::cout << "Vise srece sljedeci puta."; bet = 0; }
			std::cout << "\nOsvojili ste " << bet << " cipova.";
			hiskore.push_back(bet); std::sort(hiskore.begin(), (hiskore.begin() + 4), wayToSort); hiskore.pop_back();
			ofstream pisi("highscoredouble.txt");
			for (int i = 0; i < 3; i++) {
				pisi << hiskore[i] << endl;
			}
			pisi.close();
			g_cip += bet;
			system("PAUSE");
			glavni_izbornik();
	}

void izbornik_igara(){
	system("CLS");
	int izbor;
	cout << "\nOdaberite igru:\n1.OneHandJack\n2.Dice\n3.DoubleOrNothing";
	cin >> izbor;
	switch (izbor) {
	case 1:
		jack();
		break;
	case 2:
		dice();
		break;
	case 3:
		double_or();
		break;
	}
}

void prikaz_highscore(){
	vector<int> vjack;
	vector<int> vdice;
	vector<int> vdouble_or;
	vector<int> ukupno;
	int buffer;
	ifstream jack("higghscorejack.txt");
	for (int i = 0; i < 3; i++) {
	      jack >> buffer;
		vjack.push_back(buffer);
		ukupno.push_back(buffer);
	}
	ifstream dice("highscoredice.txt");
	for (int i = 0; i < 3; i++) {
		dice >> buffer;
		vdice.push_back(buffer);
		ukupno.push_back(buffer);
	}
	ifstream double_or("highscoredouble.txt");
	for (int i = 0; i < 3; i++) {
		double_or >> buffer;
		vdouble_or.push_back(buffer);
		ukupno.push_back(buffer);
	}
	jack.close();
	dice.close();
	double_or.close();

	sort(ukupno.begin(), ukupno.end(), wayToSort);
	for (int i = 0; i < (ukupno.size() - 3); i++) {
		ukupno.pop_back();
	}

	cout << "\nOne handed Jack\n";
	for (int i = 0; i < 3; i++) {
		cout << vjack[i] << endl;
	}
	cout << "\nDice\n";
	for (int i = 0; i < 3; i++) {
		cout << vdice[i] << endl;
	}
	cout << "\nDouble or\n";
	for (int i = 0; i < 3; i++) {
		cout << vdouble_or[i] << endl;
	}
	cout << "\nNajveci dobitci\n";
	for (int i = 0; i < 3; i++) {
		cout << ukupno[i] << endl;
	}
	system("PAUSE");
	glavni_izbornik();
}

void glavni_izbornik(){
	system("CLS");
	int izbor;
	cout << "\n1.Uplata novca\n2.Isplata novca\n3.Odabir igre\n4.High score\n5.Izlaz iz programa";
	cin >> izbor;
	switch (izbor) {
	case 1:
		uplata();
		break;
	case 2:
		isplata();
		break;
	case 3:
		izbornik_igara();
		break;
	case 4:
		prikaz_highscore();
		break;
	case 5:
		break;
	}
}



int main()
{
	glavni_izbornik();
}

