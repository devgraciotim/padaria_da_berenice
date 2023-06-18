#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sair()
{
    int sair_codigo = 0;

    do
    {
        system("cls");

        printf("===============\n");
        printf("Sair \n");
        printf("1. Sim \n");
        printf("2. Nao\n");
        printf("===============\n");
        printf("Deseja realmente sair?\n=>");
        scanf("%d", &sair_codigo);

        switch (sair_codigo)
        {
        case 1:
            exit(0);
            break;
        case 2:
            menu();
            break;
        default:
            opcao_invalida();
            break;
        }

    } while (sair_codigo < 1 || sair_codigo > 2);
}