/*
 * CETRIS - Jogo de blocos em C para Windows.
 * Projeto acadêmico desenvolvido para execução no console.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define LARGURA 10
#define ALTURA 20
#define ARQUIVO_RECORD "highscore.txt"

int tabuleiro[ALTURA][LARGURA] = {0};

typedef struct {
    int forma[4][4];
    int x, y;
    int tipo;
} Peca;

Peca pecaAtual;
int proximaPeca;
int pecaGuardada = -1;
int podeGuardar = 1;

int pontuacao = 0;
int linhasTotais = 0;
int nivelInicial = 0;
int nivel = 0;
int highscore = 0;
int fimDeJogo = 0;

// As 7 peças clássicas do Tetris
const int pecas[7][4][4] = {
    {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}}, // I
    {{1,0,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}, // J
    {{0,0,1,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}, // L
    {{0,1,1,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}}, // O
    {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}, // S
    {{0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}, // T
    {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}}  // Z
};

// Carrega o recorde salvo, caso o arquivo exista.
void carregarHighScore() {
    FILE *f = fopen(ARQUIVO_RECORD, "r");
    if (f != NULL) {
        if (fscanf(f, "%d", &highscore) != 1 || highscore < 0) {
            highscore = 0;
        }
        fclose(f);
    } else {
        highscore = 0;
    }
}

// Atualiza o recorde e grava o novo valor no arquivo.
void salvarHighScore() {
    if (pontuacao > highscore) {
        highscore = pontuacao;
        FILE *f = fopen(ARQUIVO_RECORD, "w");
        if (f != NULL) {
            fprintf(f, "%d", highscore);
            fclose(f);
        }
    }
}

// Define a cor usada no console do Windows.
void definirCor(int tipo) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (tipo) {
        case 1: SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); break; // Ciano (I)
        case 2: SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY); break; // Azul (J)
        case 3: SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); break; // Vermelho (L)
        case 4: SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); break; // Amarelo (O)
        case 5: SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); break; // Verde (S)
        case 6: SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); break; // Roxo (T)
        case 7: SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); break; // Branco claro (Z)
        case 8: SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY); break; // Cinza (Sombra/Bordas)
        default: SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break; // Reset
    }
}

// Reposiciona o cursor no início da área do jogo.
void limparTela() {
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Oculta o cursor durante a partida.
void ocultarCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// Copia o formato da peça e define sua posição inicial.
void criarPeca(Peca *p, int tipo) {
    p->tipo = tipo;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            p->forma[i][j] = pecas[tipo][i][j];
        }
    }
    p->x = LARGURA / 2 - 2;
    p->y = 0;
}

// Limpa o tabuleiro e reinicia os dados da partida.
void reiniciarJogo() {
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            tabuleiro[i][j] = 0;
        }
    }
    pontuacao = 0;
    linhasTotais = 0;
    nivel = nivelInicial;
    fimDeJogo = 0;
    pecaGuardada = -1;
    podeGuardar = 1;
    proximaPeca = rand() % 7;
    criarPeca(&pecaAtual, rand() % 7);
    system("cls");
}

// Verifica colisões com as bordas, o chão e as peças fixas.
int checarColisao(int novoX, int novoY, int forma[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (forma[i][j]) {
                int x = novoX + j;
                int y = novoY + i;
                if (x < 0 || x >= LARGURA || y >= ALTURA) return 1;
                if (y >= 0 && tabuleiro[y][x]) return 1;
            }
        }
    }
    return 0;
}

// Fixa a peça atual no tabuleiro.
void fixarPeca() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (pecaAtual.forma[i][j]) {
                int y = pecaAtual.y + i;
                int x = pecaAtual.x + j;
                if (y >= 0) {
                    tabuleiro[y][x] = pecaAtual.tipo + 1;
                }
            }
        }
    }
    podeGuardar = 1;
}

// Remove linhas completas e atualiza a pontuação e o nível.
void limparLinhas() {
    int linhasRemovidas = 0;
    for (int i = ALTURA - 1; i >= 0; i--) {
        int completa = 1;
        for (int j = 0; j < LARGURA; j++) {
            if (tabuleiro[i][j] == 0) {
                completa = 0;
                break;
            }
        }
        if (completa) {
            linhasRemovidas++;
            linhasTotais++;
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < LARGURA; j++) {
                    tabuleiro[k][j] = tabuleiro[k - 1][j];
                }
            }
            for (int j = 0; j < LARGURA; j++) {
                tabuleiro[0][j] = 0;
            }
            i++;
        }
    }

    if (linhasRemovidas > 0) {
        int pontosBase[5] = {0, 40, 100, 300, 1200};
        pontuacao += pontosBase[linhasRemovidas] * (nivel + 1);

        int proximoNivel = nivelInicial + (linhasTotais / 10);
        if (proximoNivel > nivel) {
            nivel = proximoNivel;
        }
    }
}

// Gira a peça e tenta pequenos ajustes laterais se necessário.
void rotacionarPeca() {
    int temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = pecaAtual.forma[3 - j][i];
        }
    }

    if (!checarColisao(pecaAtual.x, pecaAtual.y, temp)) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                pecaAtual.forma[i][j] = temp[i][j];
            }
        }
        return;
    }

    int kicks[] = {1, -1, 2, -2};
    for (int k = 0; k < 4; k++) {
        if (!checarColisao(pecaAtual.x + kicks[k], pecaAtual.y, temp)) {
            pecaAtual.x += kicks[k];
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    pecaAtual.forma[i][j] = temp[i][j];
                }
            }
            return;
        }
    }
}

// Cria a próxima peça e verifica se há espaço para ela.
void gerarNovaPeca() {
    criarPeca(&pecaAtual, proximaPeca);
    proximaPeca = rand() % 7;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (pecaAtual.forma[i][j] && tabuleiro[pecaAtual.y + i][pecaAtual.x + j]) {
                fimDeJogo = 1;
                salvarHighScore();
            }
        }
    }
}

// Guarda a peça atual ou troca pela peça armazenada.
void trocarPecaGuardada() {
    if (!podeGuardar) return;

    if (pecaGuardada == -1) {
        pecaGuardada = pecaAtual.tipo;
        gerarNovaPeca();
    } else {
        int temp = pecaAtual.tipo;
        criarPeca(&pecaAtual, pecaGuardada);
        pecaGuardada = temp;
    }
    podeGuardar = 0;
}

// Desenha o tabuleiro e as informações da partida.
void desenharInterface() {
    limparTela();
    definirCor(1);
    printf("╔══════════════════════════════════════════════╗\n");
    printf("║             C E T R I S   A R C A D E        ║\n");
    printf("╠════════════════════════╦═════════════════════╣\n");

    for (int i = 0; i < ALTURA; i++) {
        definirCor(8);
        printf("║");

        int sombraY = pecaAtual.y;
        while (!checarColisao(pecaAtual.x, sombraY + 1, pecaAtual.forma)) {
            sombraY++;
        }

        for (int j = 0; j < LARGURA; j++) {
            int preenchido = tabuleiro[i][j];
            int fantasma = 0;

            if (!preenchido) {
                int px = j - pecaAtual.x;
                int py = i - pecaAtual.y;
                if (px >= 0 && px < 4 && py >= 0 && py < 4) {
                    if (pecaAtual.forma[py][px]) {
                        preenchido = pecaAtual.tipo + 1;
                    }
                }
                if (!preenchido) {
                    int fpx = j - pecaAtual.x;
                    int fpy = i - sombraY;
                    if (fpx >= 0 && fpx < 4 && fpy >= 0 && fpy < 4) {
                        if (pecaAtual.forma[fpy][fpx] && sombraY > pecaAtual.y) {
                            fantasma = 1;
                        }
                    }
                }
            }

            if (preenchido) {
                definirCor(preenchido);
                printf("██");
            } else if (fantasma) {
                definirCor(8);
                printf("░░");
            } else {
                definirCor(0);
                printf("  ");
            }
        }

        definirCor(8);
        printf("║");

        if (i == 1) {
            printf(" RECORDE (HI):       ");
        } else if (i == 2) {
            definirCor(6);
            printf(" %-19d ", highscore);
        } else if (i == 4) {
            definirCor(1);
            printf(" PONTUACAO:          ");
        } else if (i == 5) {
            definirCor(4);
            printf(" %-19d ", pontuacao);
        } else if (i == 7) {
            definirCor(1);
            printf(" NIVEL / LINHAS:     ");
        } else if (i == 8) {
            definirCor(5);
            printf(" Nv:%-2d  Lin:%-4d    ", nivel, linhasTotais);
        } else if (i == 10) {
            definirCor(1);
            printf(" PECA GUARDADA [H]:  ");
        } else if (i >= 11 && i <= 14) {
            int pRow = i - 11;
            printf("    ");
            for (int c = 0; c < 4; c++) {
                if (pecaGuardada != -1 && pecas[pecaGuardada][pRow][c]) {
                    definirCor(pecaGuardada + 1);
                    printf("██");
                } else {
                    definirCor(0);
                    printf("  ");
                }
            }
            printf("         ");
        } else if (i == 16) {
            definirCor(1);
            printf(" PROXIMA PECA:       ");
        } else if (i >= 17 && i <= 19) {
            int pRow = i - 17;
            printf("    ");
            for (int c = 0; c < 4; c++) {
                if (pecas[proximaPeca][pRow][c]) {
                    definirCor(proximaPeca + 1);
                    printf("██");
                } else {
                    definirCor(0);
                    printf("  ");
                }
            }
            printf("         ");
        } else {
            printf("                     ");
        }

        definirCor(8);
        printf("║\n");
    }

    definirCor(1);
    printf("╚════════════════════════╩═════════════════════╝\n");
    printf(" [WASD/Setas] Mover | [R] Rodar | [H] Guardar | [Espaco] Queda\n");
}

// Exibe o menu e retorna o nível inicial escolhido.
int exibirMenu() {
    carregarHighScore();
    system("cls");
    definirCor(1);
    printf("\n\n");
    printf("    ██████╗███████╗████████╗██████╗ ██╗███████╗\n");
    printf("   ██╔════╝██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝\n");
    printf("   ██║     █████╗     ██║   ██████╔╝██║███████╗\n");
    printf("   ██║     ██╔══╝     ██║   ██╔══██╗██║╚════██║\n");
    printf("   ╚██████╗███████╗   ╚═╝   ╚═╝  ╚═╝╚═╝╚══════╝\n");

    definirCor(4);
    printf("\n       ========================================\n");
    printf("         RECORDE ATUAL : %d\n", highscore);
    printf("         ESCOLHA O NIVEL INICIAL (0 a 9):\n");
    printf("         Pressione uma tecla de 0 a 9\n");
    printf("       ========================================\n");
    definirCor(7);
    printf("       Aguardando selecao...\n");

    while (1) {
        if (_kbhit()) {
            char tecla = _getch();
            if (tecla >= '0' && tecla <= '9') {
                return tecla - '0';
            }
        }
    }
}

// Inicializa o jogo e executa o ciclo principal.
int main() {
    system("chcp 65001 > nul");
    srand((unsigned int)time(NULL));
    ocultarCursor();

    nivelInicial = exibirMenu();
    reiniciarJogo();
    int contadorQueda = 0;

    while (1) {
        if (!fimDeJogo) {
            if (_kbhit()) {
                int tecla = _getch();

                if (tecla == 224) {
                    int seta = _getch();
                    if (seta == 75) {
                        if (!checarColisao(pecaAtual.x - 1, pecaAtual.y, pecaAtual.forma)) pecaAtual.x--;
                    } else if (seta == 77) {
                        if (!checarColisao(pecaAtual.x + 1, pecaAtual.y, pecaAtual.forma)) pecaAtual.x++;
                    } else if (seta == 80) {
                        if (!checarColisao(pecaAtual.x, pecaAtual.y + 1, pecaAtual.forma)) pecaAtual.y++;
                    } else if (seta == 72) {
                        rotacionarPeca();
                    }
                } else {
                    if (tecla == 'a' || tecla == 'A') {
                        if (!checarColisao(pecaAtual.x - 1, pecaAtual.y, pecaAtual.forma)) pecaAtual.x--;
                    } else if (tecla == 'd' || tecla == 'D') {
                        if (!checarColisao(pecaAtual.x + 1, pecaAtual.y, pecaAtual.forma)) pecaAtual.x++;
                    } else if (tecla == 's' || tecla == 'S') {
                        if (!checarColisao(pecaAtual.x, pecaAtual.y + 1, pecaAtual.forma)) pecaAtual.y++;
                    } else if (tecla == 'w' || tecla == 'W' ||
                               tecla == 'r' || tecla == 'R') {
                        rotacionarPeca();
                    } else if (tecla == 'h' || tecla == 'H') {
                        trocarPecaGuardada();
                    } else if (tecla == ' ') {
                        while (!checarColisao(pecaAtual.x, pecaAtual.y + 1, pecaAtual.forma)) {
                            pecaAtual.y++;
                        }
                        fixarPeca();
                        limparLinhas();
                        gerarNovaPeca();
                    }
                }
            }

            contadorQueda++;

            int velocidades[10] = {30, 26, 22, 18, 13, 9, 6, 4, 3, 2};
            int velocidadeAtual = (nivel < 10) ? velocidades[nivel] : 1;

            if (contadorQueda > velocidadeAtual) {
                if (!checarColisao(pecaAtual.x, pecaAtual.y + 1, pecaAtual.forma)) {
                    pecaAtual.y++;
                } else {
                    fixarPeca();
                    limparLinhas();
                    gerarNovaPeca();
                }
                contadorQueda = 0;
            }

            desenharInterface();
            Sleep(20);
        } else {
            salvarHighScore();
            system("cls");
            definirCor(2);
            printf("\n\n\n\n");
            printf("        ██████╗  █████╗ ███╗   ███╗███████╗    ██████╗ ██╗   ██╗███████╗██████╗ \n");
            printf("       ██╔════╝ ██╔══██╗████╗ ████║██╔════╝   ██╔═══██╗██║   ██║██╔════╝██╔══██╗\n");
            printf("       ██║  ███╗███████║██╔████╔██║█████╗     ██║   ██║██║   ██║█████╗  ██████╔╝\n");
            printf("       ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝     ██║   ██║██║   ██║██╔══╝  ██╔══██╗\n");
            printf("       ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗   ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║\n");
            printf("        ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝    ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝\n");

            definirCor(4);
            printf("\n\n       Pontuacao Final : %d", pontuacao);
            printf("\n       Recorde Atual   : %d", highscore);
            printf("\n       Nivel Atingido  : %d", nivel);
            printf("\n       Linhas Totais   : %d\n\n", linhasTotais);

            definirCor(7);
            printf("       Pressione [R] para reiniciar ou [ESC] para sair.\n");

            int escolha = 0;
            while (escolha != 'r' && escolha != 'R' && escolha != 27) {
                if (_kbhit()) {
                    escolha = _getch();
                    if (escolha == 'r' || escolha == 'R') {
                        nivelInicial = exibirMenu();
                        reiniciarJogo();
                    } else if (escolha == 27) {
                        return 0;
                    }
                }
            }
        }
    }

    return 0;
}
