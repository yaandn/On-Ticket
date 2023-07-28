#include "reserva.h"
#include "cadastro.h"
#include "usuarios.h"
#include <stdlib.h>
#include <stdio.h>

void inicializaReserva(ReservasUser *reserva)
{
    int i;
    for (i = 0; i < TAM; i++)
    {
        reserva->reservas[i].id = 0;
    }
    reserva->codIngresso = 0;
}



void StartReserva(ReservasUser reserva[], PonteiroIngressos ingresso)
{
    if (ingresso == NULL)
        return;

    int i;
    for (i = 0; i < TAM; i++)
    {
        if (reserva[i].codIngresso == 0)
        {
            reserva[i].codIngresso = ingresso->codIngresso;
            for (int j = 0; j < TAM; j++)
            {
                reserva[i].reservas[j].id = 0;
            }
            break;
        }
    }

    
}


void obterReserva(ReservasUser reserva[], TipoUser usuario, ListaIngressos *ingressos, ListaShows *shows)
{
    system("clear");
    printf("\n============================================\n");
    printf("\n             OBTENÇÃO DE RESERVAS              \n");
    printf("\n============================================\n");
    if (shows->ptr_primeiro == NULL)
    {
        printf("\nNão há shows cadastrados.\n");
        printf("\nAperte ENTER para retornar...\n");
        getchar();
        getchar();
        return;
    }

    PonteiroIngressos ingressoEscolhido = escolherIngresso(ingressos, shows);

    int i;
    for (i = 0; i < TAM; i++)
    {
        if (reserva[ingressoEscolhido->codIngresso].reservas[i].id == 0)
        {
            reserva[ingressoEscolhido->codIngresso].reservas[i].id = usuario->usuario.Id;
            int j;
            for (j = 0; j < 10; j++)
            {
                if (usuario->usuario.meusIngresso[j] == 0)
                {
                    usuario->usuario.meusIngresso[j] = ingressoEscolhido->codIngresso;
                    break;
                }
                if (j == 9)
                {
                    printf("\nAlcançou o limite de reservas!\n");
                }
            }
            break;
        }
    }

    printf("\n>> Reserva obtida com sucesso <<\n\nAperte ENTER para retornar...");
    getchar();
    getchar();
}



void imprimirReservas(ReservasUser reservas[], ListaIngressos *ingressos , TipoUser usuario)
{
    system("clear");
    printf("\n============================================\n");
    printf("\n             RESERVAS OBTIDAS              \n");
    printf("\n============================================\n");
    int i = 0;
    int j;

    if (usuario->usuario.meusIngresso[0] == 0)
    {
        printf("\nVocê ainda não realizou nenhuma reserva :(\n");
        printf("\nAperte ENTER para retornar...\n");
        getchar();
        getchar();
        return;
        //aaaa
    }

    PonteiroIngressos aux =  ingressos->ptr_primeiro;

    for(i=0;i<10;i++)
    {
        
        int codIngresso = usuario->usuario.meusIngresso[i];
        if(codIngresso == 0 ) break;

        while(aux!=NULL && aux->codIngresso!=reservas[i].codIngresso)
        {
            aux = aux->ptr_prox;
        }

        for (j = 0; j < TAM; j++)
        {
            
            if (reservas[codIngresso].reservas[j].id != 0)
                {
                    printf("\nCódigo: %d\n", reservas[codIngresso].reservas[j].id);
                    printf("Artista: %s\n", aux->show->artista);
                    printf("Local: %s\n", aux->show->local);
                    printf("Tipo do Ingresso: %s\n", aux->tipo);
                    printf("Preço do ingresso: R$ %.2f\n", aux->preco);
                    printf("Data: %02d/%02d/%d\n",
                           aux->show->dia.dia,
                           aux->show->dia.mes,
                           aux->show->dia.ano);
                    printf("------------------------------------------------------\n");
                }
        }
    }

    printf("\nPressione enter para voltar...\n");
    getchar();
    getchar();
}



//void imprimirReservas(ReservasUser reservas[], TipoUser usuario)
//{
//  int i;
//  for(i=0;i<10;i++)
//  if (usuario->usuario.meusIngresso[0] == 0)
//  {
//    printf("\nVocê ainda não realizou nenhuma reserva :(\n");
//    printf("\nAperte ENTER para retornar...\n");
//    getchar();
//    getchar();
//    return;
//  }
//
//
//  printf("\nReservas Obtidas:\n");
//  for (i = 1; i <= totalReservas; i++)
//  {
//
//    printf("\nCódigo: %d\n", reservas->reservas[i].codigo);
//    printf("Artista: %s\n", reservas->reservas[i].ingresso->show->artista);
//    printf("Local: %s\n", reservas->reservas[i].ingresso->show->local);
//    printf("Tipo do Ingresso: %s\n", reservas->reservas[i].ingresso->tipo);
//    printf("Preço do ingresso: R$ %.2f\n", reservas->reservas[i].ingresso->preco);
//    printf("Data 0%d/0%d/%d\n", reservas->reservas[i].ingresso->show->dia.dia, reservas->reservas[i].ingresso->show->dia.mes, reservas->reservas[i].ingresso->show->dia.ano);
//  }
//
//  printf("\nPressione enter para voltar...\n");
//  getchar();
//  getchar();
//  return;
//}
