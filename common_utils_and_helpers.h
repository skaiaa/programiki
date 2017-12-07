#define PODS_WYMIAR 12   //podstawowy rozmiar planszy do gry
#define X_LEGENDY 2     //poczatkowa wspolrzedna x legendy
#define Y_LEGENDY 2     //poczatkowa wspolrzedna y legendy
#define X_PLANSZY 55    //poczatkowa wspolrzedna x planszy
#define Y_PLANSZY 2     //poczatkowa wspolrzedna y planszy
#define X_KOMUNIKATU 15 //poczatkowa wspolrzedna x komunikatu
#define Y_KOMUNIKATU 18 //poczatkowa wspolrzedna y komunikatu
#define PUSTE_POLE '.'    //znak pustego pola


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

void wypisz_plansze(int n, pole_t **tab);

void rysuj_ramke(int xp,int yp,int n,int m);

void wypisz_komunikat(char *txt);

int stworz_plansze(int n, pole_t ***tab);

void usun_plansze(int n, pole_t **tab);

void generuj_wzor(int n, pole_t **wzor);

void generuj_tab(int n,pole_t **tab,pole_t **wzor);

void generuj_plansze(int n,pole_t **tab,pole_t **wzor);

akcje_t obsluga_ascii(int *zn,bool *strzalki);


void ustaw_kursor(int n,int cur_pos[]);

int sprawdz_I_warunek(int n,pole_t **tab,int i,int j,char zn);

int sprawdz_II_warunek(int n,pole_t **tab,int i,int j,char zn);

int spr_w_dol(int n, pole_t **tab,int i,int j,char zn);

int spr_w_gore(int n, pole_t **tab,int i,int j,char zn);

int spr_w_prawo(int n, pole_t **tab,int i, int j,char zn);

int spr_w_lewo(int n, pole_t **tab,int i, int j,char zn);

void zmien_rozmiar(int *n, pole_t ***tab, pole_t ***wzor);

int wczytywanie_z_pliku(int n,pole_t **tab);
