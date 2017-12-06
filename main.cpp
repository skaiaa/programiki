#include<stdio.h>
#include"stdlib.h"
#include"conio2.h"
#include<malloc.h>
#include "common_utils_and_helpers.h"

void zmien_rozmiar(int *n, pole_t ***tab, pole_t ***wzor){
    usun_plansze(*n,*tab);
    usun_plansze(*n,*wzor);
    if(*n<14)(*n)+=2;
    else (*n)=6;
    stworz_plansze(*n,tab);
    stworz_plansze(*n,wzor);
    generuj_plansze(*n,*tab, *wzor);
}
void obsluga_akcji(int *n, akcje_t akcja, int cur_pos[], pole_t ***tab, pole_t ***wzor){
    switch(akcja){
        case GORA:
            cur_pos[0]=wherex();
            cur_pos[1]=wherey()-1;
            break;
        case DOL:
            cur_pos[0]=wherex();
            cur_pos[1]=wherey()+1;
            break;
        case LEWO:
            cur_pos[0]=wherex()-1;
            cur_pos[1]=wherey();
            break;
        case PRAWO:
            cur_pos[0]=wherex()+1;
            cur_pos[1]=wherey();
            break;
        case ZERO:
           (*tab)[cur_pos[1]-Y_PLANSZY][cur_pos[0]-X_PLANSZY].wartosc='0';
            break;
        case JEDEN:
            (*tab)[cur_pos[1]-Y_PLANSZY][cur_pos[0]-X_PLANSZY].wartosc='1';
            break;
        case NOWA_GRA:
             generuj_plansze(*n,*tab, *wzor);
            break;
        case ZMIANA_ROZMIARU:
            zmien_rozmiar(n,tab,wzor);
            break;
        case ESC:
            wypisz_koncowy_komunikat();
        default:
            break;
    }
}

int main() {
	int n=PODS_WYMIAR;
	pole_t **tab,**wzor;
	akcje_t akcja;
	int cur_pos[]={X_PLANSZY,Y_PLANSZY};
	int zn;
	bool strzalki=0;

#ifndef __cplusplus
	Conio2_Init();
#endif

	settitle("Anna Przybycien 172126");
	stworz_plansze(n,&tab);
	stworz_plansze(n,&wzor);
	generuj_plansze(n,tab,wzor);

	do {
        czysc_ekran();
		wypisz_legende(zn,strzalki);
        rysuj_ramke(X_PLANSZY,Y_PLANSZY,n,n);
        wypisz_plansze(n,tab);
        ustaw_kursor(n,cur_pos);
		akcja=obsluga_ascii(&zn,&strzalki);
		obsluga_akcji(&n,akcja,cur_pos,&tab,&wzor);

	} while (akcja != ESC);
    usun_plansze(n,tab);
    usun_plansze(n,wzor);
	return 0;
	}


