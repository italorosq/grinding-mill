# Grinding Mill

Sistema de controle para moinho com ESP8266 (Wemos D1 Mini), motor de passo, encoder rotativo e display LCD I2C.

## Funcionalidades

- Ajuste de velocidade por encoder no menu inicial.
- Ajuste de tempo de processo (em minutos) antes de iniciar.
- Navegacao por estados via botao do encoder:
  - `MENU_VELOCIDADE`
  - `MENU_TEMPO`
  - `ESTADO_RODANDO`
  - `ESTADO_FIM`
- Acionamento e desacionamento do motor via pino `EN` do driver.
- Controle de velocidade com rampa simples (`velocidadeAtual` -> `velocidadeAlvo`) para transicao mais suave.
- Exibicao em tempo real no LCD de:
  - Tempo decorrido e tempo alvo
  - Velocidade atual
- Parada automatica ao atingir o tempo configurado, com mensagem de processo concluido.

## Estrutura

- `firmware/`: codigo embarcado (PlatformIO + ESP8266).
- `hardware/`: documentacao de montagem, imagem de referencia e BOM.

Arquivos principais:

- `firmware/src/main.cpp`: logica principal do sistema.
- `firmware/platformio.ini`: ambiente PlatformIO do firmware.
- `hardware/README.md`: BOM e esquematico.

## Como compilar

```bash
cd firmware
pio run
```

## Como gravar no D1 Mini

```bash
cd firmware
pio run -t upload
```

## Monitor serial

```bash
cd firmware
pio device monitor -b 115200
```

## Documentacao complementar

- `firmware/README.md`
- `firmware/src/README.md`
- `firmware/include/README.md`
- `hardware/README.md`
- `hardware/images/README.md`
