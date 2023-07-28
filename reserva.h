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
    
}TipoReserva;

typedef struct reservaUser{
    int codIngresso;
    //Ingressos *ingresso;
    TipoReserva reservas[TAM];
}ReservasUser;


void inicializaReserva(ReservasUser *reserva);

void StartReserva( ReservasUser reserva[], PonteiroIngressos ingresso);

void obterReserva(ReservasUser reserva[], TipoUser usuario, ListaIngressos *ingressos, ListaShows *shows);

void imprimirReservas(ReservasUser reservas[], ListaIngressos *ingressos , TipoUser usuario);

#endif