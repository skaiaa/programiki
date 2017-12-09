#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "common_utils_and_helpers.h"

/////malloc, free, dynamiczna alokacja planszy w pamieci/////

int stworz_plansze(int n, pole_t ***tab);               //malloc

void usun_plansze(int n, pole_t **tab);                 //free

int zmien_rozmiar(int *n, pole_t ***tab, pole_t ***wzor);//usuwa stara plansze i stwarza nowa(free i malloc)
/////~/////

/////wpisywanie wartosci do planszy(tablicy)/////

void generuj_plansze(int war_nowa,int n,pole_t **tab,pole_t **wzor);//zlaczenie generuj_wzor i generuj_tab

void generuj_wzor(int n, pole_t **wzor);                            //na razie nieuzywana

void losowo_wypelnij_plansze(int n, pole_t **tab,int ilosc_losowanych);

int wczytywanie_z_pliku(int n,pole_t **tab);

void generuj_tab(int war_nowa,int n,pole_t **tab);                  //wprowadza wartosci do planszy(tablicy), losowe lub z pliku
/////~/////

/////sprawdzanie warunkow(czy mozliwe jest wpisanie wartosci w miejsce na planszy(tablicy)/////

int spr_modyfikowalnosc(pole_t **tab,int i,int j);                              //sprawdzania koloru pola(LIGHTGRAY<=>modyfikowalne)

int spr_warunki(int n, pole_t **tab, int i, int j, char zn);                    //zlaczenie spr_modyfikowalnosc i spr I,II,III warunków

int spr_I_warunek(int n, pole_t **tab, int i, int j, char zn);

int spr_w_dol(int n, pole_t **tab,int i, int j, char zn);                       //I warunek

int spr_w_gore(int n, pole_t **tab, int i, int j, char zn);                     //I warunek

int spr_w_prawo(int n, pole_t **tab, int i, int j, char zn);                    //I warunek

int spr_w_lewo(int n, pole_t **tab, int i, int j, char zn);                     //I warunek

int spr_II_warunek(int n, pole_t **tab, int i, int j, char zn);

int spr_III_warunek(int n, pole_t **tab, int i, int j, char zn);

int spr_pelny_wiersz(int n, pole_t **tab, int i, int j);                        //III warunek

int spr_pelna_kolumne(int n, pole_t **tab, int i, int j);                       //III warunek

int spr_podobienstwo_wierszy(int n, pole_t **tab, int i,int j, int w, char zn); //III warunek

int spr_podobienstwo_kolumn(int n, pole_t **tab, int i, int j, int k, char zn); //III warunek

int spr_kolumny(int n, pole_t **tab, int i, int j,char zn);                     //III warunek

int spr_wiersze(int n, pole_t **tab, int i, int j, char zn);                    //III warunek


/////~/////

void prosta_podpowiedz(int n, pole_t **tab, int i, int j);

void proste_sprawdzanie(int n,pole_t **tab);

void auto_detekcja_konca(int n,pole_t **tab);

int zliczanie_niemozliwych(int n,pole_t **tab);

void podswietlanie_jednoznacznych(int n, pole_t **tab);

#endif // GAME_LOGIC_H
