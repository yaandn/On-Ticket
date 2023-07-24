#ifndef RESERVA_H
#define RESERVA_H

#include <stdio.h>
#include <stdlib.h>
#include "usuarios.h"
#include "cadastro.h"

typedef struct Identificador
{
    int id;
    int codigo;
    Ingressos *ingresso;
    Users *user;
}Identificador;

typedef struct Reserva
{
    Identificador reserva;
    PonteiroReserva ptr_prox;
}Reserva;

typedef Reserva *PonteiroReserva;


typedef struct FilaReserva
{
    PonteiroReserva ptr_primeiro;
    PonteiroReserva ptr_fim;
}FilaReserva;

void IniciarFilaReserva(FilaReserva *fila);

void CadastrarReserva(FilaReserva *fila, TipoUser usuario);

//void RetiraReserva(FilaReserva *fila,  TipoUser usuario);

void ImprimirFilaReservas(FilaReserva *fila);

#endif