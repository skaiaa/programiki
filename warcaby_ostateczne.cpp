#include <iostream>
#define WYMIAR_PLANSZY 8
#define WYMIAR_OBRAZKA 32
using namespace std;

void pola(char plansza[][WYMIAR_OBRAZKA]){
    for(int i=0;i<WYMIAR_OBRAZKA;i++){
        for(int j=0;j<WYMIAR_OBRAZKA;j++){
            if( ( (i%8==4||i%8==7) && (j%8<4) ) || ( (i%8==0||i%8==3) && (j%8>3&&j%8<8) )
            || ( (j%8==4||j%8==7) && (i%8<4) ) || ( (j%8==0||j%8==3) && (i%8>3&&i%8<8) ) ){
                plansza[i][j]='#';
            }
            else {
                plansza[i][j]=' ';
            }

        }
    }

}

void obrazek_pocz(char plansza[][WYMIAR_OBRAZKA]){
    for(int i=0;i<WYMIAR_OBRAZKA;i++){
        for(int j=0;j<WYMIAR_OBRAZKA;j++){
            if( ((i%8==5||i%8==6)&&j%8<3&&j%8>0&&(i>20||i<7))
            || ((i%8<3&&i%8>0)&&(j%8==5||j%8==6)&&(i>20||i<11) ) ){
             if(i<11)plansza[i][j]='?';
             if(i>20)plansza[i][j]='!'; 
        }
    }
}
}
//dziala tylko dla 8 i 32 :/
void alternatywna_zmiana_planszy(int ipocz,int jpocz,int ikonc,int jkonc,char plansza[][WYMIAR_OBRAZKA], char pozycje[][WYMIAR_PLANSZY]){
    char pomocniczy[2][2];//te pozycje sa zeby pozniej zmieniac pionki ja sa damki
        for(int i=1;i<=2;i++){
            for(int j=1;j<=2;j++){
                pomocniczy[i-1][j-1]=plansza[i+4*ipocz][j+4*jpocz];
            }
        }

        for(int i=1;i<=2;i++){
            for(int j=1;j<=2;j++){
                plansza[i+4*ipocz][j+4*jpocz]=plansza[i+4*ikonc][j+4*jkonc];
            }
        }

        for(int i=1;i<=2;i++){
            for(int j=1;j<=2;j++){
                plansza[i+4*ikonc][j+4*jkonc]=pomocniczy[i-1][j-1];
            }
        }

}
void zbicie(int ipocz,int jpocz,int ikonc,int jkonc,char plansza[][WYMIAR_OBRAZKA]){
    for(int i=1;i<=2;i++){
        for(int j=1;j<=2;j++){
            plansza[2*(ipocz+ikonc)+i][2*(jpocz+jkonc)+j]=' ';
        }
    }
}
void pozycje_pocz(char pozycje[][WYMIAR_PLANSZY]) {
    for (int i = 0; i < WYMIAR_PLANSZY; i++) {
        for (int j = 0; j < WYMIAR_PLANSZY; j++) {
            if ((i + j) % 2 != 0) pozycje[i][j] = '#';
            else pozycje[i][j] = ' ';
        }
    }
}

void ustawienie_pocz(char pozycje[][WYMIAR_PLANSZY]) {
    for (int i = 0; i < WYMIAR_PLANSZY; i++) {
        for (int j = 0; j < WYMIAR_PLANSZY; j++) {
            if ((i + j) % 2 != 0&&i<3) pozycje[i][j] = 'o';//bialy pion
            if ((i + j) % 2 != 0 && i>WYMIAR_PLANSZY-4) pozycje[i][j] = 'i';//czarny pion

        }
    }
}

void rysuj_plansze(char plansza[][32]){
        for(int i=0;i<32;i++){
        for(int j=0;j<32;j++){
            cout<<plansza[i][j];
        }
        cout<<endl;
    }
}

//do sprawdzenia
void rysuj_pozycje(char pozycje[][WYMIAR_PLANSZY]) {
    for (int i = 0; i < WYMIAR_PLANSZY; i++) {
        for (int j = 0; j < WYMIAR_PLANSZY; j++) {
            cout<<pozycje[i][j];
        }
        cout << endl;
    }
}

void wypisywanie_startu(int i){
    cout << "podaj skad(0-7)(0-7) i dokad(0-7)(0-7) chcesz ruszyc" << endl;
    if (i % 2 == 0) cout << "runda bialego(o)" << endl;
    else cout << "runda czarnego(i)" << endl;

}

int zamiana_na_damki(int ikonc, int i){
    if(i%2==0&&ikonc==WYMIAR_PLANSZY-1) return 0;//zamiana bialego pionu na damke
    if(i%2!=0&&ikonc==0) return 1;//zamiana czarnego pionu na damke
    else return -1;
}

void ruch(int ipocz, int jpocz, int ikonc, int jkonc,char pozycje[][WYMIAR_PLANSZY],int zamiana) {
    char pomocny;
    pomocny = pozycje[ipocz][jpocz];
    pozycje[ipocz][jpocz] = pozycje[ikonc][jkonc];
    pozycje[ikonc][jkonc] = pomocny;
    if(zamiana==0)pozycje[ikonc][jkonc]='A';//biala damka
    if(zamiana==1)pozycje[ikonc][jkonc]='V';//czarna damka

}

void bicie(int ipocz,int jpocz, int ikonc, int jkonc, char pozycje[][WYMIAR_PLANSZY]){
    pozycje[(ipocz+ikonc)/2][(jpocz+jkonc)/2]='#';
}

int sprawdzenie_poprawnosci_danych(int ipocz, int jpocz, int ikonc, int jkonc,int i, char pozycje[][WYMIAR_PLANSZY]){
    if (ipocz < 0 || ipocz>WYMIAR_PLANSZY-1 || jpocz < 0 || jpocz>WYMIAR_PLANSZY-1
     || ikonc < 0 || ikonc>WYMIAR_PLANSZY-1 || jkonc < 0 || jkonc>WYMIAR_PLANSZY-1 )    return -1;//-1 zle dane
    else if(i%2==0&&pozycje[ipocz][jpocz]!='o'&& pozycje[ipocz][jpocz]!='A'      //bialy pion chce ruszyc z miejsca w ktorym nie jest
    || i%2!=0&&pozycje[ipocz][jpocz]!='i'&& pozycje[ipocz][jpocz]!='V') return -9;//czarny pion chce ruszyc z miejsca w ktorym nie jest
                                              
    else return 0;
}

int sprawdzenie_pola(int ikonc, int jkonc,char pozycje[][WYMIAR_PLANSZY]) {
    if (pozycje[ikonc][jkonc] == '#')return 0;
    if (pozycje[ikonc][jkonc] == ' ')return -8;
    else return -7;
}

int sprawdzenie_ruchu(int ipocz, int jpocz, int ikonc, int jkonc,int i,char pozycje[][WYMIAR_PLANSZY]) {
    if(pozycje[ipocz][jpocz]=='o' || pozycje[ipocz][jpocz]=='i'){
        if (jpocz != jkonc - 1 && jpocz != jkonc + 1)return -2;//zly ruch, nie po przekatnej
        else {
            if (i % 2 == 0 && ipocz != ikonc - 1)return -3;//zle dane dla ruchu bialym pionkiem
            else if (i % 2 != 0 && ipocz != ikonc + 1)return -4;//zle dane dla ruchu czarnym pionkiem
            else return 0;//mozna sie ruszac
        }
    }
    if(pozycje[ipocz][jpocz]=='A'||pozycje[ipocz][jpocz]=='V'){//ruch dla damek

    }
}

int sprawdzenie_bicia(int ipocz,int jpocz,int ikonc,int jkonc,int i,char pozycje[][WYMIAR_PLANSZY]){
    if(pozycje[ipocz][jpocz]=='o'||pozycje[ipocz][jpocz]=='i'){
        if(ipocz-ikonc!=-2&&ipocz-ikonc!=2&&jpocz-jkonc!=-2&&jpocz-jkonc!=2)return -2;//zle bicie
        else if(i%2==0&&pozycje[(ipocz+ikonc)/2][(jpocz+jkonc)/2]!='i') return -5;//bialy nie moze zbijac nie-czarnego piona
        else if(i%2!=0&&pozycje[(ipocz+ikonc)/2][(jpocz+jkonc)/2]!='o') return -6;//czarny nie moze zbijac nie-bialego piona
        else return 0;//mozna bic
    }
    if(pozycje[ipocz][jpocz]=='A'||pozycje[ipocz][jpocz]=='V'){//bicie dla damek

    }
}

void wypisywanie_bledow(int s){
    if(s == -1) cout << "zle dane, ruch niemozliwy, podaj inne"<<endl;
    if (s == -2) cout << "zle dane, poruszamy sie po skosie" << endl;
    if (s == -3) cout << "zle dane, biale sie tak nie ruszaja" << endl;
    if (s == -4) cout << "zle dane, czarne tak sie nie ruszaja" << endl;
    if (s == -5) cout << "nie mozna tak bic bialymi" << endl;
    if (s == -6) cout << "nie mozna tak bic czarnymi" << endl;
    if (s == -7) cout << "zajete pole" << endl;
    if (s == -8) cout<<"poruszamy sie po czarnych polach"<<endl;
    if (s == -9) cout<<"to nie jest twoj pion, nie masz stad ruchu"<<endl;
}

int sprawdzenie_warunku_konca_gry(char pozycje[][WYMIAR_PLANSZY]){
    int licz_bialych=0,licz_czarnych=0;
    for(int i=0;i<WYMIAR_PLANSZY;i++){
        for(int j=0;j<WYMIAR_PLANSZY;j++){
            if(pozycje[i][j]=='o')licz_bialych++;//jeszcze zliczac damki, ale to jak sie beda ruszac
            if(pozycje[i][j]=='i')licz_czarnych++; // bo na razie nie da sie ich zbic
        }
    }
    if(licz_bialych==0||licz_czarnych==0)return 0;
    else return 1;
}

int main() {
    int ipocz, jpocz, ikonc, jkonc,s,s2,jaki_ruch,s3,zamiana,i,s4;
    char pozycje[WYMIAR_PLANSZY][WYMIAR_PLANSZY];
    char plansza[WYMIAR_OBRAZKA][WYMIAR_OBRAZKA];
    pozycje_pocz(pozycje);
    ustawienie_pocz(pozycje);
    pola(plansza);
    obrazek_pocz(plansza);
    //pozycje[0][0] = 'A';
    rysuj_plansze(plansza);
    //rysuj_pozycje(pozycje);
    i=0;
    do{//na razie, normalnie bedzie w while
        wypisywanie_startu(i);
        do {
            cin >> ipocz >> jpocz >> ikonc >> jkonc;
            s3=sprawdzenie_poprawnosci_danych(ipocz,jpocz,ikonc,jkonc,i,pozycje);//zwraca-1.-9. 0
            wypisywanie_bledow(s3);
            if(s3==0){
                s2 = sprawdzenie_pola(ikonc, jkonc, pozycje);//zwraca-7,-8,0
                //cout<<s2<<endl;
                wypisywanie_bledow(s2);
                if(s2==0){
                    s=sprawdzenie_ruchu(ipocz, jpocz, ikonc, jkonc, i,pozycje);//zwraca-2,-3,-4, 0
                    if(s==0)jaki_ruch=0;
                    //cout<<s<<endl;
                    if(s<-1){
                        s=sprawdzenie_bicia(ipocz,jpocz,ikonc,jkonc,i,pozycje);//zwraca -2,-5,-6, 0
                        jaki_ruch=1;
                    }
                    wypisywanie_bledow(s);
                }
            }

        } while (s < 0 || s2 < 0 || s3 < 0);
        zamiana=zamiana_na_damki(ikonc,i);
        ruch(ipocz, jpocz, ikonc, jkonc, pozycje,zamiana);
        if(jaki_ruch==1) bicie(ipocz,jpocz,ikonc,jkonc,pozycje);
        s4=sprawdzenie_warunku_konca_gry(pozycje);
        alternatywna_zmiana_planszy(ipocz,jpocz,ikonc,jkonc,plansza,pozycje);
        if(jaki_ruch==1)zbicie(ipocz,jpocz,ikonc,jkonc,plansza);
        rysuj_plansze(plansza);
        i++;
    }while(s4!=0);
    //system("pause");
    return 0;
};