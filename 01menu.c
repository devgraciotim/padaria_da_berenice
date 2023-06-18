#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "10produtos.c"
#include "20vendas.c"
#include "30sair.c"

#include "opcao_invalida.c"
#include "nenhum_produto.c"

void menu()
{
    int menu_codigo = 0;

    do
    {
        system("cls");
        printf("===============\n");
        printf("Menu Principal \n");
        printf("1. Produtos \n");
        printf("2. Vendas \n");
        printf("3. Sair \n");
        printf("===============\n");
        printf("Selecione uma opcao\n=>");
        scanf("%d", &menu_codigo);

        switch (menu_codigo)
        {
        case 1:
            produtos();
            break;
        case 2:
            vendas();
            break;
        case 3:
            sair();
            break;
        default:
            opcao_invalida();
            break;
        }

        menu_codigo = 0;

    } while (menu_codigo < 1 || menu_codigo > 3);
}