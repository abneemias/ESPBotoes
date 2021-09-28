# Ardubotões
## _Simplificador de Gincanas_

Ardubotões é um circuito com 3 jogos instalados.
## Modos de Jogo

- Modo 0: Perfeito pra perguntas e respostas. Trivia. Torta na Cara
- Modo 1: Desafio de reflexo
- Modo 2: Desafio de contagem

O Modo 0 é o padrão, precisa apertar nada para entrar nele.
O Modo 1 é acionado segurando o botão referente ao _led vermelho_ ao plugar o circuito na tomada.
O Modo 2 é acionado segurando o botão referente ao _led azul_ ao plugar o circuito na tomada.

O led piscará indicando o modo selecionado.

Resultados: O LED SEMPRE INDICARÁ O VENCEDOR.

## Modo 0 - Torta na Cara
Funcionanmento simples. os Leds começaram desligados quem apertar primeiro acionará a sua luz.
    
## Modo 1 - Desafio do Reflexo
Os Leds começarão ligados. Estes mostram que o jogo iniciou. Inicia uma contagem aleatória de até 15segundos.Eles desligarão a qualquer momento, quem pressionar primeiro após o desligamento, vence.
Queimar a largada: Caso alguem aperte o botão sem que os Leds desliguem perde automaticamente

## Modo 2 - Desafio da Contagem - Exige tela computador para monitorar
No computador mostrará até que número precisa contar mentalmente. Os primeiros 4 segundos aparecerão na tela de monitoramento.
Ganha quem apertar o botão mais próximo do valor estipulado inicialmente.   
    

*O PureData é necessario apenas se for trabalhar com canhões de luz DMX. Este está configurado para controlar via MIDI
o software FreeStyler X2. Usando o controlador [LoopMIDI] do Tobias Erichsen.

[LoopMIDI]: https://www.tobias-erichsen.de/software/loopmidi.html