#include "game_logic.h"
#include<malloc.h>
#include<stdio.h>
#include "conio2.h"


int stworz_plansze(int n, pole_t ***tab){
    (*tab)=(pole_t**)malloc(n*sizeof(pole_t*));
    if(*tab==NULL) return EOF;
    for(int i= 0;i<n;i++){
        (*tab)[i]=(pole_t *)malloc(n*sizeof(pole_t));
        if((*tab)[i]==NULL) return EOF;
    }
    return 1;
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

void generuj_plansze(int war_nowa,int n,pole_t **tab,pole_t **wzor){//na razie jakakolwiek
    generuj_wzor(n,wzor);
    generuj_tab(war_nowa,n,tab);
}


int zmien_rozmiar(int *n, pole_t ***tab, pole_t ***wzor){
    char zn;
    int nowy_rozmiar=0;
    wypisz_komunikat("Podaj rozmiar:");
    gotoxy(X_KOMUNIKATU,Y_KOMUNIKATU+1);
    do{
        zn=getch();
        putch(zn);
        if((zn>='0') && (zn<='9')){
            if(nowy_rozmiar==0) nowy_rozmiar=zn -'0';
            else {
                    nowy_rozmiar *= 10;
                    nowy_rozmiar += zn-'0';
            }
        }
    }while(zn!=0x0d);
    if((nowy_rozmiar%2==0) && (nowy_rozmiar>2) && (nowy_rozmiar<20)){
        usun_plansze(*n,*tab);
        usun_plansze(*n,*wzor);
        *n=nowy_rozmiar;

        if((stworz_plansze(*n,tab))&&(stworz_plansze(*n,wzor))){
            generuj_plansze(0,*n,*tab,*wzor);
        }
        else {
                wypisz_komunikat("za malo miesca");
                getch();
        }
    }
    else {
            wypisz_komunikat("niepoprawny rozmiar");
            getch();
    }
}


void generuj_tab(int war_nowa,int n, pole_t **tab){
        int a,los_i=1,los_j=2,liczba_wyp_pol=0;
        char zn;

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                tab[i][j].wartosc=PUSTE_POLE;
                tab[i][j].kolor=LIGHTGRAY;
            }
        }
        if(war_nowa){
         if(!wczytywanie_z_pliku(n,tab)){
              losowo_wypelnij_plansze(n,tab,n*n/2);
         }
        }
r        if(!war_nowa){
            losowo_wypelnij_plansze(n,tab,n*n/2);
        }

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

int spr_I_warunek(int n,pole_t **tab,int i,int j,char zn){
    if(spr_w_lewo(n,tab,i,j,zn) && spr_w_prawo(n,tab,i,j,zn)
        && spr_w_gore(n,tab,i,j,zn) && spr_w_dol(n,tab,i,j,zn) )return 1;
}

int spr_II_warunek(int n,pole_t **tab,int i,int j,char zn){//spr czy w jednej lini jest tyle samo zer co jedynek
    int licz1_wiersz=0, licz0_wiersz=0, licz1_kol=0, licz0_kol=0;

    for(int k=0;k<n;k++){

        if(k != j)
        switch(tab[i][k].wartosc) {
            case '0': licz0_wiersz++; break;
            case '1': licz1_wiersz++; break;
            default: break;
        }
        if(k != i)
        switch(tab[k][j].wartosc) {
            case '0': licz0_kol++; break;
            case '1': licz1_kol++; break;
            default: break;
        }
    }
    switch(zn){
        case '0':{
            licz0_kol++;
            licz0_wiersz++;
            break;
        }
        case '1':{
            licz1_kol++;
            licz1_wiersz++;
            break;
        }
    }

    if( (licz0_kol<=n/2) && (licz0_wiersz<=n/2)
     && (licz1_kol<=n/2) && (licz1_wiersz<=n/2) )return 1;
    return 0;

}
int spr_pelny_wiersz(int n,pole_t **tab, int i,int j){
    int licz_puste_wiersz=0;
    for(int k=0;k<n;k++){
        if( (k!=j) && (tab[i][k].wartosc==PUSTE_POLE) ) licz_puste_wiersz++;
    }
    if(licz_puste_wiersz==0)return 1;
    return 0;
}

int spr_pelna_kolumne(int n,pole_t **tab, int i,int j){
    int licz_puste_kol=0;
    for(int w=0;w<n;w++){
        if( (w!=i) && (tab[w][j].wartosc==PUSTE_POLE) ) licz_puste_kol++;
    }
    if(licz_puste_kol==0)return 1;
    return 0;
}
int spr_podobienstwo_kolumn(int n,pole_t **tab,int i, int j,int k,char zn){
    for(int w=0;w<n;w++){
        if( (w==i) && (tab[w][k].wartosc!=zn) )               return 1;
        if( (w!=i) && (tab[w][j].wartosc!=tab[w][k].wartosc) )return 1;
    }
    return 0;
}

int spr_kolumny(int n, pole_t **tab,int i, int j,char zn){
    for(int k=0;k<n;k++){
        if((k!=j) && (spr_pelna_kolumne(n,tab,n,k)))//podanie 'n' jako trzeciego arg to trik, spr_pelna_kolumne zadnej pozycji nie pominie
            return spr_podobienstwo_kolumn(n,tab,i,j,k,zn);
    }
}
int spr_podobienstwo_wierszy(int n,pole_t **tab, int i,int j,int w,char zn){
    for(int k=0;k<n;k++){
        if( (k==j) && (tab[w][k].wartosc!=zn) )               return 1;
        if( (k!=j) && (tab[i][k].wartosc!=tab[w][k].wartosc) )return 1;
    }
    return 0;
}

int spr_wiersze(int n, pole_t **tab, int i,int j, char zn){
    for(int w=0;w<n;w++){
        if((w!=i) && (spr_pelny_wiersz(n,tab,w,n)))//podanie 'n' jako czwartego arg to trik, spr_pelny_wiersz zadnej pozycji nie pominie
            return spr_podobienstwo_wierszy(n,tab,i,j,w,zn);
    }
}


int spr_III_warunek(int n,pole_t **tab,int i,int j,char zn){
    int war1=1,war2=1;
    if(spr_pelny_wiersz(n,tab,i,j))war1=spr_wiersze(n,tab,i,j,zn);
    if(spr_pelna_kolumne(n,tab,i,j))war2=spr_kolumny(n,tab,i,j,zn);
    if(war1 && war2)return 1;
    return 0;
}

int spr_modyfikowalnosc(pole_t **tab,int i,int j){
    if((tab[i][j].kolor==LIGHTGRAY))return 1;
    return 0;
}


int spr_warunki(int n, pole_t **tab, int i,int j, char zn){
    if( (spr_I_warunek(n,tab,i,j,zn))
     && (spr_II_warunek(n,tab,i,j,zn))
     && (spr_III_warunek(n,tab,i,j,zn)) )return 1;
    else return 0;

}


void losowo_wypelnij_plansze(int n, pole_t **tab,int ilosc_losowanych){
    int los_i,los_j,liczba_wyp_pol=0;
    char zn;
    do{
                zn = '0' + rand() % 2;
                los_i=rand()%n;
                los_j=rand()%n;
                if((spr_modyfikowalnosc(tab,los_i,los_j)) && (spr_warunki(n,tab,los_i,los_j,zn)) ){
                    tab[los_i][los_j].wartosc=zn;
                    tab[los_i][los_j].kolor=RED;
                    liczba_wyp_pol++;
                }
            }while(liczba_wyp_pol<ilosc_losowanych);
}

void czemu_nie_jeden(char *warunki_dla_1, int wiersz){
    if(!warunki_dla_1[1])wypisz_tekst(2,++wiersz,"1 lamie I warunek");
    if(!warunki_dla_1[2])wypisz_tekst(2,++wiersz,"1 lamie II warunek");
    if(!warunki_dla_1[3])wypisz_tekst(2,++wiersz,"1 lamie III warunek");
}

void czemu_nie_zero(char *warunki_dla_0, int wiersz){

    if(!warunki_dla_0[1])wypisz_tekst(2,++wiersz,"0 lamie I warunek");
    if(!warunki_dla_0[2])wypisz_tekst(2,++wiersz,"0 lamie II warunek");
    if(!warunki_dla_0[3])wypisz_tekst(2,++wiersz,"0 lamie III warunek");
}


void prosta_podpowiedz(int n, pole_t **tab, int i, int j){
    int wiersz=15;
//    int tylko_jeden_znak_mozliwy=0;
    if(spr_modyfikowalnosc(tab,i,j)){
    char warunki_dla_1[5]={spr_warunki(n,tab,i,j,'1'), spr_I_warunek(n,tab,i,j,'1'),spr_II_warunek(n,tab,i,j,'1'),spr_III_warunek(n,tab,i,j,'1')};
    char warunki_dla_0[5]={spr_warunki(n,tab,i,j,'0'), spr_I_warunek(n,tab,i,j,'0'),spr_II_warunek(n,tab,i,j,'0'),spr_III_warunek(n,tab,i,j,'0')};
        if(warunki_dla_0[0] && warunki_dla_1[0]){
            wypisz_tekst(2,wiersz,"mozliwe: 1,0");
            getch();
        }
        else if(!warunki_dla_0[0] && !warunki_dla_1[0]){
            wypisz_tekst(2,wiersz,"nic nie jest mozliwe");
            czemu_nie_jeden(warunki_dla_1,wiersz);
            czemu_nie_zero(warunki_dla_0,wiersz+3);
            getch();

        }
        else if(warunki_dla_0[0]){
     //       tylko_jeden_znak_mozliwy=1;
            wypisz_tekst(2,wiersz,"mozliwe: 0");
            czemu_nie_jeden(warunki_dla_1,wiersz);
            getch();
        }
        else if(warunki_dla_1[0]){
       //     tylko_jeden_znak_mozliwy=2;
            wypisz_tekst(2,wiersz,"mozliwe: 1");
            czemu_nie_zero(warunki_dla_0,wiersz);
            getch();
        }
    }
    else{
        wypisz_tekst(2,wiersz,"niemodyfikowalne");
        getch();
    }
   // return tylko_jeden_znak_mozliwy;

}

void podswietlanie_jednoznacznych(int n, pole_t **tab){
    char zn;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if( (spr_modyfikowalnosc(tab,i,j))
            &&( ( (spr_warunki(n,tab,i,j,'1')) && (!spr_warunki(n,tab,i,j,'0')) ) || ( (!spr_warunki(n,tab,i,j,'1')) && (spr_warunki(n,tab,i,j,'0')) ) ))tab[i][j].kolor=GREEN;
        }
    }
    wypisz_plansze(n,tab);
    zn=getch();
    if(zn=='w' || zn=='W'){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(spr_warunki(n,tab,i,j,'0'))tab[i][j].wartosc='0';
                if(spr_warunki(n,tab,i,j,'1'))tab[i][j].wartosc='1';
        }
    }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if( tab[i][j].kolor==GREEN ) tab[i][j].kolor=LIGHTGRAY;
        }
    }
}
int zliczanie_niemozliwych(int n,pole_t **tab){
    int licznik_niemozliwych=0,licznik_pustych=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(tab[i][j].wartosc==PUSTE_POLE)licznik_pustych++;
            if( !spr_warunki(n,tab,i,j,'0') && !spr_warunki(n,tab,i,j,'1') && (tab[i][j].wartosc==PUSTE_POLE) ){
                tab[i][j].wartosc='x';
                licznik_niemozliwych++;
            }
        }
    }
     return licznik_pustych-licznik_niemozliwych;
}
void proste_sprawdzanie(int n,pole_t **tab){
    zliczanie_niemozliwych(n,tab);
    wypisz_plansze(n,tab);
    getch();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if( tab[i][j].wartosc=='x' ) tab[i][j].wartosc=PUSTE_POLE;
        }
    }
}


int wczytywanie_z_pliku(int n,pole_t **tab){
    FILE *plik=NULL;
    char nazwa[30];
    sprintf(nazwa,"plansze%dx%d.txt",n,n);
    plik=fopen(nazwa, "r");

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

void auto_detekcja_konca(int n,pole_t **tab){
    wypisz_tekst(X_LEGENDY,Y_LEGENDY+10,"auto detekcja konca wlaczona");
    if(!zliczanie_niemozliwych(n,tab)){
        wypisz_komunikat("brak ruchow");
        getch();
    }
}

