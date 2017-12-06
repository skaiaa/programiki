#include "common_utils_and_helpers.h"
#include<stdio.h>
#include"conio2.h"
#include<malloc.h>

void czysc_ekran(){
    textbackground(BLACK);
    clrscr();
    textcolor(LIGHTGRAY);
}

void wypisz_legende(int zn, bool strzalki){
    char txt[32];
    int i=0;
        gotoxy(X_LEGENDY, Y_LEGENDY);
        cputs("Anna Przybycien, 172126, esc,n,r,0,1");
        gotoxy(X_LEGENDY,Y_LEGENDY+(++i));
		cputs("esc = wyjscie");
        gotoxy(X_LEGENDY, Y_LEGENDY+(++i));
		cputs("n = nowa gra");
        gotoxy(X_LEGENDY, Y_LEGENDY+(++i));
		cputs("0/1 = wypelnienie planszy");
        gotoxy(X_LEGENDY, Y_LEGENDY+(++i));
		cputs("o = losowa plansza");
        gotoxy(X_LEGENDY, Y_LEGENDY+(++i));
		cputs("p = prosta podpowiedz");
        gotoxy(X_LEGENDY, Y_LEGENDY+(++i));
		cputs("r = zmiana rozmiaru");
        gotoxy(X_LEGENDY, Y_LEGENDY+(++i));
		cputs("o = losowa plansza");
        gotoxy(X_LEGENDY, Y_LEGENDY+(++i));
		if(strzalki)
            sprintf(txt, "kod klawisza: 0x00 0x%02x", zn);
		else sprintf(txt, "kod klawisza: 0x%02x", zn);
		cputs(txt);

}

void wypisz_legende2(){
        char legenda[]="esc = wyjscie strzalki = poruszanie spacja = zmiana koloru enter = zmiana koloru tla";
        puttext(X_LEGENDY,Y_LEGENDY,X_LEGENDY+10,Y_LEGENDY+5,legenda);

}

int stworz_plansze(int n, pole_t ***tab){
    (*tab)=(pole_t**)malloc(n*sizeof(pole_t*));
    if(*tab==NULL) return EOF;
    for(int i= 0;i<n;i++){
        (*tab)[i]=(pole_t *)malloc(n*sizeof(pole_t));
        if((*tab)[i]==NULL) return EOF;
    }
    return 0;
}

void usun_plansze(int n, pole_t **tab){
    for(int i=0;i<n;i++){
        free(tab[i]);
    }
    free(tab);
}

void ustaw_kursor(int n,int cur_pos[]){
    if(cur_pos[0]>X_PLANSZY+n-1)cur_pos[0]=X_PLANSZY;//tutaj sprawdzam, czy nie wychodze poza plansze
    if(cur_pos[1]>Y_PLANSZY+n-1)cur_pos[1]=Y_PLANSZY;//jak wychodze, to przenosi mnie na poczatek
    if(cur_pos[0]<X_PLANSZY)cur_pos[0]=X_PLANSZY+n-1;
    if(cur_pos[1]<Y_PLANSZY)cur_pos[1]=Y_PLANSZY+n-1;

   gotoxy(cur_pos[0],cur_pos[1]);
}

void wypisz_koncowy_komunikat(){
    rysuj_ramke(X_KOMUNIKATU,Y_KOMUNIKATU,13,3);
    gotoxy(X_KOMUNIKATU,Y_KOMUNIKATU);
    cputs("  GAME OVER");
    gotoxy(X_KOMUNIKATU+1,Y_KOMUNIKATU+3);
}


void generuj_wzor(int n,pole_t **wzor){//prowizorycznie
        int a;
        for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            a=rand()%2;
            if(a==0)wzor[i][j].wartosc='0';
            if(a==1)wzor[i][j].wartosc='1';

        }
    }
}

void generuj_tab(int n, pole_t **tab,pole_t **wzor){
        int a;
        int poziom_trudnosci=3;
        for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            a=rand()%poziom_trudnosci;
            if(a==2)tab[i][j].wartosc='.';
            else tab[i][j].wartosc=wzor[i][j].wartosc;
        }
    }
}



void generuj_plansze(int n,pole_t **tab,pole_t **wzor){//na razie jakakolwiek
    generuj_wzor(n,wzor);
    generuj_tab(n,tab,wzor);
}

void wypisz_plansze(int n, pole_t **tab){
    char c;
    int yp=Y_PLANSZY;
    gotoxy(X_PLANSZY,yp);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            //textcolor(tab[i][j].kolor);
            c=tab[i][j].wartosc;
            putch(c);
        }
        yp++;
        gotoxy(X_PLANSZY,yp);
    }
}

void rysuj_ramke(int xp,int yp,int n,int m){//brzydka ta funkcja
    //int xp=2,yp=2;
    gotoxy(xp-1,yp-1);
    putch(201);
    for(int i=0;i<n;i++)putch(205);
    putch(187);
    gotoxy(xp-1,yp+m);
    putch(200);
    for(int j=0;j<n;j++)putch(205);
    putch(188);

}

akcje_t obsluga_ascii(int *zn,bool *strzalki){
    *zn=getch();
    *strzalki=0;
    if(*zn == 0) {
            *strzalki=1;
			*zn = getch();
			if(*zn == 0x48)return GORA;// y--;
			else if(*zn == 0x50)return DOL;// y++;
			else if(*zn == 0x4b)return LEWO;// x--;
			else if(*zn == 0x4d)return PRAWO;// x++;
		} else if(*zn == ' ') ;//attr = (attr + 1) % 16;//zmiana koloru gwiazdki, jak nacisnie spacje
		else if((*zn == 0x4e) || (*zn == 0x6e))return NOWA_GRA;
		else if(*zn==0x30)return ZERO;
		else if(*zn==0x31)return JEDEN;
		else if(*zn==0x4f ||*zn==0x6f)return LOSOWA_PLANSZA;
		else if(*zn == 0x72 || *zn==0x52) return ZMIANA_ROZMIARU;
		else if(*zn==0x1B)return ESC;//back = (back + 1) % 16;// 0x0d-kod enter, zmiania tla gwiazdki
}
