#include "usuarios.h"
#include "menus.h"
#include "cadastro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void iniciaListaShows(ListaShows *lista)
{
    lista->ptr_primeiro = NULL;
    lista->ptr_ultimo = NULL;
}

void iniciaListaIngressos(ListaIngressos *lista)
{
    lista->ptr_primeiro = NULL;
    lista->ptr_ultimo = NULL;
}

void adicionarShow(ListaShows *lista, Show show)
{
    PonteiroShow novo = (PonteiroShow)malloc(sizeof(struct Show));
    if (novo == NULL)
    {
        printf("Erro de alocação de memória.\n");
        return;
    }

    novo->codShow = 0;
    strcpy(novo->artista, show.artista);
    novo->dia = show.dia;
    strcpy(novo->local, show.local);
    novo->ptr_prox = NULL;

    for (int i = 0; i < 10; i++)
    {
        novo->codigoIngresso[i] = 0;
    }

    if (lista->ptr_primeiro == NULL)
    {
        novo->codShow = 1;
        lista->ptr_primeiro = novo;
        lista->ptr_ultimo = novo;
    }
    else
    {
        novo->codShow = 1 + lista->ptr_ultimo->codShow;
        lista->ptr_ultimo->ptr_prox = novo;
        lista->ptr_ultimo = novo;
    }
}

void adicionarIngresso(ListaIngressos *lista, ListaShows *shows)
{
    PonteiroIngressos novo = (PonteiroIngressos)malloc(sizeof(struct Ingressos));
    if (novo == NULL)
    {
        printf("Erro de alocação de memória.\n");
        return;
    }

    PonteiroShow show = escolherShow(shows);
    
    novo->show = show;

    Ingressos ingresso = lerIngresso();

    novo->codIngresso = 0;
    strcpy(novo->tipo, ingresso.tipo);
    novo->preco = ingresso.preco;
    novo->ptr_prox = NULL;

    if (lista->ptr_primeiro == NULL)
    {
        novo->codIngresso = 1;
        lista->ptr_primeiro = novo;
        lista->ptr_ultimo = novo;
    }
    else
    {
        novo->codIngresso = lista->ptr_ultimo->codIngresso + 1;
        lista->ptr_ultimo->ptr_prox = novo;
        lista->ptr_ultimo = novo;
    }

    int i;
    if(show->codigoIngresso[10]!=0)
    {
        printf("Nao e possivel cadastrar mais ingressos!\n");
    } else
    {
        for(i=0; i<10; i++)
        {
            if(show->codigoIngresso[i]==0)
            {
                show->codigoIngresso[i] = novo->codIngresso;
                break;
            }
        }
    }
}

void imprimirShows(ListaShows *lista, ListaIngressos *listaingressos)
{
    PonteiroShow atual = lista->ptr_primeiro;

    if (atual == NULL)
    {
        printf("Não há shows cadastrados.\n");
        return;
    }

    while (atual != NULL)
    {
        printf("Codigo do Show: %d\n", atual->codShow);
        printf("Artista: %s\n", atual->artista);
        printf("Data: %d/%d/%d\n", atual->dia.dia, atual->dia.mes, atual->dia.ano);
        printf("Local: %s\n", atual->local);

        int ingressoEncontrado = 0;
        for (int i = 0; i < 10; i++)
        {
            if (atual->codigoIngresso[i] != 0)
            {
                ingressoEncontrado = 1;
                break;
            }
        }

        if (ingressoEncontrado)
        {
            printf("Ingressos:\n");
            imprimirIngressos(listaingressos, atual->codigoIngresso);
        }
        else
        {
            printf("Este show não possui ingressos cadastrados.\n");
        }

        printf("\n");
        atual = atual->ptr_prox;
    }
}

void imprimirIngressos(ListaIngressos *lista, int codigoIngresso[10])
{
    PonteiroIngressos ingresso_atual = lista->ptr_primeiro;

    if (ingresso_atual == NULL)
    {
        printf("Não há ingressos cadastrados.\n");
        return;
    }

    for (int i = 0; i < 10; i++)
    {
        if (codigoIngresso[i] == 0)
            break;

        while (ingresso_atual != NULL && ingresso_atual->codIngresso != codigoIngresso[i])
        {
            ingresso_atual = ingresso_atual->ptr_prox;
        }

        if (ingresso_atual != NULL)
        {
            printf("Tipo: %s, Preço: %.2lf, Codigo: %d\n",
               ingresso_atual->tipo, ingresso_atual->preco, ingresso_atual->codIngresso);
        }
    }
}


void liberarListasShows(ListaShows *lista, ListaIngressos *lista2)
{

    PonteiroIngressos atual2 = lista2->ptr_primeiro;
    PonteiroIngressos proximo2;
    while (atual2 != NULL)
    {
        proximo2 = atual2->ptr_prox;
        free(atual2);
        atual2 = proximo2;
    }

    lista2->ptr_primeiro = NULL;
    lista2->ptr_ultimo = NULL;

    PonteiroShow atual = lista->ptr_primeiro;
    PonteiroShow proximo;
    while (atual != NULL)
    {
        proximo = atual->ptr_prox;
        free(atual);
        atual = proximo;
    }

    lista->ptr_primeiro = NULL;
    lista->ptr_ultimo = NULL;
}

void lerData(Dia *data)
{
      int dia;
    int mes;
    int ano;

    printf("Digite o dia: ");
    scanf("%d", &dia);

    while (dia < 1 || dia > 31) {
        printf("\n[ERRO] Dia inválido, pressione ENTER para digitar um novo dia\n");
        getchar();
        if(getchar() == '\n') {
            printf("Digite um dia válido: ");
            scanf("%d", &dia); 
        }
        
    }
    data ->dia = dia;

    printf("Digite o mês: ");
    scanf("%d", &mes);

    while (mes < 1 || mes > 12) {
       printf("\n[ERRO] Mês inválido, pressione ENTER para digitar um novo mes\n");
        getchar();
        if(getchar() == '\n') {
            printf("Digite um mês válido: ");
            scanf("%d", &mes); 
        }
         
    }
    data ->mes = mes;

    printf("Digite o ano: ");
    scanf("%d", &ano);

     while (ano < 2023) {
        printf("\n[ERRO] Ano inválido, pressione ENTER para digitar um novo ano\n");
        getchar();
        if(getchar() == '\n') {
            printf("Digite um ano válido: ");
            scanf("%d", &ano); 
        }
        
    }
    data ->ano = ano;
}

Show lerShow()
{
    Show novo;

    printf("Digite o nome do artista: ");
    scanf(" %19[^\n]%*c", novo.artista);
    printf("Digite a data do show:\n");
    lerData(&(novo.dia));

    printf("Digite o local do show: ");
    scanf(" %31[^\n]%*c", novo.local);

    return novo;
}

Ingressos lerIngresso()
{
    Ingressos novo;

    printf("Digite o tipo de ingresso: ");
    scanf("%11s%*c", novo.tipo);

    printf("Digite o preço do ingresso: ");
    scanf("%lf%*c", &(novo.preco));

    novo.ptr_prox = NULL;

    return novo;
}

PonteiroShow escolherShow(ListaShows *lista)
{
    int opcao;

    PonteiroShow atual = lista->ptr_primeiro;

    // Exibe a lista de shows cadastrados
    printf("Lista de Shows:\n");
    while (atual != NULL)
    {
        printf("%d. %s - %d/%d/%d\n",
         atual->codShow, atual->artista, atual->dia.dia, atual->dia.mes, atual->dia.ano);
        atual = atual->ptr_prox;
    }

    // Solicita a escolha do show ao usuário
    printf("Escolha o número do show: ");

    while (scanf("%d", &opcao) != 1) 
    {
        while (getchar() != '\n');
        printf("Entrada inválida. Digite um número válido: ");
    }

    // Percorre a lista até o show escolhido
    atual = lista->ptr_primeiro;
    while (atual != NULL && opcao != atual->codShow)
    {
        atual = atual->ptr_prox;
    }

    if (atual == NULL)
    {
        printf("Opção inválida.\n");
        return NULL;
    }
    else
    {
        return atual;
    }
}
