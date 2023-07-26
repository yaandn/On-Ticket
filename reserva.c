#include "reserva.h"
#include "cadastro.h"
#include "usuarios.h"
#include <stdlib.h>
#include <stdio.h>


// void IniciarFilaReserva(FilaReserva *fila)
// {
//     fila->ptr_primeiro = NULL;
//     fila->ptr_fim = NULL;
// };

// void CadastrarReserva(FilaReserva *fila, TipoUser usuario)
// {
//     PonteiroReserva novo = (PonteiroReserva) malloc(sizeof(Reserva));

//     novo->reserva.cod = 0;
//     novo->reserva.Id = usuario->usuario.Id;
//     novo->ptr_prox = NULL;

//     if(fila->ptr_primeiro == NULL)
//     {
//         novo->reserva.cod = 1;
//         fila->ptr_primeiro = novo;
//         fila->ptr_fim = novo;
//     } else
//     {
//         novo->reserva.cod = 1 + fila->ptr_fim->reserva.cod;
//         fila->ptr_fim->ptr_prox = novo;
//         fila->ptr_fim = novo;
//     }

// };

// void RetiraReserva(FilaReserva *fila, int cod)
// {
//     PonteiroReserva aux1 = fila->ptr_primeiro;
//     PonteiroReserva aux2 = NULL;

//     while (aux1 != NULL)
//     {
//         if (aux1->reserva.cod == cod) break;

//         aux2 = aux1;
//         aux1 = aux1->ptr_prox;
//     }

//     if (aux1 == fila->ptr_primeiro) 
//     {
//         fila->ptr_primeiro = aux1->ptr_prox;
//         if (fila->ptr_primeiro == NULL) fila->ptr_fim = NULL;
//     } else
//     {
//         aux2->ptr_prox = aux1->ptr_prox;
//     }
    
//     free(aux1);
// }

// void ImprimirFilaReservas(FilaReserva *fila)
// {
//     PonteiroReserva aux = fila->ptr_primeiro;

//     while( aux!=NULL )
//     {
//         printf("", aux->reserva.user);
//         aux = aux->ptr_prox;
//     }
// };

ReservasUser* inicializaReserva(ReservasUser *reserva) {
  reserva = (ReservasUser *) malloc(sizeof(ReservasUser));
  reserva ->indice = 0;
  return reserva;
}

void obterReserva(ReservasUser *reserva, TipoUser usuario,ListaIngressos *ingressos, ListaShows *shows) {
  TipoReserva novaReserva;

  if (reserva->indice >= 10) {
    printf("Número máximo de reservas atingido\n");
    printf("Pressione ENTER para retornar...\n");
    getchar();
    getchar();
    return;
  }

  PonteiroIngressos ingressoEscolhido = escolherIngresso(ingressos, shows);

  novaReserva.id = usuario->usuario.Id;
  novaReserva.ingresso = ingressoEscolhido;
  
  if(reserva->indice == 0) {
    novaReserva.codigo = 1;
    reserva->indice++;
  } else {
    novaReserva.codigo++;
    reserva->indice++;
  }

  reserva->reservas[reserva->indice] = novaReserva;
  printf("Reserva obtida com sucesso, aperte ENTER para ratornar\n");
  getchar();
  getchar();
  
  return;
}

void imprimirReservas(ReservasUser reservas) {
  int totalReservas = reservas.indice;
  int i;
  TipoReserva reservaAtual;
  printf("\nReservas Obtidas:\n");
  for(i=0; i< totalReservas; i++) {
    reservaAtual = reservas.reservas[i];
    printf("Código: %d\n", reservaAtual.codigo);
    printf("Artista: %s\n", reservaAtual.ingresso->show->artista);
    printf("Tipo do Ingresso: %s\n", reservaAtual.ingresso->tipo);
    printf("Preço do ingresso: R$ %.2f\n", reservaAtual.ingresso->preco);
    printf("Data 0%d/0%d/%d", reservaAtual.ingresso->show->dia.dia, reservaAtual.ingresso->show->dia.mes, reservaAtual.ingresso->show->dia.ano);
  }
}


