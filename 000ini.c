#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void iniciar()
{
    FILE *pini;
    pini = fopen("ini.txt", "w");
    fprintf(pini, "0");
    fclose(pini);

    FILE *arq;
    arq = fopen("stock.txt", "w");
    fclose(arq);

    FILE *vendidos;
    vendidos = fopen("vendida.txt", "w");
    for (int i = 0; i < 50; i++)
    {
        fprintf(vendidos, "0\n");
    }
    fclose(vendidos);
}