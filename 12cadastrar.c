#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct cadastro
{
    int item_cod_cad;
    char item_nome_cad[25];
    float item_valorUN_cad;
    int item_stock_cad;
};

struct stock
{
    int item_cod;
    char item_nome[25];
    float item_valorUN;
    int item_stock;
};

void cadastrar()
{
    int qnt_prod_desejados = 0;

    int ini;

    FILE *pini;
    pini = fopen("ini.txt", "r"); // abre pini
    fscanf(pini, "%d", &ini);
    fclose(pini); // fecha pini

    do
    {
        system("cls");
        printf("================================================\n");
        printf("                Cadastro de Produtos             \n");
        printf("================================================\n");

        printf("Numero de produtos a cadastrar\n=>");
        scanf("%d", &qnt_prod_desejados);

        if (qnt_prod_desejados < 1)
        {
            printf("\nQuantia invalida!!\n");
            printf("O valor deve ser igual ou maior que 1\n");
            system("pause");
            system("cls");
        }
    } while (qnt_prod_desejados < 1);

    // Aloca cad e cad_stock
    struct cadastro *cad = (struct cadastro *)calloc(qnt_prod_desejados, sizeof(struct cadastro));
    struct stock *cad_stock = (struct stock *)malloc((ini + qnt_prod_desejados) * sizeof(struct stock));
    if (cad_stock == NULL || cad == NULL)
    {
        printf("Erro na Alocacao de cad ou cad_stock \n");
        exit(1);
    }
    // Fim da alocacçao cad e cad_stock

    FILE *pARQLERTXT;
    pARQLERTXT = fopen("stock.txt", "r"); // Abre pARQLERTXT

    for (int i = 0; i < qnt_prod_desejados; i++)
    {
        for (int j = 0; j < ini; j++)
        {
            fscanf(pARQLERTXT, "%d", &cad_stock[j].item_cod);
            fgetc(pARQLERTXT);

            fgets(cad_stock[j].item_nome, sizeof(cad_stock[j].item_nome), pARQLERTXT);
            int pos = strcspn(cad_stock[j].item_nome, "\n");
            cad_stock[j].item_nome[pos] = '\0';

            fscanf(pARQLERTXT, "%f", &cad_stock[j].item_valorUN);
            fscanf(pARQLERTXT, "%d", &cad_stock[j].item_stock);
        }

        do
        {
            system("cls");
            printf("Digite o Codigo do Item\n=>");
            scanf("%d", &cad[i].item_cod_cad);
            getchar();
            if (cad[i].item_cod_cad < 1)
            {
                system("cls");
                printf("O valor deve ser maior ou igual a 1,\nnao pode ser composto por caracteres\ne tambem deve ser unico!!\n");
                system("pause");
                continue;
            }

            bool codigoRepetido = false;
            
            int a = 0;
            for (a = 0; a < ini; a++)
            {
                if (cad[i].item_cod_cad == cad_stock[a].item_cod)
                {
                    codigoRepetido = true;
                    break;
                }
            }

            if (codigoRepetido)
            {
                system("cls");
                printf("O codigo digitado ja existe \nDigite um codigo diferente \n");
                system("pause");
                continue;
            }
            break;

        } while (true);

        char espaco = ' ';
        do
        {
            system("cls");
            printf("Digite o Nome do Item\n=>"); // String com ate 25 caracteres, nao pode ser vazio, nem so espacos
            fgets(cad[i].item_nome_cad, 25, stdin);
            if (strlen(cad[i].item_nome_cad) > 25 || cad[i].item_nome_cad[0] == '\n' || cad[i].item_nome_cad[0] == espaco)
            {
                system("cls");
                printf("Maximo 25 caracteres!! \n");
                printf("Nome nao pode ser composto somente por espacos!! \n");
                printf("Nao pode ser vazio!! \n");
                system("pause");
            }
        } while (strlen(cad[i].item_nome_cad) > 25 || cad[i].item_nome_cad[0] == '\n' || cad[i].item_nome_cad[0] == espaco);

        do
        {
            system("cls");
            printf("Digite o Valor Unitario\n=>"); // valor decimal igual ou maior que 0
            scanf("%f", &cad[i].item_valorUN_cad);
            getchar();
            if (cad[i].item_valorUN_cad < 0)
            {
                system("cls");
                printf("Valor deve ser maior que 0 !! \n");
                system("pause");
            }
        } while (cad[i].item_valorUN_cad < 0);

        do
        {
            system("cls");
            printf("Digite a Quantidade do Item\n=>"); // valor inteiro igual ou maior que 0
            scanf("%d", &cad[i].item_stock_cad);
            getchar();
            if (cad[i].item_stock_cad < 0)
            {
                system("cls");
                printf("Valor deve ser igual ou maior que 0 \n");
                system("pause");
            }
        } while (cad[i].item_stock_cad < 0);

        printf("Produto Cadastrado!!\n");
        system("pause");
        system("cls");

        // Abertura de arquivo para adicao dos itens a cada iteracao do for
        FILE *arq;
        arq = fopen("stock.txt", "a");
        if (arq == NULL)
        {
            printf("Erro ao abrir arquivo stock.txt");
            exit(4);
        }

        // Adicao dos itens no txt
        fprintf(arq, "%d\n", cad[i].item_cod_cad);
        fprintf(arq, "%s", cad[i].item_nome_cad);
        fprintf(arq, "%.2f\n", cad[i].item_valorUN_cad);
        fprintf(arq, "%d\n", cad[i].item_stock_cad);
        // Adicao dos itens no txt

        fclose(arq);
        // Fechamento de arquivo para adicao dos itens a cada iteracao do for

        ini++;
    }

    system("pause");

    pini = fopen("ini.txt", "w");
    fprintf(pini, "%d", ini);
    fclose(pini);


    free(cad);
    free(cad_stock);
    fclose(pARQLERTXT);
}