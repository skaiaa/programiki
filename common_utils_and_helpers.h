#define PODS_WYMIAR 8
#define X_LEGENDY 2
#define Y_LEGENDY 2
#define X_PLANSZY 55
#define Y_PLANSZY 2
#define X_KOMUNIKATU 35
#define Y_KOMUNIKATU 15

typedef enum{//wszyyyystkie opcje
    GORA,
    DOL,
    LEWO,
    PRAWO,
    ESC,//esc
    NOWA_GRA,//n
    ZERO,//duh.
    JEDEN,
    LOSOWA_PLANSZA,//o
    PROSTA_PODPOWIEDZ,//p
    ZMIANA_ROZMIARU,//r
    SPR_CZY_KONIEC,//k
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

void czysc_ekran();

void wypisz_legende(int zn, bool strzalki);

void wypisz_legende2();

int stworz_plansze(int n, pole_t ***tab);

void usun_plansze(int n, pole_t **tab);

void generuj_wzor(int n, pole_t **wzor);

void generuj_tab(int n,pole_t **tab,pole_t **wzor);

void generuj_plansze(int n,pole_t **tab,pole_t **wzor);

void wypisz_plansze(int n, pole_t **tab);

void rysuj_ramke(int xp,int yp,int n,int m);

akcje_t obsluga_ascii(int *zn,bool *strzalki);

void wypisz_koncowy_komunikat();

void ustaw_kursor(int n,int cur_pos[]);
