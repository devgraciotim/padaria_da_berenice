#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct atualizar
{
    int item_cod;
    char item_nome[25];
    float item_valorUN;
    int item_stock;
};

void atualizar()
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
        int escolha = 0;
        int cod_att = 0;

        float valorUN = -1;
        int quantidade = -1;

        // ALOCACAO DA STRUCT ATUALIZAR ZERANDO SEUS ELEMENTOS
        struct atualizar *stock = (struct atualizar *)calloc(ini, sizeof(struct atualizar));
        if (stock == NULL)
        {
            printf("\nERRO NA ALOCACAO DA STRUCT EXCLUIR!!!\n");
            exit(1);
        }
        // FIM DA ALOCACAO DA STRUCT ATUALIZAR

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
        fclose(pARQLERTXT);

        bool produtoEncontrado = false;
        int prod = 0;
        do
        {
            system("cls");

            exibir();

            printf("======================================================================\n");
            printf("                        Atualizacao de Produtos                       \n");
            printf("======================================================================\n");
            printf("Digite o Codigo do Produto\n=>");
            scanf("%d", &cod_att);
            for (int i = 0; i < ini; i++)
            {
                if (cod_att == stock[i].item_cod)
                {
                    printf("Produto com o codigo %d encontrado...\n", cod_att);
                    produtoEncontrado = true;
                    prod = i;
                    break;
                }
            }

            if (!produtoEncontrado)
            {
                printf("Nao existe nenhum produto com o codigo %d...\n", cod_att);
                system("pause");
            }

        } while (!produtoEncontrado);

        system("cls");
        printf("|Item(codigo) |Nome do Item             |Valor(UN) |Estoque |\n");
        printf("|%-13d|%-25s|%-10.2f|%-8d\n", stock[prod].item_cod, stock[prod].item_nome, stock[prod].item_valorUN, stock[prod].item_stock);

        do
        {
            printf("================================\n");
            printf("1. Valor Unitario \n");
            printf("2. Quantidade \n");
            printf("3. Confirmar e Voltar \n");
            printf("================================\n");
            printf("Qual dado voce deseja alterar?\n=>");
            scanf("%d", &escolha);

            switch (escolha)
            {
            case 1:
                do
                {
                    printf("Digite o novo valor unitario\n=>");
                    scanf("%f", &valorUN);
                    if (valorUN < 0)
                    {
                        system("cls");
                        printf("Valor deve ser igual ou maior que zero!!\n");
                        system("pause");
                    }
                    else
                    {
                        system("cls");
                        printf("Valor guardado, volte para confirmar.\n");
                        system("pause");
                        system("cls");
                    }

                } while (valorUN < 0);
                break;

            case 2:
                do
                {
                    printf("Digite a nova quantidade\n=>");
                    scanf("%d", &quantidade);
                    if (quantidade < 0)
                    {
                        system("cls");
                        printf("Valor deve ser igual ou maior que zero!!\n");
                        system("pause");
                    }
                    else
                    {
                        system("cls");
                        printf("Valor guardado, volte para confirmar.\n");
                        system("pause");
                        system("cls");
                    }
                } while (quantidade < 0);
                break;

            case 3:
                system("cls");
                printf("ANTES\n");
                printf("|Item(codigo) |Nome do Item             |Valor(UN) |Estoque |\n");
                printf("|%-13d|%-25s|%-10.2f|%-8d\n", stock[prod].item_cod, stock[prod].item_nome, stock[prod].item_valorUN, stock[prod].item_stock);

                // NADA FOI ALTERADO
                if (valorUN == -1 && quantidade == -1)
                {
                    printf("Nada foi alterado\n");
                    system("pause");
                }

                // VALOR ALTERADO
                if (valorUN == -1 && quantidade != -1)
                {
                    printf("DEPOIS\n");
                    printf("|Item(codigo) |Nome do Item             |Valor(UN) |Estoque |\n");
                    printf("|%-13d|%-25s|%-10.2f|%-8d\n", stock[prod].item_cod, stock[prod].item_nome, stock[prod].item_valorUN, quantidade);
                    system("pause");

                    stock[prod].item_stock = quantidade;

                    // ABERTURA DE ARQUIVO PARA SALVAR NO OUTRO TXT
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
                        fprintf(pARQESCTXT, "%d\n", stock[i].item_cod);
                        fprintf(pARQESCTXT, "%s\n", stock[i].item_nome);
                        fprintf(pARQESCTXT, "%.2f\n", stock[i].item_valorUN);
                        fprintf(pARQESCTXT, "%d\n", stock[i].item_stock);
                    }
                    // FIM DA ADICAO DOS ITENS NO TXT
                    fclose(pARQESCTXT);
                }

                // QUANTIDADE ALTERADA
                if (quantidade == -1 && valorUN != -1)
                {
                    printf("DEPOIS\n");
                    printf("|Item(codigo) |Nome do Item             |Valor(UN) |Estoque |\n");
                    printf("|%-13d|%-25s|%-10.2f|%-8d\n", stock[prod].item_cod, stock[prod].item_nome, valorUN, stock[prod].item_stock);
                    system("pause");

                    stock[prod].item_valorUN = valorUN;

                    // ABERTURA DE ARQUIVO PARA SALVAR NO OUTRO TXT
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
                        fprintf(pARQESCTXT, "%d\n", stock[i].item_cod);
                        fprintf(pARQESCTXT, "%s\n", stock[i].item_nome);
                        fprintf(pARQESCTXT, "%.2f\n", stock[i].item_valorUN);
                        fprintf(pARQESCTXT, "%d\n", stock[i].item_stock);
                    }
                    // FIM DA ADICAO DOS ITENS NO TXT
                    fclose(pARQESCTXT);
                }

                if (quantidade != -1 && valorUN != -1)
                {
                    printf("DEPOIS\n");
                    printf("|Item(codigo) |Nome do Item             |Valor(UN) |Estoque |\n");
                    printf("|%-13d|%-25s|%-10.2f|%-8d\n", stock[prod].item_cod, stock[prod].item_nome, valorUN, quantidade);
                    system("pause");

                    stock[prod].item_valorUN = valorUN;
                    stock[prod].item_stock = quantidade;

                    // ABERTURA DE ARQUIVO PARA SALVAR NO OUTRO TXT
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
                        fprintf(pARQESCTXT, "%d\n", stock[i].item_cod);
                        fprintf(pARQESCTXT, "%s\n", stock[i].item_nome);
                        fprintf(pARQESCTXT, "%.2f\n", stock[i].item_valorUN);
                        fprintf(pARQESCTXT, "%d\n", stock[i].item_stock);
                    }
                    // FIM DA ADICAO DOS ITENS NO TXT
                    fclose(pARQESCTXT);
                }
                produtos();
                break;
            default:
                opcao_invalida();
                break;
            }

            escolha = 0;

        } while (escolha < 1 || escolha > 3);

        free(stock);
    }
}