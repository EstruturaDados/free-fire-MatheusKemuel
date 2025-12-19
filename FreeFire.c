//DESAFIO FREEFIRE NÍVEL MESTRE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// variaveis globais
#define MAX_CHAR 30
#define TAM_MOCHILA 10

// estrutura do item
typedef struct
{
    char nome[TAM_MOCHILA][MAX_CHAR];
    char tipo[TAM_MOCHILA][MAX_CHAR];
    int quantidade[TAM_MOCHILA];
    int prioridade[TAM_MOCHILA];
    int total;
    int ordenado;
} Item;

// inicializa a lista do item
void inicializarItem(Item *itens)
{
    itens->total = 0;
    itens->ordenado = 0;
}

// função de adicionar item na mochila
void adicionarItem(Item *itens, const char *nome, const char *tipo, int qtd, int prio)
{
    // verifica se a mochila está cheia
    if (itens->total == TAM_MOCHILA)
    {
        printf("Erro: Mochila cheia! Nao eh possivel inserir mais itens.\n");
        return;
    }

    // salva os dados do item na lista
    strcpy(itens->nome[itens->total], nome);
    strcpy(itens->tipo[itens->total], tipo);
    itens->quantidade[itens->total] = qtd;
    itens->prioridade[itens->total] = prio;
    itens->total++;
    itens->ordenado = 0;
    printf("Item \"%s\" inserido com sucesso!\n", nome);
}

// função para remover itens da mochila
void removerItem(Item *itens, const char *nome)
{

    int i, pos = -1;

    for (i = 0; i < itens->total; i++)
    {
        if (strcmp(itens->nome[i], nome) == 0)
        {
            pos = i;
            break;
        }
    }
    if (pos == -1)
    {
        printf("Erro: Item %s nao encontrado na mochila.\n", nome);
        return;
    }
    for (i = pos; i < itens->total - 1; i++)
    {
        strcpy(itens->nome[i], itens->nome[i + 1]);
        strcpy(itens->tipo[i], itens->tipo[i + 1]);
        itens->quantidade[i] = itens->quantidade[i + 1];
        itens->prioridade[i] = itens->prioridade[i + 1];
    }

    itens->total--;

    itens->ordenado = 0;
    printf("Item %s removido com sucesso.\n", nome);
}

// função para listar itens
void listarItens(const Item *itens)
{
    // verifica se a mochila está vazia
    if (itens->total == 0)
    {
        printf("A Mochila esta vazia.\n");
        return;
    }
    printf("--- ITENS NA MOCHILA (%d/10) ---\n", itens->total);
    printf("-------------------------------------------\n");
    printf("NOME       |TIPO     |QUANTIDADE     |PRIORIDADE\n");
    printf("-------------------------------------------\n");
    // o loop percorre todos os itens inseridos e os exibe no terminal
    for (int i = 0; i < itens->total; i++)
    {
        printf("%-10s |%-9s | %-8d| %d\n", itens->nome[i], itens->tipo[i], itens->quantidade[i], itens->prioridade[i]);
    }
}

// menu para a função de remoção de itens
void menuRemoverItem(Item *itens)
{
    char nome[MAX_CHAR];

    printf("--- Remover Item ---\n");
    printf("Digite o nome do item a ser removido:");
    fgets(nome, MAX_CHAR, stdin);
    nome[strcspn(nome, "\n")] = 0;

    // aqui chama a função de remoção para remover o item digitado
    removerItem(itens, nome);
}

// menu para a função de adicionar itens
void menuAdicionarItem(Item *itens)
{
    char nome[MAX_CHAR];
    char tipo[MAX_CHAR];
    int qtd;
    int prio;

    printf("Nome do Componente: ");
    fgets(nome, MAX_CHAR, stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("Tipo do Componente (Estrutural, Eletronico, Energia): ");
    fgets(tipo, MAX_CHAR, stdin);
    tipo[strcspn(tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &qtd);
    getchar();

    printf("Prioridade: ");
    scanf("%d", &prio);
    getchar();

    nome[strcspn(nome, "\n")] = 0;

    // aqui chama a função de adicionar item para adicionar o item digitado
    adicionarItem(itens, nome, tipo, qtd, prio);
}

// função para fazer a busca sequencial dos itens
/*
void buscarItem(const Item *itens, const char *nome)
{

    int encontrado = 0;

    // loop que percorre toda a lista de itens
    for (int i = 0; i < itens->total; i++)
    {
        // faz a comparação para saber se o item está na lista, se sim, exibe o item e suas caracteristicas
        if (strcmp(itens->nome[i], nome) == 0)
        {
            printf("\nItem Encontrado!\n");
            printf("Nome: %s\n", itens->nome[i]);
            printf("Tipo: %s\n", itens->tipo[i]);
            printf("Quantidade: %d\n", itens->quantidade[i]);
            encontrado = 1;
            break;
        }
    }

    // se não encontrar, exibe uma mensagem dizendo que não foi encontrado

    if (!encontrado)
    {
        printf("\nItem \"%s\" nao encontrado na mochila.\n", nome);
    }
}

// menu para digitar o item que deseja buscar
void menuBuscaItem(Item *itens)
{
    char nome[MAX_CHAR];

    printf("--- Buscar Item na Mochila ---\n");
    printf("Digite o nome do item que deseja buscar: \n");
    fgets(nome, MAX_CHAR, stdin);
    nome[strcspn(nome, "\n")] = 0;

    // aqui chama a função  de busca propriamente dita
    buscarItem(itens, nome);
}
    */

void ordenarPorNome(Item *itens)
{
    char tempNome[MAX_CHAR];
    char tempTipo[MAX_CHAR];
    int tempQtd;
    int tempPrio;

    for (int i = 0; i < itens->total - 1; i++)
    {
        for (int j = 0; j < itens->total - i - 1; j++)
        {
            // compara nomes
            if (strcmp(itens->nome[j], itens->nome[j + 1]) > 0)
            {
                // troca nome
                strcpy(tempNome, itens->nome[j]);
                strcpy(itens->nome[j], itens->nome[j + 1]);
                strcpy(itens->nome[j + 1], tempNome);

                // troca tipo
                strcpy(tempTipo, itens->tipo[j]);
                strcpy(itens->tipo[j], itens->tipo[j + 1]);
                strcpy(itens->tipo[j + 1], tempTipo);

                // troca quantidade
                tempQtd = itens->quantidade[j];
                itens->quantidade[j] = itens->quantidade[j + 1];
                itens->quantidade[j + 1] = tempQtd;

                // troca prioridade
                tempPrio = itens->prioridade[j];
                itens->prioridade[j] = itens->prioridade[j + 1];
                itens->prioridade[j + 1] = tempPrio;
            }
        }
    }
    itens->ordenado = 1;

    listarItens(itens);
}

void ordenarPorTipo(Item *itens)
{
    int i, j;
    char keyNome[MAX_CHAR], keyTipo[MAX_CHAR];
    int keyQtd, keyPrio;

    for (i = 1; i < itens->total; i++)
    {
        strcpy(keyNome, itens->nome[i]);
        strcpy(keyTipo, itens->tipo[i]);
        keyQtd = itens->quantidade[i];
        keyPrio = itens->prioridade[i];

        j = i - 1;

        while (j >= 0 && strcmp(itens->tipo[j], keyTipo) > 0)
        {
            strcpy(itens->nome[j + 1], itens->nome[j]);
            strcpy(itens->tipo[j + 1], itens->tipo[j]);
            itens->quantidade[j + 1] = itens->quantidade[j];
            itens->prioridade[j + 1] = itens->prioridade[j];
            j--;
        }

        strcpy(itens->nome[j + 1], keyNome);
        strcpy(itens->tipo[j + 1], keyTipo);
        itens->quantidade[j + 1] = keyQtd;
        itens->prioridade[j + 1] = keyPrio;
    }

    itens->ordenado = 1;
    listarItens(itens);
}

void ordenarPorPrioridade(Item *itens)
{
    int i, j, min;

    char tempNome[MAX_CHAR], tempTipo[MAX_CHAR];
    int tempQtd, tempPrio;

    for (i = 0; i < itens->total - 1; i++)
    {
        min = i;

        for (j = i + 1; j < itens->total; j++)
        {
            if (itens->prioridade[j] < itens->prioridade[min])
            {
                min = j;
            }
        }

        if (min != i)
        {
            strcpy(tempNome, itens->nome[i]);
            strcpy(itens->nome[i], itens->nome[min]);
            strcpy(itens->nome[min], tempNome);

            strcpy(tempTipo, itens->tipo[i]);
            strcpy(itens->tipo[i], itens->tipo[min]);
            strcpy(itens->tipo[min], tempTipo);

            tempQtd = itens->quantidade[i];
            itens->quantidade[i] = itens->quantidade[min];
            itens->quantidade[min] = tempQtd;

            tempPrio = itens->prioridade[i];
            itens->prioridade[i] = itens->prioridade[min];
            itens->prioridade[min] = tempPrio;
        }
    }

    itens->ordenado = 1;
    listarItens(itens);
}

void menuOrganizaItens(Item *itens)
{

    int op;

    do
    {
        printf("--- Estrategia de Organizacao ---\n");
        printf("Como deseja ordenar os componentes?\n");
        printf("1. Por Nome (Ordem Alfabetica)\n");
        printf("2. Por Tipo\n");
        printf("3. Por Prioridade de Montagem\n");
        printf("0. Cancelar\n");
        printf("Escolha o criterio: ");
        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1:
            ordenarPorNome(itens);
            break;
        case 2:
            ordenarPorTipo(itens);
            break;

        case 3:
            ordenarPorPrioridade(itens);
            break;
        case 0:
            printf("Voltando...\n1");
            break;
        default:
            break;
        }

    } while (op != 0);
}

void buscaBinariaPorNome(const Item *itens, const char *nome)
{
    if (!itens->ordenado)
    {
        printf("Erro: a mochila precisa estar ORDENADA para busca binaria.\n");
        return;
    }

    int inicio = 0;
    int fim = itens->total - 1;
    int meio;

    while (inicio <= fim)
    {
        meio = (inicio + fim) / 2;

        int cmp = strcmp(itens->nome[meio], nome);

        if (cmp == 0)
        {
            printf("\nItem encontrado (Busca Binaria)!\n");
            printf("Nome: %s\n", itens->nome[meio]);
            printf("Tipo: %s\n", itens->tipo[meio]);
            printf("Quantidade: %d\n", itens->quantidade[meio]);
            printf("Prioridade: %d\n", itens->prioridade[meio]);
            return;
        }
        else if (cmp < 0)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }

    printf("\nItem \"%s\" nao encontrado na mochila.\n", nome);
}

void menuBuscaBinaria(Item *itens)
{
    char nome[MAX_CHAR];

    printf("--- Busca Binaria por Nome ---\n");
    printf("Digite o nome do componente: ");
    fgets(nome, MAX_CHAR, stdin);
    nome[strcspn(nome, "\n")] = 0;

    buscaBinariaPorNome(itens, nome);
}
// função main
int main()
{
    Item itens;
    inicializarItem(&itens);

    int opcao;
    do
    {
        // loop do menu principal
        printf("================================\n");
        printf("PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("================================\n");
        printf("Itens na Mochila: %d/10\n\n", itens.total);
        printf("Status de Ordenacao por Nome: %s\n\n", itens.ordenado ? "ORDENADO" : "NAO ORDENADO"); // aqui mostra o status de ordenação, "NAO ORDENADO" para quando nao estiver ordenado e "ORDENADO" para quando estiver ordenado
        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");      // usar ou o "BUBBLESORT" ou o "INSERTIONSORT"
        printf("5. Busca Binaria por Componente-Chave(por nome)\n"); // aplicar a busca binaria depois de ordenar os itens
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("--------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        // switch case para cada opção
        switch (opcao)
        {
        case 1:
            menuAdicionarItem(&itens);
            break;
        case 2:
            menuRemoverItem(&itens);
            break;
        case 3:
            listarItens(&itens);
            break;
        case 4:
            menuOrganizaItens(&itens);
            // menuBuscaItem(&itens);
            break;
        case 5:
            menuBuscaBinaria(&itens);
            break;
        case 0:
            printf("Saindo...");
            break;
        default:
            break;
        }

    } while (opcao != 0);
    return 0;
}