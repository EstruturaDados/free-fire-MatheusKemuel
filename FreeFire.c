// DESAFIO FREEFIRE - NIVEL NOVATO



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//variaveis globais
#define MAX_CHAR 30
#define TAM_MOCHILA 10


//estrutura do item
typedef struct
{
    char nome[TAM_MOCHILA][MAX_CHAR];
    char tipo[TAM_MOCHILA][MAX_CHAR];
    int quantidade[TAM_MOCHILA];
    int total;
} Item;

//inicializa a lista do item
void inicializarItem(Item *itens)

{
    itens->total = 0;
}


//função de adicionar item na mochila
void adicionarItem(Item *itens, const char *nome, const char *tipo, int qtd)
{
    //verifica se a mochila está cheia
    if (itens->total == TAM_MOCHILA)
    {
        printf("Erro: Mochila cheia! Nao eh possivel inserir mais itens.\n");
        return;
    }

    //salva os dados do item na lista
    strcpy(itens->nome[itens->total], nome);
    strcpy(itens->tipo[itens->total], tipo);
    itens->quantidade[itens->total] = qtd;
    itens->total++;
    printf("Item \"%s\" inserido com sucesso!\n", nome);
}


//função para remover itens da mochila
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
    }

    itens->total--;
    printf("Item %s removido com sucesso.\n", nome);
}


//função para listar itens
void listarItens(const Item *itens)
{
    //verifica se a mochila está vazia
    if (itens->total == 0)
    {
        printf("A Mochila esta vazia.\n");
        return;
    }
    printf("--- ITENS NA MOCHILA (%d/10) ---\n", itens->total);
    printf("-------------------------------------------\n");
    printf("NOME       |TIPO     |QUANTIDADE\n");
    printf("-------------------------------------------\n");
    //o loop percorre todos os itens inseridos e os exibe no terminal
    for (int i = 0; i < itens->total; i++)
    {
        printf("%-10s |%-9s | %d\n", itens->nome[i], itens->tipo[i], itens->quantidade[i]);
    }
}

//menu para a função de remoção de itens
void menuRemoverItem(Item *itens)
{
    char nome[MAX_CHAR];

    printf("--- Remover Item ---\n");
    printf("Digite o nome do item a ser removido:");
    fgets(nome, MAX_CHAR, stdin);
    nome[strcspn(nome, "\n")] = 0;

    //aqui chama a função de remoção para remover o item digitado
    removerItem(itens, nome);
}

//menu para a função de adicionar itens
void menuAdicionarItem(Item *itens)
{
    char nome[MAX_CHAR];
    char tipo[MAX_CHAR];
    int qtd;

    printf("Nome do item: ");
    fgets(nome, MAX_CHAR, stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("Tipo do item (arma, mucicao, cura, etc): ");
    fgets(tipo, MAX_CHAR, stdin);
    tipo[strcspn(tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &qtd);

    nome[strcspn(nome, "\n")] = 0;

    //aqui chama a função de adicionar item para adicionar o item digitado
    adicionarItem(itens, nome, tipo, qtd);
}

//função main
int main()
{
    Item itens;
    inicializarItem(&itens);
    

    int opcao;
    do
    {
        //loop do menu principal
        printf("================================\n");
        printf("MOCHILA DE SOBREVIVENCIA\n");
        printf("================================\n");
        printf("Itens na Mochila: %d/10\n\n", itens.total);
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens da Mochila\n");
        printf("0. Sair\n");
        printf("--------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();


        //switch case para cada opção
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

        case 0:
            printf("Saindo...");
            break;
        default:
            break;
        }

    } while (opcao != 0);
    return 0;
}