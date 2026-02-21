#include <stdio.h>
#include <stdlib.h>

#define byte unsigned char
#define TRUE 1
#define FALSE 0

#define maxRozmiarStringa 30
#define maxBuffor 300
#define maxIloscSlowWypowiedziU maxBuffor / 2

byte worksApp = TRUE;

typedef char string[maxRozmiarStringa];

//typedef struct {int mocWiozania; int wartosc;} wiazanie;

typedef struct {int iloscPowiozan; double * pow; } wiazaniaNeuronowe; 

int iloscSlowKloczy = 1;
string * slowaKlucze;

void slowaKluczePrt() {
    printf("--------------\n");
    for (int i = 1; i < iloscSlowKloczy; i++)
    {
        printf("0%s0\n",slowaKlucze[i]);
    }
    printf("--------------\n");
}


void stringToZero(string * meow, int wartosc) {
    for (int i = 0; i < maxRozmiarStringa; i++) (*meow)[i] = wartosc;
}


byte czyTakieSameStringi(string jeden, string dwa ) {
    for (int i = 0; jeden[i] == dwa[i]; i++) if (!jeden[i]) return TRUE;
    return FALSE;
}

int main()
{
    system("clear");

    slowaKlucze = malloc(sizeof(string));
    wiazaniaNeuronowe *  wiozaniaSlow = malloc(sizeof(wiazaniaNeuronowe));

    while (worksApp)
    {
        char buffor[maxBuffor];
        
        int wypowiedz[maxIloscSlowWypowiedziU];
        int odpowiedz[maxIloscSlowWypowiedziU];

        int iloscSlowWypowiedzi = 0;
        int iloscSlowOdpowiedzi = 0;

        short pierwszy = 0;
        fgets(buffor, sizeof(buffor),stdin);
        if (buffor[0] == '`') break;

        for (int i = 1; buffor[i] != '\n' && i < maxBuffor-1; i++)
        {
            
            if (buffor[i-1] == ' ' && buffor[i] != ' ' ) pierwszy = i;
            else if ((buffor[i-1] != ' ' && i - pierwszy < maxRozmiarStringa) && (buffor[i] == ' ' ||  buffor[i+1] == '\n') )
            {   
                string slowoPojedyncze;
                stringToZero(&slowoPojedyncze,0);

                int czyPlusJeden = 0;
                if (buffor[i+1] == '\n') czyPlusJeden = 1;

                for (int a = pierwszy; a < i+czyPlusJeden; a++) {
                    slowoPojedyncze[a-pierwszy] = buffor[a];
                    if (buffor[a] == ' ') slowoPojedyncze[a-pierwszy] = 0;
                }
                
                slowoPojedyncze[i+czyPlusJeden] = 0;

                byte czyJuzJestNaLiscie = FALSE;
                int ktoreToSlowo;

                for (ktoreToSlowo = 1; ktoreToSlowo < iloscSlowKloczy && !czyJuzJestNaLiscie; ktoreToSlowo++ )
                {
                    czyJuzJestNaLiscie =  czyTakieSameStringi(slowoPojedyncze, slowaKlucze[ktoreToSlowo]);
                    if (czyJuzJestNaLiscie == TRUE) break;
                }

                if (!czyJuzJestNaLiscie)
                {
                    iloscSlowKloczy++;
                    string * tymczasoweNoweSlowo = realloc(slowaKlucze,iloscSlowKloczy * sizeof(string));
                    wiazaniaNeuronowe * tymczasoweWiazaniaNeronowe = realloc(wiozaniaSlow, iloscSlowKloczy * sizeof(wiazaniaNeuronowe));
                    for (int nn = 0; nn < maxRozmiarStringa; nn++) tymczasoweNoweSlowo[iloscSlowKloczy-1][nn] = slowoPojedyncze[nn];
                    tymczasoweWiazaniaNeronowe[iloscSlowKloczy-1].iloscPowiozan = 1;
                    tymczasoweWiazaniaNeronowe[iloscSlowKloczy-1].pow = malloc(sizeof(double));
                    tymczasoweWiazaniaNeronowe[iloscSlowKloczy-1].pow[0] = 0.5;

                    slowaKlucze = tymczasoweNoweSlowo;
                    wiozaniaSlow = tymczasoweWiazaniaNeronowe;

                    ktoreToSlowo = iloscSlowKloczy-1;
                }

                wypowiedz[iloscSlowWypowiedzi] = ktoreToSlowo;
                iloscSlowWypowiedzi++;

            }
        }
        //generowanie odpowiedzi standardowe
        iloscSlowOdpowiedzi = 1 + rand() % 5;
        for (int i = 0; i < iloscSlowOdpowiedzi; i++) odpowiedz[i] = 1+ rand() % (iloscSlowKloczy);

        //generowanie odpowiedzi rozwinięte
            //szukanie największego rozmiaru tablicy
        int NajwiekszaWypowiedz = -2;
        for (int i = 0; i < iloscSlowWypowiedzi; i++)
        {
            if  (wiozaniaSlow[ wypowiedz[i]].iloscPowiozan > NajwiekszaWypowiedz)
            {NajwiekszaWypowiedz = wiozaniaSlow[ wypowiedz[i]].iloscPowiozan;}
        }
        NajwiekszaWypowiedz--;
            //generowanie prawdopodobnych PODSTAWOWE;
        double prawodpodobienstwoNaSlowoX[NajwiekszaWypowiedz];
        for (int i = 0; i < NajwiekszaWypowiedz; i++) prawodpodobienstwoNaSlowoX[i] = 1;

        for (int i = 0; i < iloscSlowWypowiedzi; i++ )
        {
            for (int a = 1; a < wiozaniaSlow[ wypowiedz[i]].iloscPowiozan; a++ )
            {
                prawodpodobienstwoNaSlowoX[a]*= wiozaniaSlow[ wypowiedz[i]].pow[a];
            }
        }
            //sortowanie
        prawodpodobienstwoNaSlowoX[0] = 999999;
        int posortowaneSLowaOdNajmniejszego[NajwiekszaWypowiedz];
        char czyJuzByl[NajwiekszaWypowiedz];
        for (int i = 0; i < NajwiekszaWypowiedz; i++)
        {
            posortowaneSLowaOdNajmniejszego[i] = 1;
            czyJuzByl[i] = 1;
        }

        for (int i = 1; i < NajwiekszaWypowiedz; i++)
        {
            double najmniejszyMeow = 999999;
            int najmneijszyUwU = 1;
            for (int a = 1; a < NajwiekszaWypowiedz; a++)
            {
                if (najmniejszyMeow > prawodpodobienstwoNaSlowoX[a] && czyJuzByl[a])
                {
                    najmniejszyMeow = prawodpodobienstwoNaSlowoX[a];
                    najmneijszyUwU = a;
                }
            }
            czyJuzByl[najmneijszyUwU] = 0;
            posortowaneSLowaOdNajmniejszego[i] = najmneijszyUwU;
        }
            //wypisywanie UwU
        for (int i = 0; i < iloscSlowWypowiedzi; i++){
            for (int a = 1; a < wiozaniaSlow[wypowiedz[i]].iloscPowiozan; a++) printf("(%s %f %d) ",slowaKlucze[a], wiozaniaSlow[wypowiedz[i]].pow[a],a );
            printf("|%d \n",wiozaniaSlow[wypowiedz[i]].iloscPowiozan);
        }
            //aplikacja danych
        int licznik = 1;
        for (int i = 0; NajwiekszaWypowiedz > licznik && i < iloscSlowWypowiedzi; i+=1 + rand() % 2 )
        {
            wypowiedz[i] = posortowaneSLowaOdNajmniejszego[licznik];
            licznik++;
        }




        //wypisywanie odpowiedzi
        printf("|");
        for (int i = 0; i < iloscSlowOdpowiedzi; i++) printf("%s ",slowaKlucze[odpowiedz[i]]);
        printf("\n");

        //uczenie
        char yesOrNo[5];
        char yesOrNoBool = 0;
        printf("Czy poprawna odpowiedz: Y/N/` ");
        fgets(yesOrNo, 5,stdin);

        if (yesOrNo[0] == 'y' || yesOrNo[0] == 'Y' || yesOrNo[0] == 'T' || yesOrNo[0] == 't') yesOrNoBool--;
        else if (yesOrNo[0] == 'N' || yesOrNo[0] == 'n') yesOrNoBool=1;
        else if (yesOrNo[0] == '`') break;
        
            #define kodWypowiedzi wypowiedz[i]
            #define kodOdpowiedzi odpowiedz[a]
            #define iloscPowiozanDD wiozaniaSlow[kodWypowiedzi].iloscPowiozan

            for (int i = 0; i < iloscSlowWypowiedzi; i++)
            {
                int * iloscPowiozanD =  &wiozaniaSlow[kodWypowiedzi].iloscPowiozan;
                int najwekszyElementZOdpowiedzi = -90000;

                for (int a = 0; a < iloscSlowOdpowiedzi; a++)
                {
                    if (kodOdpowiedzi > najwekszyElementZOdpowiedzi) najwekszyElementZOdpowiedzi = kodOdpowiedzi;
                }
                
                if (iloscPowiozanDD <= najwekszyElementZOdpowiedzi)
                {
                    int poprzedniaIlosc = wiozaniaSlow[kodWypowiedzi].iloscPowiozan;
                    wiozaniaSlow[kodWypowiedzi].iloscPowiozan = najwekszyElementZOdpowiedzi+1;
                    double * tmp = realloc(wiozaniaSlow[kodWypowiedzi].pow, wiozaniaSlow[kodWypowiedzi].iloscPowiozan * sizeof(double));
                    for (int c = poprzedniaIlosc; c <= najwekszyElementZOdpowiedzi; c++ ) tmp[c] = 0.50;
                    wiozaniaSlow[kodWypowiedzi].pow = tmp;
                }

                for (int a = 0; a < iloscSlowOdpowiedzi; a++)
                {
                    wiozaniaSlow[kodWypowiedzi].pow[kodOdpowiedzi] += (double)yesOrNoBool/500.0f;
                }

            }
        
        
    }


    //cleaning memory 
    for (int i = 1; i < iloscSlowKloczy; i++) if (wiozaniaSlow[i].pow != NULL ) free(wiozaniaSlow[i].pow);
    free(wiozaniaSlow);
    free(slowaKlucze);
    return 67;
}



