#include "reserva.h"
#include "cadastro.h"


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
