#ifndef DEFINICJE

#define DEFINICJE

#define SZEROKOSC 10
#define WYSOKOSC 10
#define CIAG_WYRGANY 4

typedef enum{PUSTE, X, O} typ_pola;
typedef enum{ruch_X,ruch_O} czyj_ruch;
typedef enum{ruch_bota,ruch_gracza} kogo_ruch;
typedef enum{SUKCESYWNA_WYGRANA,HANIEBNA_PORAZKA,NIC} co_sie_dzieje;


typedef struct{
    int dlugosc,kierunek;
}co_grac;

typedef struct{
    int wiersz,kolumna;
} pole;

typedef struct{
    pole na_pole;
}ruch;

typedef struct element{
    ruch dana;
    struct element *nastepny;
} ruch_na_liscie;

typedef struct{
    co_sie_dzieje typ_oceny;
    int tozero;
}ocena_pozycji;

typedef struct{
    typ_pola pole[SZEROKOSC][WYSOKOSC];
    czyj_ruch gracz_na_ruchu;
    kogo_ruch kto_gra;
} polegry;


#endif