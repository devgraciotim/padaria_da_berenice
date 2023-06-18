#include <stdio.h>
#include <stdlib.h>

struct relatorio
{
    int item_cod;
    char item_nome[25];
    float item_valorUN;
    int item_stock;
};

void relatorio()
{
    int ini;

    FILE *pini;
    pini = fopen("ini.txt", "r");
    fscanf(pini, "%d", &ini);
    fclose(pini);

    if (ini == 0)
    {
        nenhum_produto();
    }
    else
    {
        // ALOCACAO DA STRUCT EXIBIR ZERANDO SEUS ELEMENTOS
        struct relatorio *stock = (struct relatorio *)calloc(ini, sizeof(struct relatorio));
        if (stock == NULL)
        {
            printf("\nERRO NA ALOCACAO DA STRUCT EXIBIR EM RELATORIO!!!\n");
            exit(1);
        }
        // FIM DA ALOCACAO DA STRUCT RELATORIO

        // LEITURA DE DOS ITEMS NO STOCK GUARDADOS NO ARQUIVO TXT
        FILE *pARQLERTXT;
        pARQLERTXT = fopen("stock.txt", "r");
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
        fclose(pARQLERTXT);
        // FIM DA LEITURA DE DOS ITEMS NO STOCK GUARDADOS NO ARQUIVO TXT

        int *quantia = (int *)calloc(ini, sizeof(int));
        if (quantia == NULL)
        {
            printf("\nERRO NA ALOCACAO DA VARIAVEL QUANTIA EM RELATORIO!!!\n");
            exit(1);
        }

        FILE *quantia_vendida;
        quantia_vendida = fopen("vendida.txt", "r");

        for (int i = 0; i < ini; i++)
        {
            fscanf(quantia_vendida, "%d", &quantia[i]);
        }
        fclose(quantia_vendida);

        // EXIBICAO DE ESTOQUE
        system("cls");
        printf("===============================================================================\n");
        printf("                            Relatorio de Vendas                    \n");
        printf("===============================================================================\n");
        printf("         |Item(codigo) |Nome do Item             |Valor(UN) |Estoque |Vendidos\n");
        for (int i = 0; i < ini; i++)
        {
            printf("Item %d   |%-13d|%-25s|%-10.2f|%-8d|%-8d\n", i + 1, stock[i].item_cod, stock[i].item_nome, stock[i].item_valorUN, stock[i].item_stock, quantia[i]);
        }
        system("pause");
        // FIM DA EXIBICAO DE ESTOQUE

        vendas();
    }
}