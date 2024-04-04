#ifndef NEGAMAX

#define NEGAMAX

#include "definicje.h"
#include "narzedzia.h"
#include "ocena.h"
#include <assert.h>
#include <stdio.h>

int porownaj_oceny(int ocena1,int ocena2){
    return ocena1-ocena2;
}

void zabij_ruchy_na_liscie(ruch_na_liscie **ptr){
    if((*ptr)->nastepny==NULL){
        *ptr=NULL;
    }
    else{
        ruch_na_liscie *chwilowy=*ptr;
        while(chwilowy->nastepny->nastepny!=NULL){
            chwilowy=chwilowy->nastepny;
        }
        free(chwilowy->nastepny);
        chwilowy->nastepny=NULL;
    }

}

int _negamax(polegry* p,int glebokosc,int alfa,int beta){
    if(!glebokosc) return ocena_sytuacji(p);
    ruch_na_liscie *ruchy = legalne_ruchy(p), *ptr = ruchy;
    if(!ruchy) return ocena_sytuacji(p);
    int ocena_wezla=ocena_sytuacji(p), ocena_czymtasowa,czy_nowy_debesciak;
    do{
        polegry potomne=wykonaj_ruch(p,ruchy->dana);
        ocena_czymtasowa = -_negamax(&potomne,glebokosc-1,beta,alfa);
        czy_nowy_debesciak=porownaj_oceny(ocena_czymtasowa,ocena_wezla);
        if(czy_nowy_debesciak>0){
            ocena_wezla=ocena_czymtasowa;
            if(porownaj_oceny(ocena_wezla,alfa)>0);
                alfa=ocena_wezla;
        }
        if(porownaj_oceny(alfa,beta)>=0){
            ocena_wezla=alfa;
            break; 
        } 
        ruchy=ruchy->nastepny;
    } while(ruchy);
    zabij_ruchy_na_liscie(&ptr);
    return ocena_wezla;
}
int negamax(polegry* p,int glebokosc){
    return _negamax(p,glebokosc,1,0);
}


#endif