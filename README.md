# Eco Select - Lixeira Inteligente com Arduino

O **Eco Select** é um projeto acadêmico de uma lixeira inteligente desenvolvida com Arduino, sensores e motores, com o objetivo de automatizar a identificação e separação de resíduos de forma prática e sustentável.

O projeto foi construído pensando em unir **programação embarcada**, **eletrônica**, **automação** e **sustentabilidade**, criando um protótipo funcional capaz de identificar diferentes tipos de materiais e acionar uma porta automaticamente para o descarte correto.

## Objetivo do Projeto

O objetivo do Eco Select é auxiliar no descarte seletivo de resíduos por meio de uma lixeira automatizada, capaz de identificar o tipo de lixo inserido e direcioná-lo para o compartimento correto.

Além da separação automatizada, o projeto também busca incentivar práticas sustentáveis, reduzindo erros no descarte e promovendo maior consciência ambiental.

## Destaques do Projeto

- Identificação automática de materiais;
- Uso de sensores para detecção de presença, metal e cor;
- Acionamento automático de porta com servo motor;
- Movimentação interna com motor de passo;
- Interface com display LCD;
- Alimentação diretamente pela tomada;
- Protótipo físico funcional;
- Foco em sustentabilidade e descarte correto de resíduos.

## Por que alimentação pela tomada?

Durante o desenvolvimento, optamos por alimentar a lixeira diretamente pela tomada em vez de utilizar pilhas ou baterias.

Essa decisão foi tomada pensando na proposta sustentável do projeto, já que o descarte incorreto de pilhas e baterias pode causar impactos ambientais. Dessa forma, o Eco Select evita a necessidade de troca frequente de baterias e reduz a geração desse tipo de resíduo.

## Funcionamento

O funcionamento do Eco Select ocorre em etapas:

1. O usuário aproxima ou insere um resíduo na lixeira.
2. O primeiro sensor de presença detecta a entrada do lixo.
3. O motor de passo movimenta o eixo interno para posicionar o resíduo nas áreas de análise.
4. O sensor indutivo verifica se o material é metálico.
5. Caso não seja metal, o sensor RGB realiza a leitura de cor para identificar outro tipo de material.
6. Caso o material ainda não tenha sido identificado, um segundo sensor de presença é utilizado na próxima etapa.
7. Quando o material é identificado, o display LCD informa o tipo de lixo.
8. O servo motor abre e fecha a porta correspondente.
9. O motor de passo retorna o eixo para a posição inicial.

## Materiais Identificados

No protótipo atual, o Eco Select identifica os seguintes tipos de materiais:

- Metal;
- Plástico;
- Papel.

## Componentes Utilizados

- Arduino;
- 2 sensores de presença;
- 1 sensor indutivo;
- 1 sensor RGB;
- 1 motor de passo;
- 1 servo motor;
- Display LCD 16x2 com módulo I2C;
- Estrutura física da lixeira;
- Fonte de alimentação conectada à tomada.

## Tecnologias Utilizadas

- Arduino;
- Linguagem C/C++;
- Biblioteca Stepper;
- Biblioteca Servo;
- Biblioteca Wire;
- Biblioteca LiquidCrystal_I2C.

## Estrutura do Código

O código principal está organizado em funções, mesmo sem comentários internos extensos, para manter a leitura simples e direta.

### `setup()`

Inicializa os componentes do projeto, como LCD, motor de passo, servo motor, comunicação serial e pinos dos sensores.

### `abre_fecha_servo()`

Realiza o movimento de abertura e fechamento da porta da lixeira. O servo motor gira de 0° até 90°, aguarda um pequeno intervalo e retorna para 0°.

### `movimenta_motor_passo()`

Movimenta o motor de passo em uma quantidade fixa de passos, deslocando o eixo interno para a próxima posição de análise.

### `volta_para_zero(int posicaoAtual)`

Após a identificação do resíduo, o motor de passo retorna o eixo para a posição inicial com base na quantidade de posições percorridas.

### `color()`

Faz a leitura do sensor RGB, armazenando os valores de vermelho, verde e azul para auxiliar na identificação do material.

### `loop()`

Executa a lógica principal do Eco Select. Quando o primeiro sensor de presença detecta um lixo, o sistema inicia a sequência de análise dos materiais. A identificação ocorre em etapas, verificando metal, plástico e papel. Após a identificação, o LCD informa o material detectado, o servo motor abre e fecha a porta, e o motor de passo retorna o eixo para a posição inicial.

## Lógica de Identificação

A lógica principal do Eco Select segue a seguinte ordem:

```cpp
if (sensor de presença inicial detectar lixo) {
    mover eixo para primeira posição;

    if (sensor indutivo detectar metal) {
        exibir "METAL" no LCD;
        abrir e fechar porta;
    }

    else {
        mover eixo para próxima posição;
        realizar leitura RGB;

        if (cor correspondente for identificada) {
            exibir "PLASTICO" no LCD;
            abrir e fechar porta;
        }

        else {
            mover eixo para próxima posição;

            if (segundo sensor de presença detectar lixo) {
                exibir "PAPEL" no LCD;
                abrir e fechar porta;
            }
        }
    }

    retornar eixo para posição inicial;
}
else {
    exibir "COLOQUE O LIXO!" no LCD;
}
