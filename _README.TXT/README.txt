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

Tendo todos os componentes prontos é feita agora a soldagem dos mesmos ao PCB seguindo a esquemática do ficheiro 'circuito.png' da pasta 02_Desenho. Foi seguida a seguinte ordem de soldagem:
1. Módulo de carregamento
2. Header de baixo
3. Buzzer
4. Ecrã
5. Interruptor deslizante
6. Header de cima
7. 3 interruptores
8. Bateria

Assim a placa eletrónica pode agora ser inserida na caixa desenhada para a consola.

## Alternativa à soldagem na placa eletrónica
Caso seja desejado a montagem numa breadboard são apenas necessários o Arduino, os interruptores, o ecrã e o buzzer. Estes podem ser conectados aos pinos do Arduino como indicado no ficheiro 'breadboard.png' da pasta 02_Desenho.

## Instalação do jogo
Para a instalação do jogo são necessárias as bibliotecas disponíveis na pasta 03_Implementacao. Estas foram obtidas dos seguintes repositórios:
- https://github.com/MLXXXp/Arduboy2
- https://github.com/MLXXXp/ArduboyTones
- https://github.com/igvina/ArdBitmap
As versões aqui disponíveis estão ligeiramente diferentes devido a algumas mudanças necessárias como a alteração dos pinos dos botões.

As bibliotecas são então postas na respetiva diretoria para que o Arduino IDE as importe (geralmente C:\Program Files (x86)\Arduino\libraries).
Após isto basta fazer upload do ficheiro game.ino com o ficheiro sprites.c (03_Implementacao\game) para o Arduino. Fica assim a instalação completa.

### Mecânicas
O jogo tem várias rondas compostas por níveis. O número de níveis em cada ronda vai aumentando ao longo que o jogador progride. Sendo assim o objetivo é completar o maior número de níveis possível.

Em cada nível os inimigos lançam projéteis em direção ao jogador e este tem de refleti-las carregando no botão correspondente no ritmo certo.
Para além dos inimigos irem ficando mais fortes à medida que o jogador avança, no nível final de cada ronda aparece um inimigo mais forte que os outros, dificultando a progressão do jogador.

No início de uma tentativa são oferecidas ao jogador 3 opções de personagens que têm diferentes caracteristícas:
|        | Guerreiro | Arqueiro  | Mago      |
| ------ | --------- | --------- | --------- |
| Vida   | 6         | 4         | 2         |
| Ataque | 2         | 3         | 4         |

Que também têm diferentes habilidades especiais:
- Guerreiro: Cria um escudo que bloqueia um projétil inimigo
- Arqueiro: Dispara uma flecha que arrasta projéteis inimigos na sua direção. Caso acerte o inimigo diretamente causa o dobro do dano.
- Mago: Atira um projétil que recupera um ponto de vida caso atinja o inimigo. Em caso contrário, o mago fica incapacitado de atacar durante 2 segundos.

Existem também vários itens por vezes dados ao jogador aleatóriamente depois de uma ronda terminada. Estes itens podem ser:
- Armas: Adicionam dano ao ataque do jogador. Estas armas dão mais dano quanto maior o seu nível.
- Gemas: Existindo vários tipos de gema, estas duplicam o dano do jogador caso a gema corresponda ao tipo de inimigo.
- Poção: Recupera um ponto de vida quando usada.

### Controlos
Os três botões da consola têm as seguintes funções:
|       | Botão A               | Botão B              | Botão C                     |
| ----- | --------------------- | -------------------- | --------------------------- |
| Menus | Mover para a esquerda | Selecionar/Confirmar | Mover para a direita/Voltar |
| Jogo  | Refletir projéteis    | Utilizar poção       | Usar ataque especial        |

### Interface e Ecrãs
Todas as capturas de ecrã do jogo assim como a interface do mesmo podem ser vistas na diretoria '04_Teste/capturas do jogo'.
