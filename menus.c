#include <stdio.h>
#include <stdlib.h>
#include "cadastro.h"
#include "menus.h"
#include "usuarios.h"


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
  printf("\nSelecione uma opcao\n");
  printf("1: Login.\n");
  printf("2: Fazer cadastro.\n");
  printf("3: ENCERRAR o programa.\n");
}

int login( ListaUsers *users, ListaUsers *admins, TipoUser *usuario )
{
  system("clear");
  printLogin();
  int n;
  while (scanf("%d", &n) != 1) 
  {
    while (getchar() != '\n');
    printf("Entrada inválida. Digite um número válido: ");
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
      return 0;
  }
  return 0;
}


void printMenuUsuario()
{
  printf("\nSelecione uma opcao\n");
  printf("1: Consultar reservas.\n");
  printf("2: Realizar reserva.\n");
  printf("3: Minhas reservas.\n");
  printf("4: Alterar dados cadastrais\n");
  printf("5: Logoff.\n");
}

int MenuUsuario( TipoUser *usuario, ListaShows *shows, ListaIngressos *ingressos)
{
  system("clear");
  int n;
  printf("Logado como %s\n\n", (*usuario)->usuario.nome);
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
          break;

        case 3 :
          break;

        case 4 :
          MenuAlteraDados( usuario );
          break;

        case 5 :
          *usuario = NULL;
          break;

        default :
          printf("Opcao invalida, pressione ENTER para escolher novamente!\n");
          if(getchar() == '\n') {
            break;
          }
          
      }
    return 0;
  }

  
 
}

void printMenuAlteraDados()
{
  printf("\nSelecione uma opcao\n");
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
    printf("opcao invalida\n");
    return;
  }
}

void printMenuAdmin()
{
  printf("\nSelecione uma opcao\n");
  printf("1: Visualizar shows.\n");
  printf("2: Cadastrar shows.\n");
  printf("3: Disponibilizar ingressos.\n");
  printf("4: Deletar Contas\n");
  printf("5: Logoff.\n");
};

int MenuAdmin( TipoUser *usuario, ListaShows *shows, ListaIngressos *ingressos)
{
  system("clear");
  int n;
  printf("Logado como %s\n\n", (*usuario)->usuario.nome);
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
      adicionarIngresso( ingressos, shows);
      break;

    case 4 :
      break;

    case 5 :
      *usuario = NULL;
      break;

    default :
      printf("Opcao invalida, escolha novamente!\n");
      return MenuAdmin( usuario, shows, ingressos );
  }
  return 0;
}

void printMenuCadastraShow()
{
  printf("\nSelecione uma opcao\n");
  printf("1: Novo Show\n");
  printf("3: Retornar\n");
};

void MenuCadastraShow( TipoUser *usuario , ListaShows *shows, ListaIngressos *ingressos)
{
  system("clear");
  printMenuCadastraShow();
  imprimirShows( shows, ingressos );
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
    printf("opcao invalida\n");
    return;
  }
}