#include<stdio.h>
#include"stdlib.h"
#include"conio2.h"
#include<malloc.h>
#include<cstdlib>
#include<ctime>
#include "common_utils_and_helpers.h"
#include "common.h"

bool spr_indeksy(int n,int i,int j){
    if((i>=0) && (i<n) && (j>=0) && (j<n)) return true;
    return false;
}

void obsluga_akcji(int *n, akcje_t akcja, int cur_pos[], pole_t ***tab, pole_t ***wzor){
    char zn=PUSTE_POLE;
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
            zn='0';
           if( ((*tab)[cur_pos[1]-Y_PLANSZY][cur_pos[0]-X_PLANSZY].kolor==LIGHTGRAY)
               && sprawdz_I_warunek(*n,*tab,cur_pos[1]-Y_PLANSZY,cur_pos[0]-X_PLANSZY, zn)
               && sprawdz_II_warunek(*n,*tab,cur_pos[1]-Y_PLANSZY,cur_pos[0]-X_PLANSZY,zn) )
            (*tab)[cur_pos[1]-Y_PLANSZY][cur_pos[0]-X_PLANSZY].wartosc=zn;
            zn=PUSTE_POLE;
            break;
        case JEDEN:
            zn='1';
            if( ((*tab)[cur_pos[1]-Y_PLANSZY][cur_pos[0]-X_PLANSZY].kolor==LIGHTGRAY)
               && sprawdz_I_warunek(*n,*tab,cur_pos[1]-Y_PLANSZY,cur_pos[0]-X_PLANSZY,zn)
               &&  sprawdz_II_warunek(*n,*tab,cur_pos[1]-Y_PLANSZY,cur_pos[0]-X_PLANSZY,zn))
            (*tab)[cur_pos[1]-Y_PLANSZY][cur_pos[0]-X_PLANSZY].wartosc=zn;
            zn=PUSTE_POLE;
            break;
        case NOWA_GRA:
             generuj_plansze(*n,*tab, *wzor);
            break;
        case ZMIANA_ROZMIARU:
            zmien_rozmiar(n,tab,wzor);
            break;
        case ESC:
            wypisz_komunikat("GAME OVER");
            gotoxy(X_KOMUNIKATU+1,Y_KOMUNIKATU+3);
            break;
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
	bool strzalki=false;

#ifndef __cplusplus
	Conio2_Init();
#endif
    srand(time(NULL));

	settitle("Anna Przybycien 172126");
	stworz_plansze(n,&tab);
	stworz_plansze(n,&wzor);
	generuj_plansze(n,tab,wzor);

	do {
        czysc_ekran();
		wypisz_legende(zn,strzalki);
        wypisz_plansze(n,tab);
        rysuj_ramke(X_PLANSZY,Y_PLANSZY,n,n);
        ustaw_kursor(n,cur_pos);
		akcja=obsluga_ascii(&zn,&strzalki);
		obsluga_akcji(&n,akcja,cur_pos,&tab,&wzor);

	} while (akcja != ESC);
    usun_plansze(n,tab);
    usun_plansze(n,wzor);
	return 0;
	}


