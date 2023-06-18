#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

#include "11exibir.c"
#include "12cadastrar.c"
#include "13atualizar.c"
#include "14excluir.c"
#include "15salvar.c"
#include "16ler.c"

void produtos()
{
    int menu_produtos_codigo = 0;

    do
    {
        system("cls");

        printf("===============\n");
        printf("Produtos \n");
        printf("1. Exibir \n");
        printf("2. Cadastrar \n");
        printf("3. Atualizar \n");
        printf("4. Excluir \n");
        printf("5. Salvar \n");
        printf("6. Ler \n");
        printf("7. Voltar \n");
        printf("===============\n");
        printf("Selecione uma opcao\n=>");
        scanf("%d", &menu_produtos_codigo);

        switch (menu_produtos_codigo)
        {
        case 1:
            exibir();
            system("pause");
            break;
        case 2:
            cadastrar();
            break;
        case 3:
            atualizar();
            break;
        case 4:
            excluir();
            break;
        case 5:
            salvar();
            break;
        case 6:
            ler();
            break;
        case 7:
            menu();
        default:
            opcao_invalida();
            break;
        }
        menu_produtos_codigo = 0;

    } while (menu_produtos_codigo < 1 || menu_produtos_codigo > 7);
}