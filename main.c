#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define zerowanieSlowa for (int bb = 0; bb < sizeof(slowo); bb++) slowo.str[bb] = 0;

typedef struct {char str[20]; int * pow; short elementy;} string;


typedef unsigned char byte;


string * slowaKlucze;
short iloscSlowKluczy = 1;

byte czyTakieSameStringi(string jeden, string dwa )
{
    for (int i = 0; jeden.str[i] == dwa.str[i]; i++) if (!jeden.str[i]) return TRUE;
    return FALSE;
}

int main()
{
    system("clear");

    slowaKlucze = malloc(sizeof(string) * iloscSlowKluczy  );

    byte iloscSlowWWypowiedzi;
    short * slowaWWypowiedzi = malloc(sizeof(short));

    while (TRUE)
    {
        char buffor[200];
        fgets(buffor,sizeof(buffor),stdin);
        byte licznik = 0;
        iloscSlowWWypowiedzi = 1;
        string slowo;
        zerowanieSlowa

        if (buffor[0] == '`') break;

        for (int i = 0; buffor[0] != '\n' && buffor[i] != 0 && i < 200; i++)
        {
            if (i > 0) if (buffor[i-1] == 32 && buffor[i] != 32 || !buffor[i+1])
            {
                for (int z = licznik; z > 0; z--) if (slowo.str[z] == 32) slowo.str[z]=0;
                
                byte czyJuzSieZnajduje = FALSE;
                int y;

                for (y = 1; y < iloscSlowKluczy && !czyJuzSieZnajduje; y++)
                {
                    printf("%s %d %s %d\n",slowo.str,0,slowaKlucze[y].str,0);
                    if (czyTakieSameStringi(slowaKlucze[y],slowo) ) czyJuzSieZnajduje = TRUE;
                }

                if (!czyJuzSieZnajduje)
                {
                    iloscSlowKluczy++;
                    string * tymczasowy = realloc(slowaKlucze,sizeof(string) * iloscSlowKluczy);
                    slowaKlucze = tymczasowy;

                    for (int b = 0; b < licznik; b++) slowaKlucze[iloscSlowKluczy-1].str[b] = slowo.str[b];

                    slowaKlucze[iloscSlowKluczy-1].elementy = 1;
                    slowaKlucze[iloscSlowKluczy-1].pow = malloc(sizeof(int));

                    y = iloscSlowKluczy;    
                }
                
                iloscSlowWWypowiedzi++;
                short * tymczasowy = realloc(slowaWWypowiedzi,sizeof(short) * iloscSlowWWypowiedzi);
                slowaWWypowiedzi = tymczasowy;
                slowaWWypowiedzi[iloscSlowWWypowiedzi-1] = y;
                
                licznik = 0;
                zerowanieSlowa
            }
            slowo.str[licznik] = buffor[i];
            licznik++;
        }

        if ( buffor[0] != '\n')
        {
            int iloscSlowOdpowiedzi = rand () % 10;
            int odpowiedz[iloscSlowOdpowiedzi];

            for (int i = 0; i < iloscSlowOdpowiedzi; i++)
            {
                odpowiedz[i] = (rand() % (iloscSlowWWypowiedzi-1));
            }

            printf("%d\n",iloscSlowKluczy);
        }
    }

    free(slowaWWypowiedzi);
    free(slowaKlucze);
}