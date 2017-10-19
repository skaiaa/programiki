

#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
	int X,start[] = { 0,0,0,0 }, gracze[] = { 0,0,0,0 }, rzut1[] = { 0,0,0,0 }, rzut2[] = { 0,0,0,0 };
	char input[4];
	cout << "Podaj wielkosc planszy" << endl;
	cin>>X;
	while (true) {
			for (int i=0; i < 4; ++i) {                                     //pierwszy rzut
				cout << "Rzuca gracz " << i + 1 << " format (M_rzut)"<<endl;
				fgets(input, 4, stdin); fgets(input, 4, stdin);             //idk,skad pierwszy czyta
				
				if (int(input[0]) == 'P') {									//sprawdzenie wynikow, tu ten problem, ze wraca do 2 fgets
																			//i je czyta juz jako dwa, a nie jeden
					for (int k = 0; k < 4; k++) {
						cout << gracze[k] << " ";
					}
					cout << endl;
					i--;
				}
				else {														
					rzut1[i] = int(input[2])-'0';
					cout << "rzut1 gracza "<<i+1<<" "<<rzut1[i] << endl;
					if (start[i]) {											//sprawdzenie, czy sie rusza		
						gracze[i] += rzut1[i];								//ruch
						cout << gracze[i];
						if (gracze[i] >=X) {								//porownanie z plansza
							cout << "gracz " << i+1 << " wygral, END OF GAME\n";
							system("pause");
							return 0;
						}
					}
				}
			}
		for (int b = 0; b < 4; b++) {									//sprawdzanie warunku startu no. 1
			if (rzut2[b] == 1 && rzut1[b] == 6) {
				start[b] = 1;
				cout << "Gracz " << b+1 << " wystartowal!" << endl;
			}
		}
				for (int j = 0; j < 4; ++j) {
					cout << "Rzuca gracz " << j + 1 << " format (M_rzut)" << endl;
					fgets(input, 4, stdin); fgets(input, 4, stdin);
					if (int(input[0]) == 'P') {
						for (int n = 0; n < 4; n++) {
							cout << gracze[n] << " ";
						}
						cout << endl;
						j--;
					}
					else {
						rzut2[j] = int(input[2])-'0';
						cout << "rzut2 gracza " <<j+1<<" "<< rzut2[j] << endl;
						if (start[j] == 1) {
							gracze[j] += rzut2[j];
							if (gracze[j] >= X) {
								cout << "gracz " << j+1 << " wygral, END OF GAME\n";
								system("pause");
								return 0;
							}
						}
					}

				}	
			for (int a = 0; a < 4; a++) {								//sprawdzenie warunku rzutu no. 2
				if (rzut1[a] == 1 && rzut2[a] == 6) {
					start[a] = 1;
					cout << "Gracz " << a+1 << " wystartowal!" << endl;	
				}
			}	
	}
}