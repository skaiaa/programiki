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


void wypisz_komunikat(char *txt){
    rysuj_ramke(X_KOMUNIKATU,Y_KOMUNIKATU,15,3);
     gotoxy(X_KOMUNIKATU,Y_KOMUNIKATU);
     cputs(txt);
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
    putch(187);
    gotoxy(xp-1,yp+m);
    putch(200);
    for(int j=0;j<n;j++)putch(205);
    putch(188);
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

void generuj_wzor(int n,pole_t **wzor){//prowizorycznie,docelowo generuje rozwiazane puzzle binarne
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
        int a,los_i=1,los_j=2,liczba_wyp_pol=0;
        char zn;

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                tab[i][j].wartosc=PUSTE_POLE;
                tab[i][j].kolor=LIGHTGRAY;
            }
        }

         if(!wczytywanie_z_pliku(n,tab)){
            do{
                a=rand()%2;
                if(a==0)zn='0';
                if(a==1)zn='1';
                los_i=rand()%n;
                los_j=rand()%n;
                if((sprawdz_I_warunek(n,tab,los_i,los_j,zn))
                && (sprawdz_II_warunek(n,tab,los_i,los_j,zn))
                && (sprawdz_III_warunek(n,tab,los_i,los_j,zn))){
                    tab[los_i][los_j].wartosc=zn;
                    tab[los_i][los_j].kolor=RED;
                    liczba_wyp_pol++;
                }
            }while(liczba_wyp_pol<n*2);
         }

}



void generuj_plansze(int n,pole_t **tab,pole_t **wzor){//na razie jakakolwiek
    generuj_wzor(n,wzor);
    generuj_tab(n,tab,wzor);
}


void zmien_rozmiar(int *n, pole_t ***tab, pole_t ***wzor){
    usun_plansze(*n,*tab);
    usun_plansze(*n,*wzor);
    rysuj_ramke(X_KOMUNIKATU,Y_KOMUNIKATU,13,3);
    wypisz_komunikat("Podaj rozmiar:");
    gotoxy(X_KOMUNIKATU,Y_KOMUNIKATU+1);
    *n=getch() - '0';
    //if(*n<12)(*n)+=2;
    //else (*n)=6;
    stworz_plansze(*n,tab);
    stworz_plansze(*n,wzor);
    generuj_plansze(*n,*tab, *wzor);
}

int wczytywanie_z_pliku(int n,pole_t **tab){
    FILE *plik=NULL;
    if(n==12)plik=fopen("plansze12x12.txt", "r");
    if(plik==NULL)return 0;
    char znak;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
           znak=fgetc(plik);
           if(znak==EOF)return 1;
           tab[i][j].wartosc=znak;
           if(tab[i][j].wartosc==PUSTE_POLE)tab[i][j].kolor=LIGHTGRAY;
           else tab[i][j].kolor=RED;
        }
        znak=fgetc(plik);//tylko po to, zeby omijac entery
    }
    fclose(plik);
    return 1;
}


int spr_w_lewo(int n, pole_t **tab,int i, int j,char zn){
    if(j==0)return 1;
    if((j>0) && (j<n-1) && (tab[i][j-1].wartosc==tab[i][j+1].wartosc) && (tab[i][j+1].wartosc==zn))return 0;//dod spr jednej po i jednej za
    if((j>1) && (tab[i][j-2].wartosc==tab[i][j-1].wartosc) && (tab[i][j-1].wartosc==zn))return 0;//dwa w lewo
    return 1;

}

int spr_w_prawo(int n, pole_t **tab,int i, int j,char zn){
    if(j==n-1)return 1;
    if((j<n-2) && (tab[i][j+2].wartosc==tab[i][j+1].wartosc) && (tab[i][j+1].wartosc==zn))return 0;
    return 1;
}

int spr_w_gore(int n, pole_t **tab,int i,int j,char zn){
    if(i==0)return 1;
    if((i>0) && (i<n-1) && (tab[i-1][j].wartosc==tab[i+1][j].wartosc) && (tab[i+1][j].wartosc==zn) )return 0;//dod spr jednej pod i jednej nad
    if((i>1) && (tab[i-2][j].wartosc==tab[i-1][j].wartosc) && (tab[i-1][j].wartosc==zn))return 0;
    return 1;
}

int spr_w_dol(int n, pole_t **tab,int i,int j,char zn){
    if(i==n-1)return 1;
    if((i<n-2) && (tab[i+2][j].wartosc==tab[i+1][j].wartosc) && (tab[i+1][j].wartosc==zn))return 0;
    return 1;
}

int sprawdz_I_warunek(int n,pole_t **tab,int i,int j,char zn){
    if(spr_w_lewo(n,tab,i,j,zn) && spr_w_prawo(n,tab,i,j,zn)
        && spr_w_gore(n,tab,i,j,zn) && spr_w_dol(n,tab,i,j,zn) )return 1;
}

int sprawdz_II_warunek(int n,pole_t **tab,int i,int j,char zn){
    int licz1_wiersz=0, licz0_wiersz=0, licz1_kol=0, licz0_kol=0;
    for(int k=0;k<n;k++){
        if(tab[i][k].wartosc=='1')licz1_wiersz++;
        if(tab[i][k].wartosc=='0')licz0_wiersz++;
        if(tab[k][j].wartosc=='1')licz1_kol++;
        if(tab[k][j].wartosc=='0')licz0_kol++;
    }
    if(zn='1'){
        licz1_kol++;
        licz1_wiersz++;
    }
    if(zn='0'){
        licz0_kol++;
        licz0_wiersz++;
    }
    if( (licz0_kol<=n/2) && (licz0_wiersz<=n/2)
    && (licz1_kol<=n/2) && (licz1_wiersz<=n/2) )return 1;
    return 0;

}
int spr_pelny_wiersz(int n,pole_t **tab, int i){
    int licz_puste_wiersz=0;
    for(int k=0;k<n;k++){
        if(tab[i][k].wartosc==PUSTE_POLE)licz_puste_wiersz++;
    }
    if(licz_puste_wiersz==0)return 1;
    return 0;
}

int spr_pelna_kolumne(int n,pole_t **tab, int j){
    int licz_puste_kol=0;
    for(int k=0;k<n;k++){
        if(tab[k][j].wartosc==PUSTE_POLE)licz_puste_kol++;
    }
    if(licz_puste_kol==0)return 1;
    return 0;
}
int sprawdzaj_podobienstwo_kolumn(int n,pole_t **tab, int j,int k){
    for(int l=0;l<n;l++){
        if(tab[l][j].wartosc!=tab[l][j].wartosc)return 0;
    }
    return 1;
}

int sprawdzaj_kolumny(int n, pole_t **tab, int j){
    for(int k=0;k<n;k++){
        if((k!=j) && (spr_pelny_wiersz(n,tab,k)))
            return sprawdzaj_podobienstwo_kolumn(n,tab,j,k);//sprawdzaj podobienstwo
    }
}
int sprawdzaj_podobienstwo_wierszy(int n,pole_t **tab, int i,int k){
    for(int l=0;l<n;l++){
        if(tab[i][l].wartosc!=tab[k][l].wartosc)return 0;
    }
    return 1;
}

int sprawdzaj_wiersze(int n, pole_t **tab, int i){
    for(int k=0;k<n;k++){
        if((k!=i) && (spr_pelny_wiersz(n,tab,k)))
            return sprawdzaj_podobienstwo_wierszy(n,tab,i,k);//sprawdzaj podobienstwo
    }
}


int sprawdz_III_warunek(int n,pole_t **tab,int i,int j,char zn){
    int war1,war2;
    char pomocniczy=tab[i][j].wartosc;
    tab[i][j].wartosc=zn;//!!! tymaczasowo przypisuje
    if(spr_pelny_wiersz(n,tab,i))war1=sprawdzaj_wiersze(n,tab,i);
    if(spr_pelna_kolumne(n,tab,j))war2=sprawdzaj_kolumny(n,tab,j);
    tab[i][j].wartosc=pomocniczy;
    if(war1 && war2)return 1;
    return 0;
}

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
		else if(*zn==0x1B)return ESC;//back = (back + 1) % 16;// 0x0d-kod enter, zmiania tla gwiazdki
}

void ustaw_kursor(int n,int cur_pos[]){
    if(cur_pos[0]>X_PLANSZY+n-1)cur_pos[0]=X_PLANSZY;//tutaj sprawdzam, czy nie wychodze poza plansze
    if(cur_pos[1]>Y_PLANSZY+n-1)cur_pos[1]=Y_PLANSZY;//jak wychodze, to przenosi mnie na poczatek
    if(cur_pos[0]<X_PLANSZY)cur_pos[0]=X_PLANSZY+n-1;
    if(cur_pos[1]<Y_PLANSZY)cur_pos[1]=Y_PLANSZY+n-1;

   gotoxy(cur_pos[0],cur_pos[1]);
}
