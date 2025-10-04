// Cod identificador: 048

#ifndef CROSSBOTS_PS_BLACKJACK_H
#define CROSSBOTS_PS_BLACKJACK_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO_BARALHO 52
#define PONTUACAO_MAXIMA 21
#define PARADA_DEALER 17
#define MULTIPLICADOR_BLACKJACK 1.5

typedef struct {
    char naipe[5];
    char rank[3];
    int valor;
} Carta;

typedef struct {
    Carta* cartas;
    int carta_atual;
    int tamanho;
} Baralho; // Baseado na estrutura de pilha

typedef struct {
    Carta* mao;
    int num_cards;
}Player;

// Tratamento de dados

/**
 * @brief Acola a memória para um novo baralho, o preenche com 52 cartas e o embaralha *
 * A função simula a preparação de um baralho antes de uma partida, como na realidade.;
 * Faz uso de fillBaralho(b) e shuffle(b), nessa ordem;
 * O baralho retornado já está pronto para uso imediato;
 * @return Um ponteiro para a estrutura Baralho recém-criada
 */
Baralho* createBaralho();

/**
 * @brief Libera um baralho e a sua coleção de cartas;
 * @param b O baralho a ser liberado da memória
 */
void destroyBaralho(Baralho* b);

/**
 * @brief Enche um baralho com um número determinado de cartas.
 * Função de suporte para createBaralho(b);
 * A função acessa um baralho já alocado e o preenche com cartas, fazendo uso da função pushCard.;
 * As cartas e naipes colocados tem uma ordem pré-definida, sendo necessário o embaralhamento por meio de shuffle(b);
 * @param b O baralho a ser preenchido
 */
void fillBaralho(Baralho* b);

/**
 * @brief Baseado no algoritmo Fisher-Yates, a função troca as cartas de um baralho aleatoriamente *
 * Função de suporte para createBaralho(b);
 * A função tem acesso direto ao vetor de cartas de b, já que é necessário acessar posições aleatórias;
 * @param b O baralho a ser reordenado aleatoriamente
 */
void shuffle(Baralho* b);

/**
 * @brief Coloca uma carta no topo do baralho, atualizando a posição da carta ao topo como em uma pilha *
 * @param c Carta a ser colocada
 * @param b Baralho alvo
 */
void pushCard(Carta c, Baralho *b);

/**
 * @brief Retorna a carta no topo do baralho, a removendo da pilha
 * @param b Baralho alvo
 * @return Carta retirada
 */
Carta getCard(Baralho *b);

/**
 * @brief Aloca a memória para um Player e a sua mão, dando 2 cartas para ele
 * Ao final da função, o player estará com 2 cartas na sua mão;
 * A função faz tratamento de erro para caso a alocação de memória ser má-sucedida;
 * @param b O baralho de onde as cartas devem ser retiradas;
 * @return Ponteiro para o Player recém alocado
 */
Player* createPlayer(Baralho *b);

/**
 * @brief Libera a memória alocada a um Player
 * @param p Estrutura de player a ser liberada
 */
void destroyPlayer(Player* p);

// Operações
/**
 * @brief Acessa a mão de um determinado player e retorna o valor em pontos dela
 * A função trata a carta Ás (A) de forma inteligente, contando-a como 1;
 * ao invés de 11 se a pontuação total for exceder 21.;
 * @param p Jogador alvo
 * @return Valor em pontos da mão do jogador
 */
int get_value(Player* p);

/**
 * @brief Retira a carta do topo do baralho e dá para o jogador
 * @param p Jogador alvo
 * @param b Baralho utilizado
 */
void buy(Player *p, Baralho *b);

// Interface
/**
 * @brief Função que trata da rodada do bot "Dealer" *
 * O dealer comprará cartas até ter uma mão de valor igual ou maior que 17 pontos *
 * @param p Ponteiro para o Dealer
 * @param b Baralho utilizado
 */
void dealer_play(Player *p, Baralho *b);

/**
 * @brief Imprime a mão de um determinado jogador
 * A função imprime todas as cartas e os seus respetivos naipes de uma mão, e ao final imprime o valor dessa mão
 * @param p Ponteiro para o jogador
 * @param nome_jogador Diferencia "Player" de "Dealer"
 */
void print_mao(Player *p, char* nome_jogador);

/**
 * @brief Trata da jogada do Player, que decide se quer comprar ou manter
 * Para ajudar na decisão, a função imprime a mão do jogador *
 * @param p Jogador
 * @param b Baralho utilizado na jogada
 * @return 1 se o jogador decidir comprar, ou 0 se decidir manter
 */
int player_play(Player *p, Baralho *b);

/**
 * @brief Finaliza a rodada, compara as mãos do jogador e do dealer, e declara o vencedor.
 *
 * Esta função atualiza o saldo do jogador com base no resultado da partida (vitória, derrota ou empate)
 * e imprime as mensagens de fim de jogo.
 * @param bet O valor que o jogador apostou na rodada.
 * @param p Ponteiro para o jogador.
 * @param d Ponteiro para o dealer.
 * @param s Ponteiro para a variável de saldo do jogador, que será atualizada.
 */
void game_over(float bet, Player *p, Player *d, float* s);

/**
 * @brief Deixa o jogado decidir se deseja continuar a jogar após o termino de uma rodada
 * @return 1 ou 0, dependendo da escolha
 */
int try_again();

#endif //CROSSBOTS_PS_BLACKJACK_H