#include"definicje.h"
#include"narzedzia.h"
#include"negamax.h"
#include"ocena.h"
#include<string.h>

typedef struct{
    char *nazwa;
    void (*funptr)();
}komenda;

polegry poletko;
char bufor[1024];
int czy_wygrana;

void uci();
void szukaj();
void poczatek();
void wypisz_stan_gry();
void graj();
void ruch_gracza_z_konsoli();
void pomoc();
void poruszanie();
void test_01();
void test_02();

komenda komendy[] = {{ "id",uci},{"szukaj",szukaj},{"odnowa",poczatek},{"wypisz",wypisz_stan_gry},{"graj",graj},{"ruch",ruch_gracza_z_konsoli},{"pomoc",pomoc},{"porusz",poruszanie}};

void main(){
    //test_01();
    //test_02();
    printf("Witamy w KiK\nAby uzyskac informacje o komendach wpisz pomoc\n");
    do
    {
        if(czy_wygrana==1){
            switch(poletko.gracz_na_ruchu){
                case 0:{
                    printf("WYGRALY O!!!\n");
                    break;
                }
                case 1:{
                    printf("WYRGALY X!!!\n");
                    break;
                }
            }
            break;
        }
        else{
            printf("Komenda: ");
            scanf("%s", bufor);
            for(int i=0; i<8; i++)
                if(!strcmp(bufor, komendy[i].nazwa))
                    komendy[i].funptr(); 
        }
    }
    while(strcmp(bufor, "koniec"));
    printf("hasta maniana\n"); 
}

void uci(){
    printf("gra KiK\n");
    printf("wersja sigma 0.1\n");
    printf("autor: kot co przebiegl po klawiaturze");
    printf("autor v2: ci co akurat przy niej siedzieli: \n\t Adam Laziuk \n\t Dominik Soltys\n");
}

char* enum2txt(int ocena){
    if(ocena==HANIEBNA_PORAZKA){
        return "haniebna porazka";
    if(ocena==SUKCESYWNA_WYGRANA){
        return "sukcesywna wygrana";
    }
    return "";
    }
}

void szukaj(){
    negamax(&poletko,3);
}

void poczatek(){
    ustaw_stan_gry(&poletko);
}

void wypisz_stan_gry(){
    wypisz(&poletko);
}

void graj(){
    int glebokosc;
    printf("Podaj glebokosc: ");
    scanf("%d", &glebokosc);
    ruch_na_liscie *ruchy=legalne_ruchy(&poletko);
    if(ruchy){
        ruch *ruch_debesciak=NULL;
        int ocena_posuniecia,debesciak=0;
        for(ruch_na_liscie *ruch=ruchy;ruch;ruch=ruch->nastepny){
            //printf("info oceniam ruch %d %d\r",ruch->dana.na_pole.wiersz,ruch->dana.na_pole.kolumna);
            polegry wariant=wykonaj_ruch(&poletko,ruch->dana);
            ocena_posuniecia=negamax(&wariant,glebokosc);
            wariant.gracz_na_ruchu=ruch_O;
            //wariant=czystka(&wariant,debesciak); ni chuja nie dziala poprawnie
            int x=sprawdz_dlugosc_od_poz(&wariant,ruch->dana);
            ocena_posuniecia=ocena_posuniecia*x;
            if (ocena_posuniecia>debesciak){
                debesciak=ocena_posuniecia;
                ruch_debesciak=&ruch->dana;
                //printf("%d %d (%s %d) jest debesciak\n",ruch->dana.na_pole.wiersz,ruch->dana.na_pole.kolumna,enum2txt(ocena_posuniecia),ocena_posuniecia);
            }
        }
        if(!ruch_debesciak) ruch_debesciak=&ruchy->dana;
        poletko = wykonaj_ruch(&poletko,*ruch_debesciak);
        polegry hah=poletko;
        //printf("info debesciak wykonany (%s %d)\n", enum2txt(debesciak),debesciak);
        zabij_ruchy_na_liscie(&ruchy);
    }
    else  
        printf("info nie ma legalnego posuniecia\n");
    wypisz(&poletko);
    czy_wygrana=checkup(&poletko);
}

void ruch_gracza_z_konsoli(){
    int ruchstr,ruchstr2;
    printf("Kolumna(od 1 do %d): ",SZEROKOSC);
    scanf("%d",&ruchstr);
    printf("Wiersz(od 1 do %d): ",WYSOKOSC);
    scanf("%d",&ruchstr2);
    ruchstr-=1;
    ruchstr2-=1;
    if(ruchstr>=0&&ruchstr<SZEROKOSC&&ruchstr2>=0&&ruchstr2<WYSOKOSC&&(poletko.pole[ruchstr2][ruchstr]==PUSTE)){
        ruch posuniecie;
        posuniecie.na_pole.kolumna=ruchstr;
        posuniecie.na_pole.wiersz=ruchstr2;
        poletko=wykonaj_ruch(&poletko,posuniecie);
        wypisz(&poletko);
    }
    else{
        printf("Nie, nie, nie ma takiej opcji (zle dane wejsciowe lub pole nie jest puste)\n");
    }
    czy_wygrana=checkup(&poletko);
}

void pomoc(){
    printf("Komendy:\n");
    printf("id \t\t Informacje o wersji i autorach gry.\n");  
    printf("poczatek \t Ustawia plansze do gry\n");
    printf("odnowa \t\t Resetuje gre(WiP).\n");
    printf("wypisz \t\t Wypisuje obecny stan planszy.\n");
    printf("graj \t\t Ruch gracza AI(czasami gorszy niz niemowle).\n");
    printf("ruch \t\t Ruch gracza z konsoli (zostanie zadane pytanie o konkretna kolumne i wiersz.\n");
    printf("porusz \t\t Pomoc w poruszaniu sie po programie.\n");
    printf("pomoc \t\t Po wpisaniu tego ponownie zostania pokazana niespodzianka.\n");
    printf("koniec \t\t Konczy program.\n\n\n");
}

void poruszanie(){
    printf("Poruszanie: \n");
    printf("Najlepiej zaczac gre jako pierwszy od lewego gornego rogu.\n");
    printf("Zacznij wiec od komendy poczatek (ustawiasz plansze).\n");
    printf("Wpisz komende ruch\n");
    printf("Zostaniesz zadane pytanie o konkretna kolumne i wiersz - wystarczy wpisac liczbe.\n");
    printf("Potem wystarczy wpisac graj i podac glebokosc na ktora gracz AI ma przeszukac drzewko gry.\n");
    printf("Powtorz (od komendy ruch)\n\n\n");
}

void test_01(){
    poletko.pole[0][0]=X;
    poletko.pole[0][1]=O;
    poletko.pole[0][2]=X;
    poletko.gracz_na_ruchu=ruch_O;
    int glebokosc=3;
    ruch_na_liscie *ruchy=legalne_ruchy(&poletko);
    if(ruchy){
        ruch *ruch_debesciak=NULL;
        int ocena_posuniecia,debesciak=0;
        for(ruch_na_liscie *ruch=ruchy;ruch;ruch=ruch->nastepny){
            //printf("info oceniam ruch %d %d\r",ruch->dana.na_pole.wiersz,ruch->dana.na_pole.kolumna);
            polegry wariant=wykonaj_ruch(&poletko,ruch->dana);
            ocena_posuniecia=negamax(&wariant,glebokosc);
            wariant.gracz_na_ruchu=ruch_O;
            wariant=czystka(&wariant,debesciak);
            int x=sprawdz_dlugosc_od_poz(&wariant,ruch->dana);
            ocena_posuniecia=ocena_posuniecia*x;
            if (ocena_posuniecia>debesciak){
                debesciak=ocena_posuniecia;
                ruch_debesciak=&ruch->dana;
                //printf("%d %d (%s %d) jest debesciak\n",ruch->dana.na_pole.wiersz,ruch->dana.na_pole.kolumna,enum2txt(ocena_posuniecia),ocena_posuniecia);
            }
        }
        if(!ruch_debesciak) ruch_debesciak=&ruchy->dana;
        poletko = wykonaj_ruch(&poletko,*ruch_debesciak);
        polegry hah=poletko;
        //printf("info debesciak wykonany (%s %d)\n", enum2txt(debesciak),debesciak);
        zabij_ruchy_na_liscie(&ruchy);
    }
    else  
        printf("info nie ma legalnego posuniecia\n");
    wypisz(&poletko);
    polegry hah=poletko;

}

void test_02(){
    
}