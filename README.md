## Consola de jogo portátil

Este repositório contem o processo de desenvlvimento de uma consola portátil baseada em Arduino, assim como um jogo feito com a biblioteca Arduboy, o DUNG!.
A seguir estão os passos para a construção da mesma assim como a instalação do jogo.

### Consola

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

Tendo todos os componentes prontos é feita agora a soldagem dos mesmos ao PCB. Foi seguida a seguinte ordem de soldagem:
1. Módulo de carregamento
2. Header de baixo
3. Buzzer
4. Ecrã
5. Interruptor deslizante
6. Header de cima
7. 3 interruptores
8. Bateria

A placa fica então com o seguinte aspeto:


Assim a placa eletrónica pode agora ser inserida na caixa desenhada para a consola. Sendo este o resultado final:


### Jogo
Para a instalação do jogo são necessárias as bibliotecas disponíveis na pasta 03_Implementacao. Estas foram obtidas dos seguintes repositórios:
- [Arduboy2](https://github.com/MLXXXp/Arduboy2)
- [ArduboyTones](https://github.com/MLXXXp/ArduboyTones)
- [ArdBitmap](https://github.com/igvina/ArdBitmap)

As versões aqui disponíveis estão ligeiramente diferentes devido a algumas mudanças necessárias como a alteração dos pinos dos botões.

As bibliotecas são então postas na respetiva diretoria para que o Arduino IDE as importe (geralmente C:\Program Files (x86)\Arduino\libraries).
Após isto basta fazer upload do ficheiro game.ino com o ficheiro sprites.c (na pasta 03_Implementacao) para o Arduino.

Fica assim a instalação completa.
