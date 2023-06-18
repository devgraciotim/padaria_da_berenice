#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct exibir
{
    int item_cod;
    char item_nome[25];
    float item_valorUN;
    int item_stock;
};

void exibir()
{

    int ini;

    FILE *pini;
    pini = fopen("ini.txt", "r"); // abre pini
    fscanf(pini, "%d", &ini);
    fclose(pini); // fecha pini

    if (ini == 0)
    {
        nenhum_produto();
    }
    else
    {

        // ALOCACAO DA STRUCT EXIBIR ZERANDO SEUS ELEMENTOS
        struct exibir *stock = (struct exibir *)calloc(ini, sizeof(struct exibir));
        if (stock == NULL)
        {
            printf("\nERRO NA ALOCACAO DA STRUCT EXIBIR!!!\n");
            exit(1);
        }
        // FIM DA ALOCACAO DA STRUCT EXIBIR

        // LEITURA DE DOS ITEMS NO STOCK GUARDADOS NO ARQUIVO TXT
        FILE *pARQLERTXT;
        pARQLERTXT = fopen("stock.txt", "r"); // abre pARQLERTXT
        for (int i = 0; i < ini; i++)
        {
            fscanf(pARQLERTXT, "%d", &stock[i].item_cod);
            fgetc(pARQLERTXT);

            fgets(stock[i].item_nome, sizeof(stock[i].item_nome), pARQLERTXT);
            int pos = strcspn(stock[i].item_nome, "\n");
            stock[i].item_nome[pos] = '\0';

            fscanf(pARQLERTXT, "%f", &stock[i].item_valorUN);
            fscanf(pARQLERTXT, "%d", &stock[i].item_stock);
        }
        fclose(pARQLERTXT); // fecha pARQLERTXT
        // FIM DA LEITURA DE DOS ITEMS NO STOCK GUARDADOS NO ARQUIVO TXT

        // EXIBICAO DE ESTOQUE
        system("cls");
        printf("=====================================================================\n");
        printf("                    Exibicao de Produtos e Estoque                    \n");
        printf("=====================================================================\n");
        printf("         |Item(codigo) |Nome do Item             |Valor(UN) |Estoque |\n");
        for (int i = 0; i < ini; i++)
        {
            printf("Item %d   |%-13d|%-25s|%-10.2f|%-8d\n", i + 1, stock[i].item_cod, stock[i].item_nome, stock[i].item_valorUN, stock[i].item_stock);
        }
        // FIM DA EXIBICAO DE ESTOQUE

        // FREE
        free(stock);
        // FREE
    }
}