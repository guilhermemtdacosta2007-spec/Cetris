# CETRIS

Jogo de blocos inspirado no Tetris, desenvolvido em linguagem C para execução no
console do **Windows**, utilizando o Code::Blocks e o compilador MinGW.

O projeto foi organizado para facilitar a leitura do código-fonte, a compilação
e a avaliação acadêmica.

## Funcionalidades

- Tabuleiro com 10 colunas e 20 linhas.
- Sete peças clássicas.
- Movimentação, rotação e queda rápida das peças.
- Pré-visualização da próxima peça.
- Recurso para guardar uma peça e utilizá-la posteriormente.
- Projeção da posição em que a peça vai parar.
- Pontuação, nível e contagem de linhas removidas.
- Recorde salvo localmente no arquivo `highscore.txt`.
- Menu para escolher o nível inicial.
- Tela de fim de jogo com opção de reiniciar ou sair.

## Controles

| Tecla | Ação |
|---|---|
| `A` ou `←` | Mover para a esquerda |
| `D` ou `→` | Mover para a direita |
| `S` ou `↓` | Acelerar a descida |
| `W`, `R` ou `↑` | Girar a peça |
| `H` | Guardar a peça atual ou trocar pela peça guardada |
| `Espaço` | Descer a peça imediatamente |

Na tela de fim de jogo, pressione `R` para voltar ao menu e iniciar outra
partida, ou `ESC` para sair.

O uso de `H` é limitado a uma vez por peça. Depois que uma nova peça é fixada,
o recurso fica disponível novamente.

## Estrutura do repositório

```text
CETRIS/
├── src/
│   └── cetris.c
├── CETRIS.cbp
├── README.md
└── .gitignore
```

- `src/cetris.c`: código-fonte do jogo.
- `CETRIS.cbp`: projeto para abrir diretamente no Code::Blocks.
- `README.md`: documentação e instruções.
- `.gitignore`: arquivos gerados localmente que não precisam ser enviados ao GitHub.

## Requisitos

- Windows.
- Code::Blocks com MinGW/GCC instalado.
- Terminal do Windows compatível com a página de código UTF-8.

O projeto utiliza `windows.h` e `conio.h`, portanto foi preparado para Windows.
Não é necessário instalar bibliotecas gráficas ou bibliotecas externas.

## Como abrir e executar no Code::Blocks

1. Baixe o repositório pelo botão **Code > Download ZIP** no GitHub e extraia
   o conteúdo, ou clone o repositório com Git.
2. Abra o arquivo `CETRIS.cbp` no Code::Blocks.
3. Confira se o compilador **GNU GCC Compiler** está configurado em
   **Settings > Compiler**.
4. Selecione o alvo **Debug** ou **Release**.
5. Clique em **Build and Run** ou pressione `F9`.

O projeto está configurado para utilizar o padrão C99. O arquivo de recorde
`highscore.txt` é criado automaticamente na pasta de execução quando uma nova
pontuação supera o recorde anterior.

## Compilar pelo terminal com MinGW

Abra o Prompt de Comando ou o terminal na pasta raiz do repositório e execute:

```bash
gcc -std=c99 -Wall -Wextra -o CETRIS.exe src/cetris.c
```

Depois, execute:

```bash
CETRIS.exe
```

O MinGW deve estar instalado e o executável `gcc` precisa estar disponível no
`PATH` do Windows.

## Como o professor pode baixar e testar

1. Acesse a página do repositório no GitHub.
2. Clique em **Code > Download ZIP**.
3. Extraia o arquivo ZIP.
4. Abra `CETRIS.cbp` no Code::Blocks.
5. Pressione `F9` para compilar e executar.

Também é possível consultar o código diretamente em `src/cetris.c` pela página
do GitHub, sem baixar o projeto.

## Observações

- O projeto é destinado ao Windows e ao console.
- O recorde é armazenado localmente em `highscore.txt`, que é gerado durante
  a execução e ignorado pelo Git.
- Os arquivos executáveis e temporários do Code::Blocks não fazem parte do
  código-fonte publicado.
