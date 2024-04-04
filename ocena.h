#ifndef OCENA

#define OCENA

#include "definicje.h"

int ocena_sytuacji(polegry* plansza){
    int licznikt=0,liczniknt=0,maxi=0,t=0,nt=0;
    if(plansza->gracz_na_ruchu==ruch_O){
        t=2;
        nt=1;
    }else{
        t=1;
        nt=2;
    }
    for(int w=0;w<WYSOKOSC;w++){
        for(int k=0;k<SZEROKOSC;k++){
            if((int)plansza->pole[w][k]==t){
                for(int j=w;j<WYSOKOSC;j++,licznikt++){
                    if(plansza->pole[j][k]==PUSTE||plansza->pole[j][k]==nt) break;
                    if(licznikt==CIAG_WYRGANY){
                        return 1;
                    }
                }
                licznikt--;
                for(int j=w;j>=0;j--,licznikt++){
                    if(plansza->pole[j][k]==PUSTE||plansza->pole[j][k]==nt) break;
                    if(licznikt==CIAG_WYRGANY){
                        return 1;
                    }
                }   
                if(licznikt>maxi) maxi=licznikt;
                licznikt=0;
                for(int j=k;j<SZEROKOSC;j++,licznikt++){
                    if(plansza->pole[w][j]==PUSTE||plansza->pole[w][j]==nt) break;
                    if(licznikt==CIAG_WYRGANY){
                        return 1;
                    }
                }
                licznikt--;
                for(int j=k;j>=0;j--,licznikt++){
                    if(plansza->pole[w][j]==PUSTE||plansza->pole[w][j]==nt) break;
                    if(licznikt==CIAG_WYRGANY){
                        return 1;
                    }
                }
                if(licznikt>maxi) maxi=licznikt;
                licznikt=0;
                int i=w,j=k;
                while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
                    if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                        i--;
                        j--;
                        licznikt++;
                    }else break;
                    if(licznikt==CIAG_WYRGANY){
                        return 1;
                    }
                }
                i=w;
                j=k;
                licznikt--;
                while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
                    if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                        i++;
                        j++;
                        licznikt++;
                    }else break;
                    if(licznikt==CIAG_WYRGANY){
                        return 1;
                    }
                }
                if(licznikt>maxi) maxi=licznikt;
                licznikt=0;
                i=w;
                j=k;
                while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
                    if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                        i--;
                        j++;
                        licznikt++;
                    }else break;
                    if(licznikt==CIAG_WYRGANY){
                        return 1;
                    }
                }
                i=w;
                j=k;
                licznikt--;
                while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
                    if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                        i++;
                        j--;
                        licznikt++;
                    }else break;
                    if(licznikt==CIAG_WYRGANY){
                        return 1;
                    }
                }
                if(licznikt>maxi) maxi=licznikt;
                licznikt=0;
            }
        }
    }
    licznikt=maxi;
    maxi=0;
    if(t==1){
        t=2;
        nt=1;
    }else{
        t=1;
        nt=2;
    }
    for(int w=0;w<WYSOKOSC;w++){
        for(int k=0;k<SZEROKOSC;k++){
            if((int)plansza->pole[w][k]==t){
                for(int j=w;j<WYSOKOSC;j++,liczniknt++){
                    if(plansza->pole[j][k]==PUSTE||plansza->pole[j][k]==nt) break;
                    if(liczniknt==CIAG_WYRGANY){
                        return 0;
                    }
                }
                liczniknt--;
                for(int j=w;j>=0;j--,liczniknt++){
                    if(plansza->pole[j][k]==PUSTE||plansza->pole[j][k]==nt) break;
                    if(liczniknt==CIAG_WYRGANY){
                        return 0;
                    }
                }   
                if(liczniknt>maxi) maxi=liczniknt;
                liczniknt=0;
                for(int j=k;j<SZEROKOSC;j++,liczniknt++){
                    if(plansza->pole[w][j]==PUSTE||plansza->pole[w][j]==nt) break;
                    if(liczniknt==CIAG_WYRGANY){
                        return 0;
                    }
                }
                liczniknt--;
                for(int j=k;j>=0;j--,liczniknt++){
                    if(plansza->pole[w][j]==PUSTE||plansza->pole[w][j]==nt) break;
                    if(liczniknt==CIAG_WYRGANY){
                        return 0;
                    }
                }
                if(liczniknt>maxi) maxi=liczniknt;
                liczniknt=0;
                int i=w,j=k;
                while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
                    if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                        i--;
                        j--;
                        liczniknt++;
                    }else break;
                    if(liczniknt==CIAG_WYRGANY){
                        return 0;
                    }
                }
                i=w;
                j=k;
                liczniknt--;
                while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
                    if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                        i++;
                        j++;
                        liczniknt++;
                    }else break;
                    if(liczniknt==CIAG_WYRGANY){
                        return 0;
                    }
                }
                liczniknt=0;
                i=w;
                j=k;
                if(liczniknt>maxi) maxi=liczniknt;
                while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
                    if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                        i--;
                        j++;
                        liczniknt++;
                    }else break;
                    if(liczniknt==CIAG_WYRGANY){
                        return 0;
                    }
                }
                i=w;
                j=k;
                liczniknt--;
                while(plansza->pole[i][j]!=PUSTE&&plansza->pole[i][j]!=nt){
                    if(i<WYSOKOSC&&j<SZEROKOSC&&i>=0&&j>=0){
                        i++;
                        j--;
                        liczniknt++;
                    }else break;
                    if(liczniknt==CIAG_WYRGANY){
                        return 0;
                    }
                }
                if(liczniknt>maxi) maxi=liczniknt;
                liczniknt=0;
            }
        }
    }
    liczniknt=maxi;
    if(licznikt>liczniknt) return 1;
    else return 0;
}


#endif