#include <stdio.h>
#include <stdlib.h>

struct ler
{
    int item_cod;
    char item_nome[25];
    float item_valorUN;
    int item_stock;
};

void ler()
{
    int ini;

    FILE *pARQLERBIN = fopen("produtosBi.bin", "rb");
    if (pARQLERBIN == NULL)
    {
        printf("Erro ao abrir o arquivo produtos.bin");
        exit(1);
    }

    fread(&ini, sizeof(int), 1, pARQLERBIN);

    int quantia[ini]; // Dimensionamento do array quantia com o valor lido de ini

    // Alocacao da struct ler zerando seus elementos
    struct ler *stock = (struct ler *)calloc(ini, sizeof(struct ler));
    if (stock == NULL)
    {
        printf("\nERRO NA ALOCACAO DA STRUCT LER!!!\n");
        exit(1);
    }

    // Leitura dos itens no stock guardados no arquivo binário
    for (int i = 0; i < ini; i++)
    {
        fread(&stock[i].item_cod, sizeof(int), 1, pARQLERBIN);
        fread(&stock[i].item_nome, sizeof(char), sizeof(stock[i].item_nome), pARQLERBIN);
        fread(&stock[i].item_valorUN, sizeof(float), 1, pARQLERBIN);
        fread(&stock[i].item_stock, sizeof(int), 1, pARQLERBIN);
        fread(&quantia[i], sizeof(int), 1, pARQLERBIN);
    }
    fclose(pARQLERBIN);

    FILE *quantia_vendida;
    quantia_vendida = fopen("vendida.txt", "w");

    for (int i = 0; i < ini; i++)
    {
        fprintf(quantia_vendida, "%d\n", quantia[i]);
    }
    fclose(quantia_vendida);

    // Abertura de arquivo para adicao dos itens
    FILE *pARQESCTXT;
    pARQESCTXT = fopen("stock.txt", "w");
    if (pARQESCTXT == NULL)
    {
        printf("Erro ao abrir arquivo stock.txt");
        exit(1);
    }

    // ADICAO DOS ITENS
    for (int i = 0; i < ini; i++)
    {
        fprintf(pARQESCTXT, "%d\n", stock[i].item_cod);
        fprintf(pARQESCTXT, "%s\n", stock[i].item_nome);
        fprintf(pARQESCTXT, "%.2f\n", stock[i].item_valorUN);
        fprintf(pARQESCTXT, "%d\n", stock[i].item_stock);
    }
    // Fechamento do arquivo de escrita
    fclose(pARQESCTXT);

    FILE *pini;
    pini = fopen("ini.txt", "w");
    fprintf(pini, "%d", ini);
    fclose(pini);

    free(stock);


    printf("Leitura dos produtos salvados anteriormente foi concluida.\n");
    system("pause");
}