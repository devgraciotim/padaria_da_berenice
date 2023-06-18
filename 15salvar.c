#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct salvar
{
    int item_cod;
    char item_nome[25];
    float item_valorUN;
    int item_stock;
};

void salvar()
{

    // ABERTURA E LEITURA DO ARQUIVO TXT ONDE ESTA GUARDADO A QUANTIDADE DE PRODUTOS CADASTRADOS
    int ini;
    FILE *pini;
    pini = fopen("ini.txt", "r");
    fscanf(pini, "%d", &ini);
    fclose(pini);
    // FECHAMENTO DO ARQUIVO TXT ONDE ESTA GUARDADO A QUANTIDADE DE PRODUTOS CADASTRADOS

    if (ini == 0)
    {
        nenhum_produto();
    }
    else
    {
        // ALOCACAO DA STRUCT SALVAR ZERANDO SEUS ELEMENTOS
        struct salvar *stock = (struct salvar *)calloc(ini, sizeof(struct salvar));
        if (stock == NULL)
        {
            printf("\nERRO NA ALOCACAO DA STRUCT SALVAR!!!\n");
            exit(1);
        }
        // FIM DA ALOCACAO DA STRUCT SALVAR

        // ABERTURA DE ARQUIVO PARA LEITURA
        FILE *pARQLERTXT;
        pARQLERTXT = fopen("stock.txt", "r");
        if (pARQLERTXT == NULL)
        {
            printf("Erro ao abrir arquivo stock.txt");
            exit(1);
        }
        // LEITURA DE DOS ITEMS NO STOCK GUARDADOS NO ARQUIVO TXT
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
        // FIM DA LEITURA DE DOS ITEMS NO STOCK GUARDADOS NO ARQUIVO TXT
        fclose(pARQLERTXT);

        int *quantia = (int *)calloc(ini, sizeof(int));
        FILE *quantia_vendida;
        quantia_vendida = fopen("vendida.txt", "r");

        for (int i = 0; i < ini; i++)
        {
            fscanf(quantia_vendida, "%d", &quantia[i]);
        }
        fclose(quantia_vendida);

        // ABERTURA DE ARQUIVO PARA SALVAR NO OUTRO TXT
        FILE *pARQESCBIN = fopen("produtosBi.bin", "wb");
        if (pARQESCBIN == NULL)
        {
            printf("Erro ao abrir o arquivo produtos.bin");
            exit(1);
        }

        fwrite(&ini, sizeof(int), 1, pARQESCBIN);

        for (int i = 0; i < ini; i++)
        {
            fwrite(&stock[i].item_cod, sizeof(int), 1, pARQESCBIN);
            fwrite(&stock[i].item_nome, sizeof(char), sizeof(stock[i].item_nome), pARQESCBIN);
            fwrite(&stock[i].item_valorUN, sizeof(float), 1, pARQESCBIN);
            fwrite(&stock[i].item_stock, sizeof(int), 1, pARQESCBIN);
            fwrite(&quantia[i], sizeof(int), 1, pARQESCBIN);
        }

        fclose(pARQESCBIN);

        free(stock);

        system("cls");
        printf("Os produtos estao agora salvos no arquivo binario produtos 'produtosBi.bin'\n");
        system("pause");
    }
}