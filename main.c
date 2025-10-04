// Cod Identificador: 048
#include "blackjack.h"

#ifdef _WIN32
#include <windows.h>
#endif


int main(void) {
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    #endif

    srand(time(NULL));

    int continuar = 1;
    float saldo = 100.0;

    printf("Bem-vindo ao Blackjack!\n");
    printf("Seu saldo inicial é: R$%.2f\n", saldo);

    while (continuar) {
        if (saldo <= 0) {
            printf("Você não tem mais saldo para apostar. Fim de jogo!\n");
            break;
        }

        // Alocação das entidades
        Baralho* b = createBaralho();
        Player* p = createPlayer(b);
        Player* d = createPlayer(b);

        float bet = 0;

        while (bet <= 0 || bet > saldo) {
            printf("\nSaldo atual: R$%.2f. Faça sua aposta: ", saldo);
            char buffer_aposta[20];
            if (fgets(buffer_aposta, sizeof(buffer_aposta), stdin) != NULL) {
                bet = strtof(buffer_aposta, NULL); // strtof = String to float
            }
            if (bet <= 0) {
                printf("A aposta deve ser um valor positivo.\n");
            }
            if (bet > saldo) {
                printf("Aposta maior que o seu saldo!\n");
            }
        }

        printf("Carta revelada do Dealer: [%s%s]\n", d->mao[0].rank, d->mao[0].naipe);

        int jogador_continua = 1;
        while (jogador_continua) {
            print_mao(p, "Jogador");
            if (get_value(p) > PONTUACAO_MAXIMA){
                printf("Você estourou com %d pontos\n", get_value(p));
                break;
            }
            jogador_continua = player_play(p, b); // A função retorna 1 ou 0 dependendo se o player quiser manter ou comprar
        }

        if (get_value(p) <= PONTUACAO_MAXIMA) {
            // O dealer só joga se fizer sentido (o jogador não ter estourado)
            printf("\n--- Vez do Dealer ---\n");
            dealer_play(d, b);
        }

        // Funções de game over
        game_over(bet, p ,d, &saldo);

        destroyBaralho(b);
        destroyPlayer(p);
        destroyPlayer(d);

        continuar = try_again();
    }
    return 0;
}