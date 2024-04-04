#ifndef NARZEDZIA

#define NARZEDZIA

#include "definicje.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdbool.h>

void wypisz(polegry *poletko){
    for(int i=0;i<WYSOKOSC;i++){
        for (int j=0;j<SZEROKOSC;j++){
               switch (poletko->pole[i][j]){
                case PUSTE:
                    printf("   ");
                    break;
                case X:
                    printf(" X ");
                    break;
                case O:
                    printf(" O ");
                    break;
               }

               if(j!=SZEROKOSC-1) printf("|"); 
        }
        printf("\n");
        for(int g=0;g<SZEROKOSC;g++) 
            if(i!=WYSOKOSC-1)
                if(g==SZEROKOSC-1)printf("---");
                    else printf("----");
        printf("\n");
    }
    printf("\n\n\n");
}
void ustaw_stan_gry(polegry *poletko){
    for (int i=0;i<SZEROKOSC;i++)
        for (int j=0;j<WYSOKOSC;j++)
        poletko->pole[i][j]=PUSTE;
    poletko->gracz_na_ruchu = ruch_X;
}


ruch_na_liscie *legalne_ruchy(polegry* plansza){
    ruch_na_liscie *glowa=NULL, *ptr=NULL;
    ruch ruch_legalny;
    for(int w=0;w<WYSOKOSC;w++)
        for(int k=0;k<SZEROKOSC;k++)
            if(plansza->pole[w][k]==PUSTE){
                if(ptr){
                    ptr->nastepny=(ruch_na_liscie*)calloc(1,sizeof(ruch_na_liscie));
                    ptr=ptr->nastepny;
                }
                else
                    ptr=(ruch_na_liscie*)calloc(1,sizeof(ruch_na_liscie));
                ptr->nastepny==NULL;
                ptr->dana.na_pole = (pole) {w,k};
                if(!glowa) glowa=ptr;
            }  
                
    return glowa;
}



int sprawdz_dlugosc(polegry *plansza){

    int licznik=0,maxi=0,t=0,nt=0,kierunek=0;
    t=2;
    nt=1;
    for(int g=0;g<2;g++,t=1,nt=2){
        for(int w=0;w<WYSOKOSC;w++){
            for(int k=0;k<SZEROKOSC;k++){
                if((int)plansza->pole[w][k]==t){
                    for(int j=w;j<WYSOKOSC;j++,licznik++){
                        if(plansza->pole[j][k]==PUSTE||plansza->pole[j][k]==nt) break;
                        if(licznik==CIAG_WYRGANY){
                            maxi=licznik;
                            return maxi;
                        }
                    }
                    licznik--;
                    for(int j=w;j>=0;j--,licznik++){
                        if(plansza->pole[j][k]==PUSTE||plansza->pole[j][k]==nt) break;
                        if(licznik==CIAG_WYRGANY){
                            maxi=licznik;
                            return maxi;
                        }
                    }   
                    if(licznik>maxi) maxi=licznik;
                    licznik=0;
                    for(int j=k;j<SZEROKOSC;j++,licznik++){
                        if(plansza->pole[w][j]==PUSTE||plansza->pole[w][j]==nt) break;
                        if(licznik==CIAG_WYRGANY){
                            maxi=licznik;
                            return maxi;
                        }
                    }
                    licznik--;
                    for(int j=k;j>=0;j--,licznik++){
                        if(plansza->pole[w][j]==PUSTE||plansza->pole[w][j]==nt) break;
                        if(licznik==CIAG_WYRGANY){
                            maxi=licznik;
                            return maxi;
                        }
                    }
                    if(licznik>maxi) maxi=licznik;
                    licznik=0;
                    int i=w,j=k;
                    while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
                        if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                            i--;
                            j--;
                            licznik++;
                        }else break;
                        if(licznik==CIAG_WYRGANY){
                            maxi=licznik;
                            return maxi;
                        }
                    }
                    i=w;
                    j=k;
                    licznik--;
                    while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
                        if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                            i++;
                            j++;
                            licznik++;
                        }else break;
                        if(licznik==CIAG_WYRGANY){
                            maxi=licznik;
                            return maxi;
                        }
                    }
                    licznik=0;
                    i=w;
                    j=k;
                    if(licznik>maxi) maxi=licznik;
                    while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
                        if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                            i--;
                            j++;
                            licznik++;
                        }else break;
                        if(licznik==CIAG_WYRGANY){
                            maxi=licznik;
                            return maxi;
                        }
                    }
                    i=w;
                    j=k;
                    licznik--;
                    while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
                        if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                            i++;
                            j--;
                            licznik++;
                        }else break;
                        if(licznik==CIAG_WYRGANY){
                            maxi=licznik;
                            return maxi;
                        }
                    }
                    if(licznik>maxi) maxi=licznik;
                    licznik=0;
                }
            }
        }
    }
    return maxi;
  
}

int checkup(polegry *plansza){
    int x=sprawdz_dlugosc(plansza);
    if(x==CIAG_WYRGANY) return 1;
    else return 0;
}

int sprawdz_dlugosc_od_poz(polegry *plansza,ruch posuniecie){

    int licznik=0,maxi=0,t=0,nt=0,kierunek=0;
    if(plansza->gracz_na_ruchu==ruch_O){
        t=2;
        nt=1;
    }else{
        t=1;
        nt=2;
    }
    int w=posuniecie.na_pole.wiersz,k=posuniecie.na_pole.kolumna;
    for(int j=w;j<WYSOKOSC;j++,licznik++){
        if(plansza->pole[j][k]==PUSTE||plansza->pole[j][k]==nt) break;
        if(licznik==CIAG_WYRGANY){
            maxi=licznik;
            return maxi;
        }
    }
    licznik--;
    for(int j=w;j>=0;j--,licznik++){
        if(plansza->pole[j][k]==PUSTE||plansza->pole[j][k]==nt) break;
        if(licznik==CIAG_WYRGANY){
            maxi=licznik;
            return maxi;
        }
    }   
    if(licznik>maxi) maxi=licznik;
    licznik=0;
    for(int j=k;j<SZEROKOSC;j++,licznik++){
        if(plansza->pole[w][j]==PUSTE||plansza->pole[w][j]==nt) break;
        if(licznik==CIAG_WYRGANY){
            maxi=licznik;
            return maxi;
        }
    }
    licznik--;
    for(int j=k;j>=0;j--,licznik++){
        if(plansza->pole[w][j]==PUSTE||plansza->pole[w][j]==nt) break;
        if(licznik==CIAG_WYRGANY){
            maxi=licznik;
        }
    }
    if(licznik>maxi) maxi=licznik;
    licznik=0;
    int i=w,j=k;
    while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
        if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
            i--;
            j--;
            licznik++;
        }else break;
        if(licznik==CIAG_WYRGANY){
            maxi=licznik;
            return maxi;
        }
    }
    i=w;
    j=k;
    licznik--;
    while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
        if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
            i++;
            j++;
            licznik++;
        }else break;
        if(licznik==CIAG_WYRGANY){
            maxi=licznik;
            return maxi;
        }
    }
    licznik=0;
    i=w;
    j=k;
    if(licznik>maxi) maxi=licznik;
    while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
        if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
            i--;
            j++;
            licznik++;
        }else break;
        if(licznik==CIAG_WYRGANY){
            maxi=licznik;
            return maxi;
        }
    }
    i=w;
    j=k;
    licznik--;
    while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
        if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
            i++;
            j--;
            licznik++;
        }else break;
    if(licznik==CIAG_WYRGANY){
        maxi=licznik;
        return maxi;
        }
    }
    if(licznik>maxi) maxi=licznik;  
    return maxi;
  
}

bool czy_koniec(polegry *plansza, ruch posuniecie,int debesciak,int kierunek){
    int licznik=0,t=0,nt=0,block=0;
    if(plansza->gracz_na_ruchu==ruch_O){
        t=2;
        nt=1;
    }else{
        t=1;
        nt=2;
    }
    int w=posuniecie.na_pole.wiersz,k=posuniecie.na_pole.kolumna;
    switch(kierunek){
        case 5:{
            for(int j=w;j<WYSOKOSC;){
                if(plansza->pole[j][k]==PUSTE){
                    return false;
                }
                if(plansza->pole[j][k]==nt){
                    block++;
                    break;
                }
                j++;
                if(j==SZEROKOSC||j==-1){
                    block++;
                    break;
                }
            }
            for(int j=w;j>=0;){
                if(plansza->pole[j][k]==PUSTE){
                    return false;
                }
                if(plansza->pole[j][k]==nt){
                    block++;
                    break;
                }
                j--;
                if(j==SZEROKOSC||j==-1){
                    block++;
                    break;
                }
            }
            if(block==2) return true;
            break;
        }
        case 3:{
            for(int j=k;j<WYSOKOSC;){
                if(plansza->pole[w][j]==PUSTE){
                    return false;
                }
                if(plansza->pole[w][j]==nt){
                    block++;
                    break;
                }
                j++;
                if(j==SZEROKOSC||j==-1){
                    block++;
                    break;
                }
            }
            for(int j=k;j>=0;){
                if(plansza->pole[w][j]==PUSTE){
                    return false;
                }
                if(plansza->pole[w][j]==nt){
                    block++;
                    break;
                }
                j--;
                if(j==SZEROKOSC||j==-1){
                    block++;
                    break;
                }
            }
            if(block==2) return true;
            break;
        }
        case 4:{
            int i=w,j=k;
            while(plansza->pole[i][j]){
                if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                    if(plansza->pole[i][j]==PUSTE){
                        return false;
                        break;
                    }
                    if(plansza->pole[i][j]==nt){
                        block++;
                        break;
                    }
                    i++;
                    j++;
                    if(i==-1||j==SZEROKOSC||i==WYSOKOSC||j==-1){
                        block++;
                        break;
                    }
                }else break;
            }
            i=w;
            j=k;
            while(plansza->pole[i][j]){
                if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                    if(plansza->pole[i][j]==PUSTE){
                        return false;
                        break;
                    }
                    if(plansza->pole[i][j]==nt){
                        block++;
                        break;
                    }
                    i--;
                    j--;
                    if(i==-1||j==SZEROKOSC||i==WYSOKOSC||j==-1){
                        block++;
                        break;
                    }
                }else break;
            }
            if(block==2) return true;
            break;
        }
        case 6:{
            int i=w,j=k;
            while(plansza->pole[i][j]){
                if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                    if(plansza->pole[i][j]==PUSTE){
                        return false;
                        break;
                    }
                    if(plansza->pole[i][j]==nt){
                        block++;
                        break;
                    }
                    i++;
                    j--;
                    if(i==-1||j==SZEROKOSC||i==WYSOKOSC||j==-1){
                        block++;
                        break;
                    }
                }else break;
            }
            i=w;
            j=k;
            while(plansza->pole[i][j]){
                if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                    if(plansza->pole[i][j]==PUSTE){
                        return false;
                        break;
                    }
                    if(plansza->pole[i][j]==nt){
                        block++;
                        break;
                    }
                    i--;
                    j++;
                    if(i==-1||j==SZEROKOSC||i==WYSOKOSC||j==-1){
                        block++;
                        break;
                    }
                }else break;
            }
            if(block==2) return true;
            break;
        }
    }
}

polegry czystka(polegry *plansza,int debesciak){
    polegry *czystosc=plansza;
    ruch posuniecie;
    int licznik,t,nt;
    if(plansza->gracz_na_ruchu==ruch_O){
        t=2;
        nt=1;
    }else{
        t=1;
        nt=2;
    }
    if(debesciak==0) return *czystosc;
    if(debesciak==1) return *czystosc;
    for(int w=0;w<WYSOKOSC;w++){
        for(int k=0;k<SZEROKOSC;k++){
            if(czystosc->pole[w][k]==t){
                for(int j=w;j<WYSOKOSC;j++,licznik++){
                    if(plansza->pole[j][k]==PUSTE||plansza->pole[j][k]==nt) break; 
                    if(licznik>=debesciak){              
                        posuniecie.na_pole.wiersz=w;
                        posuniecie.na_pole.kolumna=k;
                        if(czy_koniec(czystosc,posuniecie,debesciak,5)==true){
                            for(int j=w;j<WYSOKOSC;j++){
                                czystosc->pole[j][k]=PUSTE;
                            }
                        }
                    }
                }
                licznik=0;
                for(int j=k;j<SZEROKOSC;j++,licznik++){
                    if(plansza->pole[w][j]==PUSTE||plansza->pole[w][j]==nt) break;       
                    if(licznik>=debesciak){             
                        posuniecie.na_pole.wiersz=w;
                        posuniecie.na_pole.kolumna=k;
                        if(czy_koniec(czystosc,posuniecie,debesciak,3)==true){
                            for(int j=k;j<SZEROKOSC;j++){
                                czystosc->pole[w][j]=PUSTE;
                            }
                        }
                    }
                }
                licznik=0;
                int i=w,j=k;
                while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
                    if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                        i++;
                        j++;
                        licznik++;
                    }else break;   
                    if(licznik>=debesciak){                    
                        posuniecie.na_pole.wiersz=w;
                        posuniecie.na_pole.kolumna=k;
                        if(czy_koniec(czystosc,posuniecie,debesciak,4)==true){
                            while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
                                if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                                    czystosc->pole[i][j]=PUSTE;
                                    i++;
                                    j++;
                                    }else break;
                            }
                        }
                    }
                }
                licznik=0;
                i=w;
                j=k;
                while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
                    if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                        i++;
                        j--;
                        licznik++;
                    }else break;     
                    if(licznik>=debesciak){                  
                        posuniecie.na_pole.wiersz=w;
                        posuniecie.na_pole.kolumna=k;
                        if(czy_koniec(czystosc,posuniecie,debesciak,6)==true){
                            while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
                                if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                                    czystosc->pole[i][j]=PUSTE;
                                    i++;
                                    j++;
                                }else break;
                            }
                        }
                    }
                licznik=0;
                }
            }
        }
    }
    return *czystosc;
}

// WiP w skrocie ma usuwac niepotrzebne ciagi nie naruszajac legalnych ruchow(w wariancie) zeby debesciak byl dalej mozliwy przy "remisach" np 3 z blokiem w jednym miejscu i 2 z mozliwascia zrobienia 3 w ciagu bez bloku 

polegry wykonaj_ruch(polegry *plansza,ruch posuniecie){
    
    assert(posuniecie.na_pole.kolumna>=0&&posuniecie.na_pole.kolumna<SZEROKOSC&&posuniecie.na_pole.wiersz>=0&&posuniecie.na_pole.wiersz<WYSOKOSC);
    assert(plansza->pole[posuniecie.na_pole.wiersz][posuniecie.na_pole.kolumna]==PUSTE);
    polegry nowe = *plansza;
    nowe.pole[posuniecie.na_pole.wiersz][posuniecie.na_pole.kolumna] =nowe.gracz_na_ruchu == ruch_O ? O : X;
    nowe.gracz_na_ruchu = nowe.gracz_na_ruchu==ruch_O ? ruch_X : ruch_O;
    return nowe;
}



#endif