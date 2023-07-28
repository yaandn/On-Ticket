#include "usuarios.h"
#include "menus.h"
#include "cadastro.h"
#include "reserva.h"
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

    printf("\n\n>>> Show cadastrado com sucesso <<<\n\nAperte ENTER para retornar...");
    getchar();
    
}

PonteiroIngressos adicionarIngresso(ListaIngressos *lista, ListaShows *shows)
{
  system("clear");
  printf("\n================================================\n");
  printf("\n             CADASTRO DE INGRESSOS              \n");
  printf("\n================================================\n");

  if(shows->ptr_primeiro == NULL) {
    printf("\nNão há Shows cadastrados.\n\nAperte enter para retornar...");
    getchar();
    getchar();
    return NULL;
  }
    PonteiroIngressos novo = (PonteiroIngressos)malloc(sizeof(struct Ingressos));
    if (novo == NULL)
    {
        printf("Erro de alocação de memória.\n");
        return NULL;
    }

    PonteiroShow show = escolherShow(shows);
    
    novo->show = show;

    if(show == NULL) {
      printf("\nShow não encontrado, aperte ENTER para escolher novamente...");
      getchar();
      getchar();
    }

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
        printf("Não é possivel cadastrar mais ingressos!\n");
        return NULL;
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

    printf("\n\n>>> Ingresso cadastrado com sucesso <<<\n\nAperte ENTER para retornar...");
    getchar();
    
    return lista->ptr_ultimo;
    
}

void imprimirShows(ListaShows *lista, ListaIngressos *listaingressos)
{
  system("clear");
  printf("\n============================================\n");
  printf("\n             TELA DE SHOWS             \n\n");
  printf("============================================\n\n");
    PonteiroShow atual = lista->ptr_primeiro;

    if (atual == NULL)
    {
        printf("\nNão há shows cadastrados.\n");
        return;
    }

    while (atual != NULL)
    {
        printf("Código do Show: %d\n", atual->codShow);
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
            printf("--------------------------------------------\n");
        }
        else
        {
            printf("Este show não possui ingressos cadastrados.\n");
            printf("--------------------------------------------\n");
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

    printf("\nDigite o nome do artista: ");
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

    printf("\nDigite o tipo de ingresso: ");
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
    printf("\nLista de Shows:\n\n");
    while (atual != NULL)
    {
        printf("%d. %s - 0%d/0%d/0%d\n",
         atual->codShow, atual->artista, atual->dia.dia, atual->dia.mes, atual->dia.ano);
        atual = atual->ptr_prox;
    }

    // Solicita a escolha do show ao usuário
    printf("\nEscolha o número do show: ");

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
      
        return NULL;
    }
    else
    {
        return atual;
    }
}

PonteiroIngressos escolherIngresso(ListaIngressos *Ingressos, ListaShows *Shows) {
  PonteiroShow showEscolhido = escolherShow(Shows);
  int codigoEscolhido;
  printf("-------------------------------------------------\n");
  printf("\nLista de ingressos disponíveis:\n\n");

  imprimirIngressos(Ingressos, showEscolhido->codigoIngresso);
  
  printf("\nSelecione o código do tipo desejado:");
  scanf("%d", &codigoEscolhido);

  //percorrer a lista de ingressos para encontar o ingresso escolhido pelo usuario e o retornar
  PonteiroIngressos atual = Ingressos->ptr_primeiro;

  while (atual != NULL) {
    if(atual->codIngresso == codigoEscolhido) {
      return atual;
    }

    atual = atual->ptr_prox;
  }
}
