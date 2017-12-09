
#include<stdio.h>
#include"stdlib.h"
#include"conio2.h"
#include<malloc.h>
#include<cstdlib>
#include<ctime>
#include "common_utils_and_helpers.h"
#include "game_logic.h"

bool spr_indeksy(int n,int i,int j){
    if((i>=0) && (i<n) && (j>=0) && (j<n)) return true;
    return false;
}


void obsluga_akcji(int *n, akcje_t akcja, int cur_pos[], pole_t ***tab, pole_t ***wzor,int *auto_detekcja){
    char zn=PUSTE_POLE;
    //int podswietlone=0;
    int war_nowa=0, i=cur_pos[1]-Y_PLANSZY, j=cur_pos[0]-X_PLANSZY;
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
            if( (spr_modyfikowalnosc(*tab,i,j)) && (spr_warunki(*n,*tab,i,j,zn)) ){
                (*tab)[i][j].wartosc=zn;
                zn=PUSTE_POLE;
            }
            break;
        case JEDEN:
            zn='1';
            if( (spr_modyfikowalnosc(*tab,i,j)) && (spr_warunki(*n,*tab,i,j,zn)) ){
                (*tab)[i][j].wartosc=zn;
                zn=PUSTE_POLE;
            }
            break;
        case NOWA_GRA:
            war_nowa=1;
             generuj_plansze(war_nowa,*n,*tab, *wzor);
            break;
        case ZMIANA_ROZMIARU:
            zmien_rozmiar(n,tab,wzor);
            break;
        case LOSOWA_PLANSZA:
            war_nowa=0;
            generuj_plansze(war_nowa,*n,*tab,*wzor);
            break;
        case PROSTA_PODP:
            prosta_podpowiedz(*n,*tab,i,j);
            break;
        case PROSTE_SPR:
            proste_sprawdzanie(*n,*tab);
            break;
        case AUTO_CZY_KONIEC:
            if(*auto_detekcja)*auto_detekcja=0;
            else *auto_detekcja=1;
            break;
        case ZAZNACZ_OCZYWISTE:
            //podswietlone=1;
            podswietlanie_jednoznacznych(*n,*tab);
            break;
        case ESC:
            wypisz_komunikat("   GAME OVER");
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
	int zn,war_nowa=1,auto_detekcja=0;
	bool strzalki=false;
	//char debug[2];

#ifndef __cplusplus
	Conio2_Init();
#endif
    srand(time(NULL));
    //debug[1]='\0';
	settitle("Anna Przybycien 172126");
	stworz_plansze(n,&tab);
	stworz_plansze(n,&wzor);
	generuj_plansze(war_nowa,n,tab,wzor);
    czysc_ekran();
    wypisz_legende(zn,strzalki,cur_pos);
    wypisz_plansze(n,tab);
    rysuj_ramke(X_PLANSZY,Y_PLANSZY,n,n);
    wyswietl_liczbe_znakow(n,tab);
	do {
        if(akcja==ZMIANA_ROZMIARU || akcja==PROSTA_PODP || akcja==AUTO_CZY_KONIEC){
            czysc_ekran();
            rysuj_ramke(X_PLANSZY,Y_PLANSZY,n,n);
        }
        if(akcja==ZMIANA_ROZMIARU || akcja==JEDEN || akcja==ZERO || akcja==NOWA_GRA
        || akcja==LOSOWA_PLANSZA || akcja==PROSTA_PODP || akcja==PROSTE_SPR
         || akcja==AUTO_CZY_KONIEC || akcja==ZAZNACZ_OCZYWISTE)wypisz_plansze(n,tab);
        wypisz_legende(zn,strzalki,cur_pos);
        wyswietl_liczbe_znakow(n,tab);
        //debug[0]=auto_detekcja+'0';
        //wypisz_tekst(2,14,debug);
        if(auto_detekcja)auto_detekcja_konca(n,tab);
        ustaw_kursor(n,cur_pos);
		akcja=obsluga_ascii(&zn,&strzalki);
		obsluga_akcji(&n,akcja,cur_pos,&tab,&wzor,&auto_detekcja);


	} while (akcja != ESC);
    usun_plansze(n,tab);
    usun_plansze(n,wzor);
	return 0;
	}

