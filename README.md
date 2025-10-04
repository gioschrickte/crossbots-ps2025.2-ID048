Desafio para o processo seletivo Crossbots. ID: 048

# Blackjack em C

Este projeto é uma implementação do clássico jogo de cartas Blackjack (ou Vinte e Um), desenvolvido em linguagem C. O objetivo é simular uma partida entre um jogador e um dealer (a "casa"), incluindo um sistema de apostas e a lógica de jogadas padrão do jogo.

## Funcionalidades

- **Baralho Completo:** Simulação de um baralho padrão de 52 cartas.
- **Embaralhamento:** O baralho é embaralhado aleatoriamente a cada nova rodada usando o algoritmo Fisher-Yates.
- **Lógica do Jogador:** O jogador pode escolher "comprar" mais cartas ou "manter" sua mão atual.
- **Lógica do Dealer:** O dealer segue a regra padrão de comprar cartas até atingir 17 pontos ou mais.
- **Sistema de Apostas:** O jogador inicia com um saldo e pode fazer apostas a cada rodada.
- **Cálculo de Pontos:** Contabilização automática dos pontos, tratando o Ás (A) como 11 ou 1, conforme a necessidade para evitar estourar 21 pontos.
- **Múltiplas Rodadas:** O jogador pode optar por jogar novamente após o fim de uma partida.

Para executar: gcc main.c blackjack.c -o blackjack

## Estrutura do Código

O projeto está organizado nos seguintes arquivos:

- **blackjack.h**: Define todas as estruturas de dados (Carta, Baralho, Player) e os protótipos das funções utilizadas no jogo.
- **blackjack.c**: Source. Contém a implementação de todas as funções declaradas em blackjack.h, abrangendo a lógica de manipulação do baralho, as ações dos jogadores e as regras do jogo.
- **main.c**: É responsável pelo loop principal do jogo, pela interação com o usuário (entradas e saídas no console) e pelas chamadas das funções em blackjack.c
