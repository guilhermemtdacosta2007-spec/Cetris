# CETRIS

Clone de Tetris em linguagem C para console Windows (desenvolvido no Code::Blocks).

## Funcionalidades
- Tabuleiro classico `10x20` com as 7 pecas (`I`, `J`, `L`, `O`, `S`, `T`, `Z`).
- Rotacao com ajuste lateral (*wall kick*), *ghost piece* e reserva de peca (*hold*).
- Selecao de nivel inicial (`0` a `9`) e progressao automatica de velocidade.
- Salvamento de recorde em `highscore.txt`.

## Controles
- **Mover:** `A` / `D` / `S` ou setas `Esquerda` / `Direita` / `Baixo`
- **Rotacionar:** `R` ou seta `Cima`
- **Guardar peca:** `H`
- **Queda rapida:** `Espaco`

## Como compilar e executar (Windows)
1. Abra `cetris.c` no **Code::Blocks** (ou compile via terminal com `gcc cetris.c -o cetris.exe`).
2. Execute o programa no console do Windows.
