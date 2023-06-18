#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct excluir
{
    int item_cod;
    char item_nome[25];
    float item_valorUN;
    int item_stock;
};

void excluir()
{

    // ABERTURA E LEITURA DO ARQUIVO TXT ONDE ESTA GUARDADO A QUANTIDADE DE PRODUTOS CADASTRADOS
    int ini;

    FILE *pini;
    pini = fopen("ini.txt", "r");
    fscanf(pini, "%d", &ini);
    fclose(pini);
    // FECHAMENTO DO ARQUIVO TXT ONDE ESTA GUARDADO A QUANTIDADE DE PRODUTOS CADASTRADOS

    int quantia[ini];
    int posicao = 0;

    // ALOCACAO DA STRUCT EXCLUIR ZERANDO SEUS ELEMENTOS
    struct excluir *stock = (struct excluir *)calloc(ini, sizeof(struct excluir));
    if (stock == NULL)
    {
        printf("\nERRO NA ALOCACAO DA STRUCT EXCLUIR!!!\n");
        exit(1);
    }
    // FIM DA ALOCACAO DA STRUCT EXCLUIR

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
    // FIM DA LEITURA DE DOS ITEMS NO STOCK GUARDADOS NO ARQUIVO TXT

    if (ini == 0)
    {
        nenhum_produto();
    }
    else
    {
        int codEX = 0;

        // LEITURA E VERIFICACAO DO CODIGO DO PRODUTO
        do
        {
            exibir();
            printf("Digite o codigo do produto a ser excluido\n=>");
            scanf("%d", &codEX);
            for (int i = 0; i < ini; i++)
            {
                if (codEX == stock[i].item_cod)
                {
                    system("cls");
                    printf("Item Encontrado \n");
                    posicao = i;
                    system("pause");
                    break;
                }
            }

            if (codEX != stock[posicao].item_cod)
            {
                printf("Produto com o Codigo %d nao encontrado!!\n", codEX);
                system("pause");
            }
        } while (codEX != stock[posicao].item_cod);
        // FIM LEITURA E VERIFICACAO DO CODIGO DO PRODUTO

        FILE *quantia_vendida;
        quantia_vendida = fopen("vendida.txt", "r");

        for (int a = 0; a < ini; a++)
        {
            fscanf(quantia_vendida, "%d", &quantia[a]);
        }

        fclose(quantia_vendida);

        quantia_vendida = fopen("vendida.txt", "w");

        for (int a = 0; a < ini; a++)
        {
            if (a != posicao)
            {
                fprintf(quantia_vendida, "%d\n", quantia[a]);
            }
        }

        fclose(quantia_vendida);

        int escolha = 0;
        do
        {
            system("cls");

            printf("Esse item sera excluido\n");
            printf("|Item(codigo) |Nome do Item             |Valor(UN) |Estoque |\n");
            printf("|%-13d|%-25s|%-10.2f|%-8d\n", stock[posicao].item_cod, stock[posicao].item_nome, stock[posicao].item_valorUN, stock[posicao].item_stock);

            printf("Deseja realmente excluir? \n1.Sim\n2.Nao\n=>");
            scanf("%d", &escolha);

            if (escolha < 1 || escolha > 2)
            {
                printf("Digite uma escolha valida\n");
                system("pause");
            }

        } while (escolha < 1 || escolha > 2);

        if (escolha == 1)
        {
            FILE *pARQESCTXT;
            pARQESCTXT = fopen("stock.txt", "w");
            if (pARQESCTXT == NULL)
            {
                printf("Erro ao abrir arquivo stock.txt");
                exit(1);
            }
            // ADICAO DOS ITENS NO TXT
            for (int i = 0; i < ini; i++)
            {
                if (i != posicao)
                {
                    fprintf(pARQESCTXT, "%d\n", stock[i].item_cod);
                    fprintf(pARQESCTXT, "%s\n", stock[i].item_nome);
                    fprintf(pARQESCTXT, "%.2f\n", stock[i].item_valorUN);
                    fprintf(pARQESCTXT, "%d\n", stock[i].item_stock);
                }
            }
            // FIM DA ADICAO DOS ITENS NO TXT
            fclose(pARQESCTXT);

            ini--;
            pini = fopen("ini.txt", "w");
            fprintf(pini, "%d", ini);
            fclose(pini);

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
            // FIM DA LEITURA DE DOS ITEMS NO STOCK GUARDADOS NO ARQUIVO TXT
            fclose(pARQLERTXT);

            system("cls");
            printf("Produto Excluido com Sucesso!! \n");
            for (int i = 0; i < ini; i++)
            {
                printf("Item %d   |%-13d|%-25s|%-10.2f|%-8d\n", i + 1, stock[i].item_cod, stock[i].item_nome, stock[i].item_valorUN, stock[i].item_stock);
            }
            system("pause");
        }
        else
        {
            printf("Nada foi Excluido \n");
            system("pause");
            produtos();
        }
    }
    free(stock);
}