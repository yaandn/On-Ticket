#ifndef RESERVA_H
#define RESERVA_H
#define TAM 10

#include <stdio.h>
#include <stdlib.h>
#include "cadastro.h"
#include "usuarios.h"

typedef struct reserva
{
    int id;
    int codigo;
    Ingressos *ingresso;
    
}TipoReserva;

typedef struct reservaUser{
    int indice;
    TipoReserva reservas[TAM];
}ReservasUser;

// typedef Reserva *PonteiroReserva;


// typedef struct FilaReserva
// {
//     PonteiroReserva ptr_primeiro;
//     PonteiroReserva ptr_fim;
// }FilaReserva;

// void IniciarFilaReserva(FilaReserva *fila);

// void CadastrarReserva(FilaReserva *fila, TipoUser usuario);

// //void RetiraReserva(FilaReserva *fila,  TipoUser usuario);

// void ImprimirFilaReservas(FilaReserva *fila);

ReservasUser* inicializaReserva(ReservasUser *reserva);

void obterReserva(ReservasUser *reserva,TipoUser usuario, ListaIngressos *ingressos, ListaShows *shows);
void imprimirReservas(ReservasUser reservas);

#endif