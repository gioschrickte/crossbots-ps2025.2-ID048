// Cod identificador: 048
#include "blackjack.h"
#include <windows.h>
#include <stdio.h>

void shuffle(Baralho *b) {
    for (int i = b->carta_atual - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carta temp = b->cartas[i];
        b->cartas[i] = b->cartas[j];
        b->cartas[j] = temp;
    }
}

void pushCard(Carta c, Baralho *b) { // Função que funciona como um "push" de uma pilha
    if (b->carta_atual == b->tamanho) {
        fprintf(stderr, "error: stack overflow!\n");
        exit(EXIT_FAILURE);
    }
    b->cartas[b->carta_atual] = c;
    b->carta_atual++;
}

Carta getCard(Baralho *b) { // Função que funciona como um "pop" de uma pilha
    if (b->carta_atual == 0) {
        fprintf(stderr, "error: stack underflow!\n");
        exit(EXIT_FAILURE);
    }
    b->carta_atual--;
    return b->cartas[b->carta_atual];
}

void fillBaralho(Baralho *b) { // Pega um baralho vazio e preenche ele ordenadamente, note que o baralho deve estar vazio
    char* ranks[] = {"A","2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int valores[] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    char* naipes_simbolos[] = {"♥", "♦", "♣", "♠"};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            Carta c;
            strcpy(c.rank, ranks[j]);
            strcpy(c.naipe, naipes_simbolos[i]);
            c.valor = valores[j];
            pushCard(c, b);
        }
    }
}

Baralho* createBaralho() { // Aloca um baralho vazio na memória, preenche e embaralha, e no fim retorna. É como o procedimento que o dealer faz antes de cada partida
    Baralho* b = (Baralho*)malloc(sizeof(Baralho));
    if (b == NULL) {
        perror("Erro ao alocar memória para o baralho");
        exit(EXIT_FAILURE);
    }

    b->cartas = (Carta*)malloc(sizeof(Carta) * TAMANHO_BARALHO);
    if (b->cartas == NULL) {
        perror("Erro ao alocar memória para as cartas");
        free(b); // Libera a memória já alocada
        exit(EXIT_FAILURE);
    }

    b->tamanho = TAMANHO_BARALHO;
    b->carta_atual = 0;
    fillBaralho(b);
    shuffle(b);
    return b;
}

void destroyBaralho(Baralho* b) { // Libera o espaço alocado do baralho
    free(b->cartas);
    free(b);
}

// Funções do Jogador

Player* createPlayer(Baralho* b) { // Aloca e retorna um player
    Player* p = malloc(sizeof(Player));
    if (p == NULL) {
        perror("Erro ao alocar memória para o jogador");
        exit(EXIT_FAILURE);
    }
    p->mao = (Carta*)malloc(TAMANHO_BARALHO * sizeof(Carta));
    if (p->mao == NULL) {
        perror("Erro ao alocar memória para a mão do jogador");
        free(p);
        exit(EXIT_FAILURE);
    }

    p->num_cards = 0;
    // Dá as duas cartas iniciais
    buy(p,b);
    buy(p,b);
    return p;
}

void destroyPlayer(Player* p) {// Libera o espaço alocado de um player
    free(p->mao);
    free(p);
}

int get_value(Player* p) { // Retorna o valor em pontos da mão de um jogador
    int value = 0;
    int as = 0;
    for (int i = 0; i < p->num_cards; i++) {
        if (p->mao[i].valor == 11) {
            as++;
        }
        value += p->mao[i].valor;
    }
    while (as && value > PONTUACAO_MAXIMA) {
        value -= 10;
        as--;// Faz o ás somar apenas 1 ao valor da mão nos casos mais conveniente
    }
    return value;
}

void buy(Player *p, Baralho *b) { // A mão recebe a carta do topo do baralho
    p->mao[p->num_cards] = getCard(b);
    p->num_cards++;
}

void print_mao(Player *p, char* nome_jogador) { // Imprime uma mão
    printf("Cartas de %s: ", nome_jogador);
    printf("[");
    for (int i = 0; i < p->num_cards; i++) {
        printf("%s%s", p->mao[i].rank, p->mao[i].naipe);
        if (i < p->num_cards - 1) printf(", ");
    }
    printf("] (total = %d)\n", get_value(p));
}

// Lógica do Jogo

int player_play(Player *p, Baralho *b) { // Pergunta a ação do jogador e retorna 1 caso ele decide comprar ou 0 caso não
    char resposta[10];
    while (1) {
        printf("Você deseja 'comprar' ou 'manter'? ");
        fgets(resposta, sizeof(resposta), stdin);
        resposta[strcspn(resposta, "\n")] = '\0'; // Remove o \n

        if (strcmp(resposta, "comprar") == 0) {
            buy(p, b);
            return 1; // Continua jogando
        }
        if (strcmp(resposta, "manter") == 0) {
            return 0; // Para de jogar
        }
        printf("Resposta inválida. Por favor, digite 'comprar' ou 'manter'.\n");
    }
}

void dealer_play(Player *d, Baralho *b) { // Jogada do dealer
    print_mao(d, "Dealer");

    while (get_value(d) < 17) { // Loop indefinido em que o dealer compra até atingir os limites determinados pelo enunciado
        printf("Dealer compra uma carta...\n");
        buy(d, b);
        print_mao(d, "Dealer");
    }
}

void game_over(float bet, Player *p, Player *d, float* s) { // Função de final de jogo, usa o saldo passado por referência
    int v_p = get_value(p);
    int v_d = get_value(d);

    printf("\n--- Fim de Jogo ---\n");
    print_mao(p, "Jogador");
    print_mao(d, "Dealer");
    printf("-------------------\n");

    int player_ganhou = 0; // 0 = perdeu, 1 = ganhou, 2 = empatou
    float ganho = 0;

    if (v_p > PONTUACAO_MAXIMA) {
        printf("Jogador estourou! Dealer vence.\n");
        player_ganhou = 0;
    } else if (p->num_cards == 2 && v_p == PONTUACAO_MAXIMA) {
        printf("Blackjack Natural! Parabéns!\n");
        player_ganhou = 1;
        ganho = bet * MULTIPLICADOR_BLACKJACK;
    } else if (v_d > PONTUACAO_MAXIMA) {
        printf("Dealer estourou! Jogador vence.\n");
        player_ganhou = 1;
        ganho = bet;
    } else if (v_p > v_d) {
        printf("Jogador vence com %d pontos!\n", v_p);
        player_ganhou = 1;
        ganho = bet;
    } else if (v_d > v_p) {
        printf("Dealer vence com %d pontos!\n", v_d);
        player_ganhou = 0;
    } else { // v_p == v_d
        printf("Empate (Push)!\n");
        player_ganhou = 2;
    }

    if (player_ganhou == 1) { // Ganhou
        *s += ganho;
    } else if (player_ganhou == 0) { // Perdeu
        *s -= bet;
    }
    // Se for empate (2), o saldo não muda.

    printf("Saldo atual: R$%.2f\n", *s);
}

int try_again(){ // Controle de loop
    char buffer[10];
    printf("\nDeseja jogar novamente? (S/N): ");

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char resposta = tolower(buffer[0]);
        if (resposta == 's')
            return 1;
    }
    return 0;
}