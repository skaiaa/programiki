#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__


#define PODS_WYMIAR 12   //podstawowy rozmiar planszy do gry
#define X_LEGENDY 2     //poczatkowa wspolrzedna x legendy
#define Y_LEGENDY 2     //poczatkowa wspolrzedna y legendy
#define X_PLANSZY 45    //poczatkowa wspolrzedna x planszy
#define Y_PLANSZY 2     //poczatkowa wspolrzedna y planszy
#define X_KOMUNIKATU 15 //poczatkowa wspolrzedna x komunikatu
#define Y_KOMUNIKATU 20 //poczatkowa wspolrzedna y komunikatu
#define PUSTE_POLE '.'    //znak pustego pola
#define ILOSC_WARUNKOW 3


typedef enum{//wszystkie opcje
    GORA,
    DOL,
    LEWO,
    PRAWO,
    ESC,//esc
    NOWA_GRA,//n
    ZERO,//duh.
    JEDEN,
    LOSOWA_PLANSZA,//o
    PROSTA_PODP,//p
    ZMIANA_ROZMIARU,//r
    PROSTE_SPR,//k
    SPR_LINIE,//d
    AUTO_CZY_KONIEC,//a
    ZAZNACZ_OCZYWISTE,//j(podswietl)
    WYPELN_OCZYWISTE,//w
    ZAPISZ,//s
    ZALADUJ,//l
    SPR_I_WYPENIJ,//b
    BLEDNY_KLAWISZ
} akcje_t;

typedef struct{
    char wartosc;
    int kolor;
}pole_t;

/////wypisywanie na ekran, czyszczenie ekranu, ustawianie kursora, czytanie z ekranu/////
void czysc_ekran();

void wypisz_legende(int zn, bool strzalki,int cur_pos[]);

void wypisz_plansze(int n, pole_t **tab);

void rysuj_ramke(int xp,int yp,int n,int m);    //rysuj ramke w okolo prostokata i poczatkowych wspol x,y, szerokosci n i wysokosci m

void wypisz_tekst(int x, int y, char *str);

void wypisz_komunikat(char *txt);               //wypisz_tekst w ramce w X i Y_KOMUNIKATU

void ustaw_kursor(int n,int cur_pos[]);

akcje_t obsluga_ascii(int *zn,bool *strzalki);  //zmienia kody ascii na rodzaj akcji(np.NOWA_GRA)

void wyswietl_liczbe_znakow(int n,pole_t **tab);
/////~/////


#endif // __UTILS_H_INCLUDED__
