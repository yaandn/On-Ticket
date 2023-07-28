#include <stdio.h>
#include <stdlib.h>
#include "cadastro.h"
#include "menus.h"
#include "usuarios.h"
#include "reserva.h"


#ifdef _WIN32
  #define CLEAR_COMMAND "cls"
#elif defined __linux__
  #define CLEAR_COMMAND "clear"
#elif defined __APPLE__
  #define CLEAR_COMMAND "clear"
#elif defined __unix__
  #define CLEAR_COMMAND "clear"
#else
  #define CLEAR_COMMAND ""
#endif


void clear()
{
  system(CLEAR_COMMAND);
}

void printLogin()
{
  printf("\n============================================\n");
  printf("\n               TELA DE INICIO             \n\n");
  printf("============================================\n");
  printf("\nSelecione uma opção:\n\n");
  printf("1- Fazer Login.\n");
  printf("2- Realizar cadastro.\n");
  printf("3- ENCERRAR o programa.\n");
}

int login( ListaUsers *users, ListaUsers *admins, TipoUser *usuario )
{
  system("clear");
  printLogin();
  int n;
  while (scanf("%d", &n) != 1) 
  {
    while (getchar() != '\n');
    printf("Entrada inválida.\n\n Digite um número válido: ");
  }
  switch ( n )
  {
    case 1 :
      *usuario = fazerLogin( users, admins );
      break;    
    case 2 :
      cadastraUsuarios( users );
      break;
    case 3 :
      return 1;
      break;
    default :
      printf("\nNúmero inválido.\n\nAperte ENTER para digitar novamente...");
      getchar();
      getchar();
      return 0;
  }
  return 0;
}


void printMenuUsuario()
{
  printf("\nSelecione uma opção:\n\n");
  printf("1- Consultar reservas.\n");
  printf("2- Realizar reserva.\n");
  printf("3- Minhas reservas.\n");
  printf("4- Alterar dados cadastrais\n");
  printf("5- Logoff.\n");
}

int MenuUsuario( TipoUser *usuario, ListaShows *shows, ListaIngressos *ingressos, ReservasUser reservas[])
{
  system("clear");
  int n;
  printf("\n============================================\n");
  printf("\n          Logado como %s!              \n\n",(*usuario)->usuario.nome);
  printf("============================================\n");
  //printf("Logado como %s\n\n", (*usuario)->usuario.nome);
  printMenuUsuario();


  while(scanf("%d", &n) != 4) {
      switch ( n )
      {
        case 1 :
        imprimirShows( shows, ingressos );
        printf("\nAperte Enter para retornar...");
        getchar();  // Captura o Enter pressionado
        getchar();  // Pausa até o Enter ser pressionado novamente

          
          
          break;

        case 2 :
          obterReserva(reservas,*usuario,ingressos, shows);
          break;

        case 3 :
          imprimirReservas(reservas, ingressos, *usuario);
          break;

        case 4 :
          MenuAlteraDados( usuario );
          break;

        case 5 :
          *usuario = NULL;
          break;

        default :
          printf("\nOpcao invalida, aperte ENTER para escolher novamente...");
          getchar();
          getchar();
          MenuUsuario( usuario, shows, ingressos, reservas);
        }
          
      
    return 0;
  }

  
 
}

void printMenuAlteraDados()
{
  printf("\n============================================\n");
  printf("\n             RESERVAS OBTIDAS              \n");
  printf("\n============================================\n");
  printf("\nSelecione uma opção\n\n");
  printf("1: Alterar o nome\n");
  printf("2: Mudar Senha\n");
  printf("3: Retornar\n");
};

void MenuAlteraDados( TipoUser *usuario )
{
  system("clear");
  printMenuAlteraDados();
  int n;
  while (scanf("%d", &n) != 1) 
  {
    while (getchar() != '\n');
    printf("Entrada inválida. Digite um número válido: ");
  }
  switch ( n )
  {
    case 1 :
    alteraNome( usuario );
    break;

    case 2 :
    alteraSenha( usuario );
    break;

    case 3 :
    return;

    default :
    printf("\nOpcao invalida, aperte ENTER para escolher novamente...");
    getchar();
    getchar();
    return;
  }
}

void printMenuAdmin()
{
  printf("\nMenu de Administração:\n\n");
  printf("1: Visualizar shows.\n");
  printf("2: Cadastrar shows.\n");
  printf("3: Disponibilizar ingressos.\n");
  printf("4: Logoff.\n");
};

int MenuAdmin( TipoUser *usuario, ListaShows *shows, ListaIngressos *ingressos, ReservasUser reserva[])
{
  system("clear");
  int n;
  printf("\n============================================\n");
  printf("\n     Logado como %s!              \n\n",(*usuario)->usuario.nome);
  printf("============================================\n\n");
  //printf("Logado como %s\n\n", (*usuario)->usuario.nome);
  printMenuAdmin();
  while (scanf("%d", &n) != 1) 
  {
    while (getchar() != '\n');
    printf("Entrada inválida. Digite um número válido: ");
  }
  switch ( n )
  {
    case 1 :
      imprimirShows( shows, ingressos );
      printf("\nAperte Enter para retornar...");
      getchar();  // Captura o Enter pressionado
      getchar();  // Pausa até o Enter ser pressionado novamente
      break;
      break;

    case 2 :
      MenuCadastraShow( usuario, shows, ingressos );
      break;

    case 3 :
      //adicionarIngresso( ingressos, shows);
      PonteiroIngressos newingresso = adicionarIngresso( ingressos, shows);
      StartReserva( reserva, newingresso );
      break;

    case 4 :
      *usuario = NULL;
      break;

    default :
      printf("\nOpcao invalida, aperte ENTER para escolher novamente...");
      getchar();
      getchar();
      return MenuAdmin( usuario, shows, ingressos, reserva );
  }
  return 0;
}

void printMenuCadastraShow()
{
  printf("\n============================================\n");
  printf("\n             CADASTRO DE SHOWS               \n");
  printf("\n============================================\n");
  printf("\nSelecione uma opcao\n");
  printf("\n1- Novo Show\n");
  printf("2- Retornar\n");
};

void MenuCadastraShow( TipoUser *usuario , ListaShows *shows, ListaIngressos *ingressos)
{
  system("clear");
  
  printMenuCadastraShow();
  //imprimirShows( shows, ingressos );
  int n;
  while (scanf("%d", &n) != 1) 
  {
    while (getchar() != '\n');
    printf("Entrada inválida. Digite um número válido: ");
  }
  switch ( n )
  {
    case 1 :
      Show show = lerShow();
      adicionarShow( shows, show);
    break;

    case 2 :
      return;

    default :
      printf("\nOpcao invalida, aperte ENTER para escolher novamente...");
      getchar();
      getchar();
    return;
  }
}