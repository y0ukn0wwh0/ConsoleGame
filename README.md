# Consola de jogo portátil

Este repositório contem o processo de desenvolvimento de uma consola portátil baseada em Arduino, assim como um jogo feito com a biblioteca Arduboy, o DUNG!.
A seguir estão os passos para a construção da mesma assim como a instalação do jogo.

## Montagem da consola

São usados os seguintes componentes:
- Arduino Nano
- 3 interruptores PTS636 de 2.5mm de altura
- Interruptor deslizante MSK12C01-07
- Bateria 601730 de 250mAh com dimensões 6*17*30mm
- Módulo de carregamento TP4056
- Resistência SMD de 5kΩ 
- Ecrã OLED i2c de 0.96 polegadas com o chip ssd1306
- Buzzer de 5V, 12mm de diâmetro
- 2 headers cada um com capacidade para 15 pinos (do Arduino Nano)
- O nosso PCB

Antes de se soldar os componentes ao PCB é necessário trocar a resistência do módulo de carregamento para a desejada de 5kΩ.

Tendo todos os componentes prontos é feita agora a soldagem dos mesmos ao PCB seguindo a [esquemática](/02_Desenho/circuito.png). Foi seguida a seguinte ordem de soldagem:
1. Módulo de carregamento
2. Header de baixo
3. Buzzer
4. Ecrã
5. Interruptor deslizante
6. Header de cima
7. 3 interruptores
8. Bateria

<img src="/04_Teste/solda_feita.png" height="300">

Assim a placa eletrónica pode agora ser inserida na caixa desenhada para a consola.

<img src="/04_Teste/caixa.jpg" height="300">

## Alternativa à soldagem na placa eletrónica
Caso seja desejado a montagem numa breadboard são apenas necessários o Arduino, os interruptores, o ecrã e o buzzer. Estes podem ser conectados aos pinos do Arduino como indicado na seguinte imagem.

<img src="/02_Desenho/breadboard.png" height="300">

## Jogo
Para a instalação do jogo são necessárias as bibliotecas disponíveis na pasta 03_Implementacao. Estas foram obtidas dos seguintes repositórios:
- [Arduboy2](https://github.com/MLXXXp/Arduboy2)
- [ArduboyTones](https://github.com/MLXXXp/ArduboyTones)
- [ArdBitmap](https://github.com/igvina/ArdBitmap)

As versões aqui disponíveis estão ligeiramente diferentes devido a algumas mudanças necessárias como a alteração dos pinos dos botões.

As bibliotecas são então postas na respetiva diretoria para que o Arduino IDE as importe (geralmente C:\Program Files (x86)\Arduino\libraries).
Após isto basta fazer upload para o Arduino do ficheiro [game.ino](/03_Implementacao/game/game.ino) com o [sprites.c](/03_Implementacao/game/sprites.c) na mesma pasta. Fica assim a instalação completa.
