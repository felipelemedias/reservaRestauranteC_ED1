#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Reserva {
  int numeroMesa;
  char nomeCliente[50];
  char cpf[12];
  char telefone[15]; // DDD + número
  int diaNascimento;
  int mesNascimento;
  int anoNascimento;
  char rua[50];
  char bairro[30];
  char cidade[30];
  char pedido[100];
  int reservarEstacionamento;
  char placaCarro[10];
  struct Reserva *proximo;
  struct Reserva *anterior;
} Reserva;

Reserva *criarReserva(int numeroMesa, const char nomeCliente[],
                      const char cpf[], const char telefone[],
                      int diaNascimento, int mesNascimento, int anoNascimento,
                      const char rua[], const char bairro[],
                      const char cidade[], const char pedido[],
                      int reservarEstacionamento, const char placaCarro[]) {
  Reserva *novaReserva = (Reserva *)malloc(sizeof(Reserva));
  novaReserva->numeroMesa = numeroMesa;
  strcpy(novaReserva->nomeCliente, nomeCliente);
  strcpy(novaReserva->cpf, cpf);
  strcpy(novaReserva->telefone, telefone);
  novaReserva->diaNascimento = diaNascimento;
  novaReserva->mesNascimento = mesNascimento;
  novaReserva->anoNascimento = anoNascimento;
  strcpy(novaReserva->rua, rua);
  strcpy(novaReserva->bairro, bairro);
  strcpy(novaReserva->cidade, cidade);
  strcpy(novaReserva->pedido, pedido);
  novaReserva->reservarEstacionamento = reservarEstacionamento;
  strcpy(novaReserva->placaCarro, placaCarro);
  novaReserva->proximo = NULL;
  novaReserva->anterior = NULL;
  return novaReserva;
}

void adicionarReserva(Reserva **listaReservas, Reserva *novaReserva) {
  if (*listaReservas == NULL) {
    *listaReservas = novaReserva;
  } else {
    novaReserva->proximo = *listaReservas;
    (*listaReservas)->anterior = novaReserva;
    *listaReservas = novaReserva;
  }
}

Reserva *encontrarReservaPorCliente(Reserva *listaReservas,
                                    const char nomeCliente[],
                                    const char cpf[]) {
  Reserva *atual = listaReservas;
  while (atual != NULL) {
    if (strcmp(atual->nomeCliente, nomeCliente) == 0 &&
        strcmp(atual->cpf, cpf) == 0) {
      return atual;
    }
    atual = atual->proximo;
  }
  return NULL; // Cliente não encontrado
}

// Função para exibir a lista de reservas
void exibirReservas(Reserva *listaReservas) {
  printf("\n--- Lista de Reservas ---\n");
  Reserva *atual = listaReservas;
  while (atual != NULL) {
    printf("Mesa %d - Cliente: %s - CPF: %s - Telefone: %s\n",
           atual->numeroMesa, atual->nomeCliente, atual->cpf, atual->telefone);
    printf("Data de Nascimento: %02d/%02d/%04d\n", atual->diaNascimento,
           atual->mesNascimento, atual->anoNascimento);
    printf("Endereco: Rua: %s - Bairro: %s - Cidade: %s\n", atual->rua,
           atual->bairro, atual->cidade);
    printf("Pedido: %s - Estacionamento: %s - Placa Carro: %s\n", atual->pedido,
           (atual->reservarEstacionamento == 1) ? "Sim" : "Não",
           atual->placaCarro);
    atual = atual->proximo;
  }
  printf("\n-------------------------\n");
}

Reserva *encontrarReservaPorMesa(Reserva *listaReservas, int numeroMesa) {
  Reserva *atual = listaReservas;
  while (atual != NULL) {
    if (atual->numeroMesa == numeroMesa) {
      return atual;
    }
    atual = atual->proximo;
  }
  return NULL; // Mesa não encontrada
}

void editarReservaMesa(Reserva *listaReservas) {
  char nomeCliente[50];
  char cpf[12];

  while (getchar() != '\n')
    ;

  printf("Nome do Cliente: ");
  fgets(nomeCliente, sizeof(nomeCliente), stdin);
  nomeCliente[strcspn(nomeCliente, "\n")] = '\0';

  printf("CPF do Cliente: ");
  fgets(cpf, sizeof(cpf), stdin);
  cpf[strcspn(cpf, "\n")] = '\0';

  // Encontra a reserva da mesa
  Reserva *reservaEditar =
      encontrarReservaPorCliente(listaReservas, nomeCliente, cpf);

  if (reservaEditar != NULL) {
    char telefone[15];
    int diaNascimento, mesNascimento, anoNascimento;
    char rua[50];
    char bairro[30];
    char cidade[30];
    int novaMesa;

    // Loop para verificar se a nova mesa está ocupada
    do {
      printf("Mesa desejada: ");
      scanf("%d", &novaMesa);

      Reserva *reservaExistenteMesa =
          encontrarReservaPorMesa(listaReservas, novaMesa);

      if (reservaExistenteMesa != NULL &&
          reservaExistenteMesa != reservaEditar) {
        printf("A mesa %d já está ocupada. Escolha outra mesa.\n", novaMesa);
      } else {
        break;
      }
    } while (1);

    printf("Telefone do Cliente (no formato DDD XXXXXXXXX): ");
    scanf("%s", telefone);
    printf("Data de Nascimento do Cliente (dia mes ano): ");
    scanf("%d %d %d", &diaNascimento, &mesNascimento, &anoNascimento);
    printf("Endereco do Cliente (rua bairro cidade): ");
    scanf("%s %s %s", rua, bairro, cidade);

    // Atualiza todos os campos da reserva
    reservaEditar->numeroMesa = novaMesa;
    strcpy(reservaEditar->telefone, telefone);
    reservaEditar->diaNascimento = diaNascimento;
    reservaEditar->mesNascimento = mesNascimento;
    reservaEditar->anoNascimento = anoNascimento;
    strcpy(reservaEditar->rua, rua);
    strcpy(reservaEditar->bairro, bairro);
    strcpy(reservaEditar->cidade, cidade);

    printf("Edicao da reserva para o cliente %s realizada com sucesso!\n",
           nomeCliente);
  } else {
    printf("Nao foi possivel encontrar a reserva para o cliente %s.\n",
           nomeCliente);
  }
}

void editarPedidoReserva(Reserva *listaReservas) {
  char nomeCliente[50];
  char cpf[12];

  while (getchar() != '\n')
    ;

  printf("Nome do Cliente: ");
  fgets(nomeCliente, sizeof(nomeCliente), stdin);
  nomeCliente[strcspn(nomeCliente, "\n")] = '\0';

  printf("CPF do Cliente: ");
  fgets(cpf, sizeof(cpf), stdin);
  cpf[strcspn(cpf, "\n")] = '\0';

  Reserva *reservaEditar =
      encontrarReservaPorCliente(listaReservas, nomeCliente, cpf);

  if (reservaEditar != NULL) {
    printf("Digite o novo pedido: ");
    while (getchar() != '\n')
      ; // Limpeza do buffer antes de ler a string
    fgets(reservaEditar->pedido, sizeof(reservaEditar->pedido), stdin);
    reservaEditar->pedido[strcspn(reservaEditar->pedido, "\n")] = '\0';

    printf("Edicao do pedido para o cliente %s realizada com sucesso!\n",
           nomeCliente);
  } else {
    printf("Nao foi possivel encontrar a reserva para o cliente %s.\n",
           nomeCliente);
  }
}

void editarReservaEstacionamento(Reserva *listaReservas) {
  char nomeCliente[50];
  char cpf[12];

  while (getchar() != '\n')
    ;

  printf("Nome do Cliente: ");
  fgets(nomeCliente, sizeof(nomeCliente), stdin);
  nomeCliente[strcspn(nomeCliente, "\n")] = '\0';

  printf("CPF do Cliente: ");
  fgets(cpf, sizeof(cpf), stdin);
  cpf[strcspn(cpf, "\n")] = '\0';

  Reserva *reservaEditar =
      encontrarReservaPorCliente(listaReservas, nomeCliente, cpf);

  if (reservaEditar != NULL) {
    printf("Reservar Estacionamento (1-Sim, 0-Nao): ");
    scanf("%d", &reservaEditar->reservarEstacionamento);

    // Se não estiver reservando o estacionamento, remove a placa do carro
    if (reservaEditar->reservarEstacionamento == 0) {
      reservaEditar->placaCarro[0] =
          '\0'; // Define a placa como uma string vazia
    } else if (reservaEditar->reservarEstacionamento == 1) {
      // Se estiver reservando o estacionamento, solicita a nova placa do carro
      printf("Digite a nova placa do carro: ");
      scanf("%s", reservaEditar->placaCarro);
    }

    printf("Edicao da reserva de estacionamento para o cliente %s realizada "
           "com sucesso!\n",
           nomeCliente);
  } else {
    printf("Nao foi possivel encontrar a reserva para o cliente %s.\n",
           nomeCliente);
  }
}

void excluirReserva(Reserva **listaReservas, const char nomeCliente[],
                    const char cpf[], int numeroMesa) {
  Reserva *reservaExcluir =
      encontrarReservaPorCliente(*listaReservas, nomeCliente, cpf);

  if (reservaExcluir != NULL && reservaExcluir->numeroMesa == numeroMesa) {
    if (reservaExcluir->anterior != NULL) {
      reservaExcluir->anterior->proximo = reservaExcluir->proximo;
    } else {
      *listaReservas = reservaExcluir->proximo;
    }

    if (reservaExcluir->proximo != NULL) {
      reservaExcluir->proximo->anterior = reservaExcluir->anterior;
    }

    free(reservaExcluir);

    printf("Reserva da mesa %d para o cliente %s excluida com sucesso!\n",
           numeroMesa, nomeCliente);
  } else {
    printf(
        "Nao foi possivel encontrar a reserva da mesa %d para o cliente %s.\n",
        numeroMesa, nomeCliente);
  }
}

void salvarReservas(Reserva *listaReservas) {
  FILE *arquivo = fopen("reservas.txt", "w");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo para escrita.\n");
    return;
  }

  Reserva *atual = listaReservas;
  while (atual != NULL) {
    fprintf(arquivo, "%d %s %s %s %d %d %d %s %s %s %s %d %s\n",
            atual->numeroMesa, atual->nomeCliente, atual->cpf, atual->telefone,
            atual->diaNascimento, atual->mesNascimento, atual->anoNascimento,
            atual->rua, atual->bairro, atual->cidade, atual->pedido,
            atual->reservarEstacionamento, atual->placaCarro);

    atual = atual->proximo;
  }

  fclose(arquivo);
}

Reserva *carregarReservas() {
  FILE *arquivo = fopen("reservas.txt", "r");

  if (arquivo == NULL) {
    printf("Arquivo de reservas nao encontrado. Criando novo arquivo.\n");
    return NULL;
  }

  Reserva *listaReservas = NULL;

  while (!feof(arquivo)) {
    int numeroMesa, diaNascimento, mesNascimento, anoNascimento,
        reservarEstacionamento;
    char nomeCliente[50], cpf[12], telefone[15], rua[50], bairro[30],
        cidade[30], pedido[100], placaCarro[10];

    if (fscanf(arquivo, "%d %s %s %s %d %d %d %s %s %s %s %d %s\n", &numeroMesa,
               nomeCliente, cpf, telefone, &diaNascimento, &mesNascimento,
               &anoNascimento, rua, bairro, cidade, pedido,
               &reservarEstacionamento, placaCarro) == 12) {
      Reserva *novaReserva =
          criarReserva(numeroMesa, nomeCliente, cpf, telefone, diaNascimento,
                       mesNascimento, anoNascimento, rua, bairro, cidade,
                       pedido, reservarEstacionamento, placaCarro);
      adicionarReserva(&listaReservas, novaReserva);
    }
  }

  fclose(arquivo);
  return listaReservas;
}

int main() {

  Reserva *listaReservas = carregarReservas();
  int numeroMesa;
  char nomeCliente[50];
  char cpf[12];
  char telefone[15];
  int diaNascimento, mesNascimento, anoNascimento;
  char rua[50];
  char bairro[30];
  char cidade[30];
  int reservarEstacionamento;
  char placaCarro[10];

  int opcao;
  do {
    printf("\n--- Menu ---\n");
    printf("1 - Fazer Reserva\n");
    printf("2 - Editar Reserva\n");
    printf("3 - Excluir Reserva\n");
    printf("4 - Listar Reservas\n");
    printf("5 - Sair do Programa\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    switch (opcao) {
    case 1: {
      int escolhaReserva;
      printf("\n--- Fazer Reserva ---\n");
      printf("1 - Reservar Mesa\n");
      printf("2 - Fazer Pre-agendamento do Pedido\n");
      printf("3 - Reservar Estacionamento\n");
      printf("Escolha uma opcao: ");
      scanf("%d", &escolhaReserva);
      switch (escolhaReserva) {
      case 1: {
        printf("\n--- Reservar Mesa ---\n");

        printf("Numero da Mesa: ");
        scanf("%d", &numeroMesa);

        Reserva *reservaExistenteMesa =
            encontrarReservaPorMesa(listaReservas, numeroMesa);

        if (reservaExistenteMesa != NULL) {
          printf("Mesa %d ja esta ocupada. Escolha outra mesa.\n", numeroMesa);
        } else {
          printf("Nome do Cliente: ");
          scanf("%s", nomeCliente);
          printf("CPF do Cliente: ");
          scanf("%s", cpf);
          printf("Telefone do Cliente (no formato DDD XXXXXXXXX): ");
          scanf("%s", telefone);
          printf("Data de Nascimento do Cliente (dia mes ano): ");
          scanf("%d %d %d", &diaNascimento, &mesNascimento, &anoNascimento);
          printf("Endereco do Cliente (rua bairro cidade): ");
          scanf("%s %s %s", rua, bairro, cidade);

          // Verifica se o cliente já tem uma mesa reservada
          Reserva *reservaExistente =
              encontrarReservaPorCliente(listaReservas, nomeCliente, cpf);

          // Adiciona ou atualiza a reserva conforme a escolha
          if (reservaExistente == NULL) {
            Reserva *novaReserva = criarReserva(
                numeroMesa, nomeCliente, cpf, telefone, diaNascimento,
                mesNascimento, anoNascimento, rua, bairro, cidade, "", 0, "");
            adicionarReserva(&listaReservas, novaReserva);
            printf("Mesa reservada com sucesso!\n");
          } else {
            printf("Cliente ja possui mesa reservada.\n");
          }
        }
        break;
      }
      case 2: {
        char nomeClienteVerificacao[50];
        char cpfVerificacao[12];

        printf("\n--- Fazer Pre-agendamento do Pedido ---\n");

        // Limpeza do buffer de entrada para evitar problemas com leitura de
        // strings
        while (getchar() != '\n')
          ;

        printf("Nome do Cliente: ");
        fgets(nomeClienteVerificacao, sizeof(nomeClienteVerificacao), stdin);
        nomeClienteVerificacao[strcspn(nomeClienteVerificacao, "\n")] =
            '\0'; // Remover o caractere de nova linha

        printf("CPF do Cliente: ");
        fgets(cpfVerificacao, sizeof(cpfVerificacao), stdin);
        cpfVerificacao[strcspn(cpfVerificacao, "\n")] = '\0';

        Reserva *reservaExistente = encontrarReservaPorCliente(
            listaReservas, nomeClienteVerificacao, cpfVerificacao);

        if (reservaExistente != NULL) {
          // Cliente tem mesa reservada, permita fazer o pré-agendamento do
          // pedido
          printf("Pedido: ");
          while (getchar() != '\n')
            ;
          fgets(reservaExistente->pedido, sizeof(reservaExistente->pedido),
                stdin);
          reservaExistente->pedido[strcspn(reservaExistente->pedido, "\n")] =
              '\0';

          printf("Pré-agendamento do pedido realizado com sucesso!\n");
          exibirReservas(listaReservas);
        } else {
          printf("Cliente nao tem mesa reservada. Realize a reserva antes de "
                 "fazer o pré-agendamento do pedido.\n");
        }

        break;
      }
      case 3: {
        char nomeClienteVerificacao[50];
        char cpfVerificacao[12];

        printf("\n--- Reservar Estacionamento ---\n");

        // Limpeza do buffer de entrada para evitar problemas com leitura de
        // strings
        while (getchar() != '\n')
          ;

        printf("Nome do Cliente: ");
        fgets(nomeClienteVerificacao, sizeof(nomeClienteVerificacao), stdin);
        nomeClienteVerificacao[strcspn(nomeClienteVerificacao, "\n")] =
            '\0'; // Remover o caractere de nova linha

        printf("CPF do Cliente: ");
        fgets(cpfVerificacao, sizeof(cpfVerificacao), stdin);
        cpfVerificacao[strcspn(cpfVerificacao, "\n")] = '\0';

        // Verifica se o cliente já tem uma mesa reservada
        Reserva *reservaExistente = encontrarReservaPorCliente(
            listaReservas, nomeClienteVerificacao, cpfVerificacao);

        if (reservaExistente != NULL) {
          printf("Reservar Estacionamento (1-Sim, 0-Nao): ");
          scanf("%d", &reservaExistente->reservarEstacionamento);
          if (reservaExistente->reservarEstacionamento == 1) {
            printf("Placa do Carro: ");
            scanf("%s", reservaExistente->placaCarro);
          }

          printf("Reserva de Estacionamento realizada com sucesso!\n");
          exibirReservas(listaReservas);
        } else {
          printf("Cliente nao tem mesa reservada. Realize a reserva antes de "
                 "reservar o estacionamento.\n");
        }

        break;
      }
      }
      break;
    }

    case 2: {
      int menuEditar;
      printf("\n--- Editar Reserva ---\n");
      printf("1 - Editar Reserva Mesa\n");
      printf("2 - Editar Pedido\n");
      printf("3 - Editar Reserva Estacionamento\n");
      printf("Escolha uma opcao: ");
      scanf("%d", &menuEditar);

      switch (menuEditar) {
      case 1: {
        printf("\n--- Editar Reservar ---\n");
        editarReservaMesa(listaReservas);
        break;
      }
      case 2: {
        printf("\n--- Editar Pedido ---\n");
        editarPedidoReserva(listaReservas);
        break;
      }
      case 3: {
        printf("\n--- Editar Reserva Estacionamento ---\n");
        editarReservaEstacionamento(listaReservas);
        break;
      }

      default:
        printf("Opcao invalida no menu de edicao.\n");
        break;
      }
      break;
    }

    case 3: {
      printf("\n--- Insira as informações pra deletar a Reserva da mesa ---\n");
      char nomeClienteExclusao[50];
      char cpfExclusao[12];
      int mesaExclusao;

      // Limpeza do buffer de entrada para evitar problemas com leitura de
      // strings
      while (getchar() != '\n')
        ;

      printf("Nome do Cliente: ");
      fgets(nomeClienteExclusao, sizeof(nomeClienteExclusao), stdin);
      nomeClienteExclusao[strcspn(nomeClienteExclusao, "\n")] =
          '\0'; // Remover o caractere de nova linha

      printf("CPF do Cliente: ");
      fgets(cpfExclusao, sizeof(cpfExclusao), stdin);
      cpfExclusao[strcspn(cpfExclusao, "\n")] = '\0';

      printf("Digite o numero da mesa a ser excluida: ");
      scanf("%d", &mesaExclusao);

      excluirReserva(&listaReservas, nomeClienteExclusao, cpfExclusao,
                     mesaExclusao);
      break;
    }
    case 4: {
      exibirReservas(listaReservas);
      break;
    }
    case 5: {
      printf("Saindo do Programa.\n");
      break;
    }
    default:
      printf("Opcao invalida.\n");
      break;
    }
  } while (opcao != 5);

  salvarReservas(listaReservas);
  Reserva *atual = listaReservas;
  while (atual != NULL) {
    Reserva *temp = atual;
    atual = atual->proximo;
    free(temp);
  }
  return 0;
}