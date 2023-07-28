#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"
#include "menus.h"
#include "cadastro.h"
#include "reserva.h"




int main()
{
  FILE *arquivoUsuarios;
  ListaUsers users;
  ListaUsers admins;
  TipoUser usuario = NULL;
  ReservasUser reservas[10];
  

  iniciaListaUsuarios(&users);
  iniciaListaUsuarios(&admins);

  int i;
  for(i=0;i<10;i++)
    inicializaReserva(&(reservas[i]));
  

  ListaShows shows;
  ListaIngressos ingressos;
  iniciaListaShows(&shows);
  iniciaListaIngressos(&ingressos);


  arquivoUsuarios = fopen("usuarios.txt", "r+");
  if (arquivoUsuarios == NULL)
  {
    // Se o arquivo de usuários não existir, criar um novo arquivo vazio
    arquivoUsuarios = fopen("usuarios.txt", "w+");
    if (arquivoUsuarios == NULL)
    {
      printf("Erro ao criar o arquivo de usuários.\n");
      return 1;
    }
  }
  else
  {
    carregarDadosUsuarios(&users, &admins, arquivoUsuarios);
  }
  
  printf("\033[3;36m");
  //Corpo da função principal do programa
  while (1)
  {
    //pede login de um usuario
    if (usuario == NULL)
    {
      if (login(&users, &admins, &usuario))
        break;
    }
    //entra no programa como um usuario
    if (usuario != NULL && usuario->usuario.privilegio==0)
    {
      if (MenuUsuario(&usuario, &shows, &ingressos, reservas))
        break;
    }
    //entra no programa como um administrador
    if (usuario != NULL && usuario->usuario.privilegio==1)
    {
      if (MenuAdmin( &usuario, &shows, &ingressos, reservas) )
        break;
    }
  }

  liberarListasShows(&shows, &ingressos);

  // Posicionar o ponteiro do arquivo no início
  rewind(arquivoUsuarios);
  // Salvar as alterações no arquivo de usuários
  salvarDadosUsuarios(&admins, arquivoUsuarios);
  salvarDadosUsuarios(&users, arquivoUsuarios);
  fclose(arquivoUsuarios);

  liberarListaUsuarios(&users);

  return 0;
}