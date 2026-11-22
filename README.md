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
3. Confira se o compilador **GNU GCC Compiler** está configurado. As instruções
   para corrigir o caminho do MinGW estão na seção seguinte.
4. Selecione o alvo **Debug** ou **Release**.
5. Clique em **Build and Run** ou pressione `F9`.

O projeto está configurado para utilizar o padrão C99. O arquivo de recorde
`highscore.txt` é criado automaticamente na pasta de execução quando uma nova
pontuação supera o recorde anterior.

## Solução de problemas: Code::Blocks não encontra o compilador

Ao tentar compilar, o Code::Blocks pode mostrar uma mensagem parecida com esta:

```text
The compiler's setup (GNU GCC Compiler) is invalid.
Tried to run compiler executable 'C:\MinGW/bin/gcc.exe', but failed!
```

Isso geralmente significa que o Code::Blocks está configurado para procurar o
GCC em uma pasta que não existe ou não contém o compilador. O problema está na
configuração do MinGW, e não necessariamente no código do CETRIS.

### 1. Verificar se o MinGW foi instalado

Se ainda for instalar o Code::Blocks, prefira o instalador cujo nome contém
`mingw` (por exemplo, `codeblocks-...mingw-setup.exe`). Ele já inclui o
compilador MinGW/GCC. Um instalador sem `mingw` pode instalar apenas o ambiente
do Code::Blocks, sem o compilador.

### 2. Detectar o compilador automaticamente

1. Abra o Code::Blocks.
2. Clique em **Settings > Compiler...**.
3. Selecione **GNU GCC Compiler** em **Global compiler settings**.
4. Abra a aba **Toolchain executables**.
5. Clique em **Auto-detect**.
6. Confira se o diretório de instalação do compilador foi preenchido com a pasta
   correta. Clique em **OK** para salvar.

Depois, tente compilar novamente com `F9`.

### 3. Configurar o caminho manualmente, se o Auto-detect não funcionar

1. Na aba **Toolchain executables**, localize **Compiler's installation
   directory**.
2. Clique no botão de procurar pasta e selecione a pasta principal do MinGW,
   isto é, a pasta que contém a subpasta `bin`.
3. Dentro de `bin`, confirme que existem pelo menos `gcc.exe` e `g++.exe`.
4. Salve as configurações em **OK** e tente compilar novamente.

O caminho depende de onde o Code::Blocks/MinGW foi instalado. Um exemplo comum
é:

```text
C:\Program Files\CodeBlocks\MinGW
```

Em algumas instalações, a pasta pode estar em outro local, como
`C:\Program Files (x86)\CodeBlocks\MinGW`. Use somente o caminho que
realmente existe no seu computador. Não mantenha `C:\MinGW` se essa pasta não
existir ou não tiver o arquivo `bin\gcc.exe`.

**Importante:** o campo **Compiler's installation directory** deve apontar para
a pasta principal do MinGW, e não diretamente para `bin` nem para o arquivo
`gcc.exe`.

### 4. Se o compilador não estiver instalado

Se não houver uma pasta MinGW com `bin\gcc.exe`, instale novamente o Code::Blocks
usando o instalador para Windows que inclui MinGW (o nome do arquivo contém
`mingw`). Depois de instalar, volte às etapas de detecção automática acima.

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
