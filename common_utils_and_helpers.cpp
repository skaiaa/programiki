#include "common_utils_and_helpers.h"
#include<stdio.h>
#include"conio2.h"
#include<malloc.h>

/////wypisywanie na ekran, czyszczenie ekranu, ustawianie kursora//////

void czysc_ekran(){
    textbackground(BLACK);
    clrscr();
    textcolor(LIGHTGRAY);
}

void wypisz_legende(int zn, bool strzalki,int cur_pos[]){
    char txt[32];
    int i=0;
        wypisz_tekst(X_LEGENDY, Y_LEGENDY,"esc = wyjscie");
        wypisz_tekst(X_LEGENDY, Y_LEGENDY+(++i),"n = nowa gra");
        wypisz_tekst(X_LEGENDY, Y_LEGENDY+(++i),"0/1 = wypelnienie planszy");
        wypisz_tekst(X_LEGENDY, Y_LEGENDY+(++i),"o = losowa plansza");
        wypisz_tekst(X_LEGENDY, Y_LEGENDY+(++i),"p = prosta podpowiedz");
        wypisz_tekst(X_LEGENDY, Y_LEGENDY+(++i),"r = zmiana rozmiaru");
        wypisz_tekst(X_LEGENDY, Y_LEGENDY+(++i),"0/1 = wypelnienie planszy");
        wypisz_tekst(X_LEGENDY, Y_LEGENDY+(++i),"a = auto detekcja konca gry");
        wypisz_tekst(X_LEGENDY, Y_LEGENDY+(++i),"j = podswietl oczywiste");
        wypisz_tekst(X_LEGENDY, Y_LEGENDY+(++i),"w = wypeln podswietlone");
		if(strzalki)
            sprintf(txt, "kod klawisza: 0x00 0x%02x", zn);
		else sprintf(txt, "kod klawisza: 0x%02x", zn);
		wypisz_tekst(X_LEGENDY, Y_LEGENDY+(++i),txt);
		sprintf(txt,"polozenie kursora: %d %d",cur_pos[0],cur_pos[1]);
		wypisz_tekst(X_LEGENDY, Y_LEGENDY+(++i),txt);

}


void wypisz_tekst(int x, int y, char *str) {
    gotoxy(x, y);
    cputs(str);
    return;
}

void wypisz_komunikat(char *txt){
    rysuj_ramke(X_KOMUNIKATU,Y_KOMUNIKATU,15,3);
    wypisz_tekst(X_KOMUNIKATU, Y_KOMUNIKATU, txt);
    return;
}



void wypisz_plansze(int n, pole_t **tab){
    char c;
    int yp=Y_PLANSZY;
    gotoxy(X_PLANSZY,yp);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            textcolor(tab[i][j].kolor);
            c=tab[i][j].wartosc;
            putch(c);
        }
        yp++;
        gotoxy(X_PLANSZY,yp);
    }
    textcolor(LIGHTGRAY);
}

void rysuj_ramke(int xp,int yp,int n,int m){//brzydka ta funkcja
    //int xp=2,yp=2;
    gotoxy(xp-1,yp-1);
    putch(201);
    for(int i=0;i<n;i++)putch(205);
    //gotoxy(xp+n,yp-1);
    putch(187);
    gotoxy(xp-1,yp+m);
    putch(200);
    for(int j=0;j<n;j++)putch(205);
    putch(188);
}


void ustaw_kursor(int n,int cur_pos[]){
    if(cur_pos[0]>X_PLANSZY+n-1)cur_pos[0]=X_PLANSZY;//tutaj sprawdzam, czy nie wychodze poza plansze
    if(cur_pos[1]>Y_PLANSZY+n-1)cur_pos[1]=Y_PLANSZY;//jak wychodze, to przenosi mnie na poczatek
    if(cur_pos[0]<X_PLANSZY)cur_pos[0]=X_PLANSZY+n-1;
    if(cur_pos[1]<Y_PLANSZY)cur_pos[1]=Y_PLANSZY+n-1;

   gotoxy(cur_pos[0],cur_pos[1]);
}


int licz_znaki_w_wierszu(int n,pole_t **tab,int i,char znak){
    int licznik=0;
    for(int k=0;k<n;k++){
        if( tab[i][k].wartosc==znak )licznik++;
    }
    return licznik;
}

int licz_znaki_w_kolumnie(int n,pole_t **tab,int j,char znak){
    int licznik=0;
    for(int w=0;w<n;w++){
        if( tab[w][j].wartosc==znak )licznik++;
    }
    return licznik;
}

void wyswietl_liczbe_znakow(int n,pole_t **tab){
    char liczba_znakow[2];
    liczba_znakow[1]='\0';
    textcolor(GREEN);
    wypisz_tekst(X_PLANSZY+n+1,Y_PLANSZY-1,"0 1");
    wypisz_tekst(X_PLANSZY-1,Y_PLANSZY+n+1,"0");
    wypisz_tekst(X_PLANSZY-1,Y_PLANSZY+n+2,"1");
    textcolor(LIGHTGRAY);
    for(int i=0;i<n;i++){
            liczba_znakow[0]=licz_znaki_w_wierszu(n,tab,i,'0')+'0';
            wypisz_tekst(X_PLANSZY+n+1,Y_PLANSZY+i,liczba_znakow);
            liczba_znakow[0]=licz_znaki_w_wierszu(n,tab,i,'1')+'0';
            wypisz_tekst(X_PLANSZY+n+3,Y_PLANSZY+i,liczba_znakow);
            liczba_znakow[0]=licz_znaki_w_kolumnie(n,tab,i,'0')+'0';
            wypisz_tekst(X_PLANSZY+i,Y_PLANSZY+n+1,liczba_znakow);
            liczba_znakow[0]=licz_znaki_w_kolumnie(n,tab,i,'1')+'0';
            wypisz_tekst(X_PLANSZY+i,Y_PLANSZY+n+2,liczba_znakow);
    }
}

/////~/////

akcje_t obsluga_ascii(int *zn,bool *strzalki){
    *zn=getch();
    *strzalki=false;
    if(*zn == 0) {
            *strzalki=true;
			*zn = getch();
			if(*zn == 0x48)return GORA;// y--;
			else if(*zn == 0x50)return DOL;// y++;
			else if(*zn == 0x4b)return LEWO;// x--;
			else if(*zn == 0x4d)return PRAWO;// x++;
		} else if(*zn == ' ') ;//attr = (attr + 1) % 16;//zmiana koloru gwiazdki, jak nacisnie spacje
		else if((*zn == 'n') || (*zn == 'N'))return NOWA_GRA;
		else if(*zn=='0')return ZERO;
		else if(*zn=='1')return JEDEN;
		else if(*zn=='o' ||*zn=='O')return LOSOWA_PLANSZA;
		else if(*zn == 'r' || *zn=='R') return ZMIANA_ROZMIARU;
        else if(*zn=='o' || *zn=='O')return LOSOWA_PLANSZA;
        else if(*zn=='p' || *zn=='P')return PROSTA_PODP;
        else if(*zn=='k' || *zn=='K')return PROSTE_SPR;
        else if(*zn=='j' || *zn=='J')return ZAZNACZ_OCZYWISTE;
        else if(*zn=='a' || *zn=='A')return AUTO_CZY_KONIEC;
		else if(*zn==0x1B)return ESC;//back = (back + 1) % 16;// 0x0d-kod enter, zmiania tla gwiazdki

}

