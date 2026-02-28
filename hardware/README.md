# Hardware

Documentacao de hardware do projeto do moinho.

## Conteudo

- `images/moinhoserra_bb.png`: diagrama/foto de referencia da montagem.

## Esquematico

![Esquematico de ligacao](images/moinhoserra_bb.png)

## BOM (Bill of Materials)

| Item | Quantidade | Observacao |
|---|---:|---|
| Wemos D1 Mini (ESP8266) | 1 | Controlador principal |
| Driver de motor de passo (A4988 ou DRV8825) | 1 | Compativel com `STEP`/`DIR` |
| Motor de passo | 1 | Compatibilizar corrente com driver |
| Display LCD 16x2 com interface I2C (0x27) | 1 | Usado com `LiquidCrystal_I2C` |
| Encoder rotativo com push-button | 1 | Ajuste de parametros e navegacao |
| Fonte de alimentacao adequada | 1 | Conforme motor e eletronica |
| Protoboard/PCB e jumpers | 1 kit | Interligacoes |

## Mapeamento de sinais no firmware

- `STEP_PIN`: `D2`
- `DIR_PIN`: `D1`
- `EN_PIN`: `D8`
- `ENCODER_CLK`: `D4`
- `ENCODER_DT`: `D3`
- `ENCODER_SW`: `D7`
- `LCD SDA`: `D5`
- `LCD SCL`: `D6`
