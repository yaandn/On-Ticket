#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"
#include "menus.h"
#include "cadastro.h"


// inicializacao da lista de usuarios
void iniciaListaUsuarios(ListaUsers *lista)
{
    lista->ptr_primeiro = (TipoUser) malloc(sizeof(Users));
    lista->ptr_ultimo = lista->ptr_primeiro;
    lista->ptr_primeiro->ptr_prox = NULL;
}

//confere se a lista está vazia e retorna 1 em caso positivo, 0 caso negativo
int listaUsuariosVazia(ListaUsers *lista)
{
    return (lista->ptr_ultimo == lista->ptr_primeiro) ? 1 : 0;
}

//busca o numero do CPF e retorna os dados do usuario caso seja encontrado
TipoUser buscaCPF(char cpf[], ListaUsers *lista)
{
    TipoUser aux = lista->ptr_primeiro;
    while (aux != NULL)
    {
        if (strcmp(cpf, aux->usuario.cpf) == 0)
        {
            printf("CPF encontrado.\n");
            return aux;
        }
        aux = aux->ptr_prox;
    }

    return NULL;
};

//busca o numero do Id e retorna os dados do usuario caso seja encontrado
TipoUser buscaId(int Id, ListaUsers *lista)
{
    TipoUser aux = lista->ptr_primeiro;
    while (aux != NULL)
    {
        if ( Id == aux->usuario.Id)
        {
            printf("CPF encontrado.\n");
            return aux;
        }
        aux = aux->ptr_prox;
    }

    return NULL;
};

//compara se o cpf já está na lista de usuarios
// retorna valor 1 caso o usuario já possua conta e 0 caso contrario
int checaCPFCadastrado(char cpf[], ListaUsers *lista)
{
    TipoUser verifica = NULL;
    if(listaUsuariosVazia( lista )) return 0;

    verifica = buscaCPF(cpf, lista);
    if (verifica != NULL)
    {
        printf("Este CPF ja possui cadastro no sitema.\n");
        printf("Entre em contato com o suporte para recuperar sua conta\n");
        return 1;
    }
    return 0;
}

//cadastra novos usuarios ao sistema
//A função confere se o CPF já está cadastrado no sistema
//retorna 1 caso não seja possivel realizar o cadastro
//retorna 0 caso o cadastro tenha sido realizado com sucesso
int cadastraUsuarios( ListaUsers *lista )
{
    TipoUser novo = (TipoUser) malloc(sizeof(Users));
    if (novo == NULL) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }
    printf("\nDigite o numero do CPF\n");
    scanf("%11s%*c", novo->usuario.cpf);
    
    if(checaCPFCadastrado(novo->usuario.cpf, lista))
    {
        return 1;
    };

    printf("Digite uma senha\n");
    scanf("%11s%*c", novo->usuario.senha);
    printf("Digite o seu nome completo\n");
    scanf("%31[^\n]%*c", novo->usuario.nome);
    if(listaUsuariosVazia (lista)) novo->usuario.Id = 1;
    else
    {
        novo->usuario.Id = lista->ptr_ultimo->usuario.Id + 1;
    }
    novo->usuario.privilegio = 0;

    novo->ptr_prox = NULL;
    lista->ptr_ultimo->ptr_prox = novo;
    lista->ptr_ultimo = novo;
    return 0;
};


//função para fazer login no sistema
TipoUser fazerLogin(ListaUsers *lista1, ListaUsers *lista2)
{
    int tentativa = 0;
    Dados novo;
    printf("\nDigite o numero do CPF:\n");
    scanf("%s", novo.cpf);

    TipoUser usuarioEncontrado = buscaCPF(novo.cpf, lista2);
    if (usuarioEncontrado == NULL)
    {
        usuarioEncontrado = buscaCPF(novo.cpf, lista1);
    }

    while(tentativa<3)
    {
        if( usuarioEncontrado == NULL )
        {
            printf("CPF nao encontrado, faca cadastro para prosseguir.\n");
            break;
        }
        if (usuarioEncontrado)
        {
            printf("Digite uma senha:\n");
            scanf("%s", novo.senha);

            if (strcmp(novo.senha, usuarioEncontrado->usuario.senha) == 0)
            {
                printf("Login realizado com sucesso!\n");
                printf("Bem-vindo, %s!\n", usuarioEncontrado->usuario.nome);
                printf("\nAperte Enter para continuar...");
                getchar();  // Captura o Enter pressionado
                getchar();  // Pausa até o Enter ser pressionado novamente
                usuarioEncontrado->usuario.reservas.indice = 0;
                return usuarioEncontrado;
            }
            else
            {
                printf("Senha incorreta. Login falhou.\n");
                printf("Digite a senha novamente\n");
            }
        }
        tentativa++;
    }
    if(tentativa == 3)
    {
        printf("Errou a senha 3 vezes.\n");
        printf("\nAperte Enter para continuar...");
        getchar();  // Captura o Enter pressionado
        getchar();  // Pausa até o Enter ser pressionado novamente
    }
    return NULL;
}

// função para separar os dados de um usuário por um caracter especial '$'
void salvarDadosUsuarios(ListaUsers *lista, FILE *arquivo)
{
    TipoUser atual = lista->ptr_primeiro->ptr_prox;

    while (atual != NULL)
    {
        fprintf(arquivo, "%s$%s$%s$%d$%d\n",
         atual->usuario.cpf, atual->usuario.senha, atual->usuario.nome,
          atual->usuario.Id, atual->usuario.privilegio);
        atual = atual->ptr_prox;
    }
}


//função para liberar memoria ao fechar programa
void liberarListaUsuarios(ListaUsers *lista)
{
    TipoUser atual = lista->ptr_primeiro->ptr_prox;
    TipoUser proximo;

    while (atual != NULL)
    {
        proximo = atual->ptr_prox;
        free(atual);
        atual = proximo;
    }

    lista->ptr_primeiro = NULL;
    lista->ptr_ultimo = NULL;
}

//função de teste que imprime a lista de usuarios
void Imprime(ListaUsers *lista)
{
    TipoUser Aux;
    Aux = lista->ptr_primeiro->ptr_prox;
    while (Aux != NULL)
    {
        printf("\n%s\n", Aux->usuario.cpf);
        printf("%s\n", Aux->usuario.senha);
        printf("%s\n", Aux->usuario.nome);
        printf("%d\n", Aux->usuario.Id);
        Aux = Aux->ptr_prox;
    }
}

// função para carregar os dados dos usuários a partir do arquivo separados pelo caracter especial '$'
void carregarDadosUsuarios(ListaUsers *lista1, ListaUsers *lista2, FILE *arquivo)
{
    char line[100];

    while (fgets(line, sizeof(line), arquivo) != NULL)
    {
        char cpf[12];
        char senha[12];
        char nome[32];
        int id;
        int privilegio;

        if (sscanf(line, "%11[^$]$%11[^$]$%31[^$]$%d$%d",
         cpf, senha, nome, &id, &privilegio) == 5)
        {
            TipoUser novo = (TipoUser)malloc(sizeof(Users));
            if (novo == NULL)
            {
                printf("Erro de alocação de memória.\n");
                return;
            }

            strcpy(novo->usuario.cpf, cpf);
            strcpy(novo->usuario.senha, senha);
            strcpy(novo->usuario.nome, nome);
            novo->usuario.Id = id;
            novo->usuario.privilegio = privilegio;

            if (novo->usuario.privilegio == 0)
            {
                novo->ptr_prox = NULL;
                lista1->ptr_ultimo->ptr_prox = novo;
                lista1->ptr_ultimo = novo;
            }
            else
            {
                novo->ptr_prox = NULL;
                lista2->ptr_ultimo->ptr_prox = novo;
                lista2->ptr_ultimo = novo;
            }
        }
        else
        {
            printf("Erro ao ler linha do arquivo.\n");
        }
    }
}



void alteraNome( TipoUser *usuario )
{
    char nome[32];
    printf("\nDigite o novo nome do usuario\n");
    scanf(" %[^\n]%*c", nome);
    strcpy( (*usuario)->usuario.nome, nome);
};

void alteraSenha( TipoUser *usuario )
{
    char senha[12];
    printf("\nDigite a nova senha\n");
    scanf("%s", senha);
    strcpy( (*usuario)->usuario.senha, senha);
};