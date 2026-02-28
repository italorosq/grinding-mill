# Firmware

Firmware do moinho usando ESP8266 (Wemos D1 Mini) com PlatformIO.

## Conteudo

- `platformio.ini`: configuracao de ambiente e bibliotecas.
- `src/main.cpp`: logica principal (menu, encoder, LCD e motor).
- `include/`: headers opcionais para modularizacao futura.

## Uso rapido

```bash
pio run
pio run -t upload
pio device monitor -b 115200
```

## Fluxo funcional atual

1. Ajuste de velocidade no menu.
2. Ajuste do tempo de processo.
3. Execucao do motor ate tempo alvo.
4. Tela de conclusao.
