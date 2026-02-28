# Grinding Mill

Projeto organizado em duas frentes principais:

- `firmware/`: codigo embarcado (PlatformIO + ESP8266).
- `hardware/`: documentacao, imagem de montagem e lista de materiais (BOM).

## Estrutura

- `firmware/README.md`
- `firmware/src/README.md`
- `firmware/include/README.md`
- `hardware/README.md`
- `hardware/images/README.md`

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
