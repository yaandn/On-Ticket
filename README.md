# On-Ticket

Este é um programa em C que oferece funcionalidades para o cadastro de eventos, reserva de ingressos e visualização das reservas. Ele agora foi aprimorado com a adição de um sistema de login para melhorar a segurança do acesso. O programa permite que os usuários façam login com suas credenciais antes de acessar as funcionalidades do sistema.

## Funcionalidades:

### Login:

Os usuários devem fazer login com o cpf cadastrado e senha válidos para acessar as funcionalidades do sistema.
As credenciais de login são armazenadas em um arquivo  e são verificadas para garantir a autenticidade do usuário.

### Cadastro de Eventos:

Usuários autenticados como administradores podem cadastrar novos eventos no sistema, fornecendo informações como nome do evento, data e local.
Os detalhes do evento são armazenados em uma estrutura de dados,uma lista de eventos.

### Listagem de Eventos:

Após o login, os usuários podem visualizar a lista de eventos cadastrados no sistema, incluindo informações relevantes, como nome, data e local.

### Reserva de Ingressos:

Usuários autenticados podem reservar ingressos para eventos específicos selecionados a partir da lista de eventos.
O programa solicita o código do show desejado e verifica a disponibilidade antes de efetuar a reserva.
A reserva é confirmada e adicionada ás credenciais do usuário.

### Visualização de Reservas:

Os usuários podem visualizar suas reservas atuais após o login, incluindo o nome do evento, artista e data.

### Instruções de Compilação e Execução:

Para compilar o programa, execute o seguinte comando no terminal:

gcc -o on-ticket cadastro.c reserva.c usuarios.c menus.c  main.c

Para executar o programa, utilize o seguinte comando:

./on-ticket
