#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "21vender.c"
#include "22relatorio.c"

void vendas()
{
    int menu_vendas_codigo = 0;

    do
    {
        system("cls");

        printf("===============\n");
        printf("Vendas \n");
        printf("1. Realizar Vendas \n");
        printf("2. Relatorio de Vendas \n");
        printf("3. Voltar \n");
        printf("===============\n");
        printf("Selecione uma opcao\n=>");
        scanf("%d", &menu_vendas_codigo);

        switch (menu_vendas_codigo)
        {
        case 1:
            realizar_vendas();
            break;
        case 2:
            relatorio();
            break;
        case 3:
            menu();
            break;
        default:
            opcao_invalida();
            break;
        }

        menu_vendas_codigo = 0;

    } while (menu_vendas_codigo < 1 || menu_vendas_codigo > 3);
}