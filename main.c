// Copyright 2018 Rachieru Costin-Tudor <costinrch46@gmail.com>
#include <stdio.h>

// Afiseaza Macroboardul.
void afisare_macro(int n, int macroboard[10][10]) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (macroboard[i][j] == 1) printf("X");
            if (macroboard[i][j] == 2) printf("0");
            if (macroboard[i][j] == 0) printf("-");
            if (macroboard[i][j] == -2) printf("X");
            if (macroboard[i][j] == -1) printf("0");
        }
        printf("\n");
    }
}

// Verifica daca celula respectiva este libera.
int check_empty(int x, int y, int board[100][100]) {
    if (board[x][y] != 0) {
        return 0;
        } else {
            return 1;
            }
}

/* Verifica daca parametrii de intrare sunt corecti,
adica sa indice spre un loc care exista pe board. */
int check_limits(int x, int y, int n) {
    if ((x >= (n * n)) || (x < 0)) {
        return 0;
        }
    if ((y >= (n * n)) || (y < 0)) {
        return 0;
        }
    return 1;
}

// Verifica daca ordinea in care pun X si 0 e corecta.
int check_order(int c, int i, int before) {
    if (i == 0) {
        if (c != 88) return 0;
        } else {
            if (c == before) return 0;
            }
    return 1;
}

// Verifica daca mai este loc pe board.
int check_space(int n, int mutari) {
    if (mutari <= (n * n * n * n )) {
        return 1;
        } else {
            return 0;
            }
}

// Functie pentru atribuirea mutarilor in cazul celor invalide.
void round_robin(char c, int n, int board[100][100]) {
    int i, j, j_up = 1, i_down = 1,
    gasit = 0, up_or_down = 0;
    /* Cand variabila up_or_down este 0 se va parcurge diagonala principala,
    cand este 1 se va parcurge urmatoarea diagonala de deasupra, 
    iar cand e -1 se va parcurge urmatoarea diagonala de dedesubt. */
    while (gasit == 0) {
        if (up_or_down == 0) {
            i = 0;
            j = 0;
            }
        if (up_or_down == 1) {
            i = 0;
            j = 0 + j_up;
            }
        if (up_or_down == -1) {
            i = 0 + i_down;
            j = 0;
            }
        while ((i < (n * n)) && (j < (n * n))) {
            if (check_empty(i, j, board)) {
                if (c == 88) {
                    board[i][j] = 1;
                    gasit = 1;
                    } else {
                        board[i][j] = 2;
                        gasit = 1;
                        }
                break;
                } else {
                    i++;
                    j++;
                    }
        }
        /* Se modifca up_or_down in asa fel incat 
        sa ia in ordinea corecta diagonalele. */
        if (up_or_down == 0) {
            up_or_down = 1;
            } else {
                if (up_or_down == 1) {
                    j_up++;
                    up_or_down = -1;
                    } else {
                        if (up_or_down == -1) {
                            i_down++;
                            up_or_down = 1;
                            }
                        }
                }
    }
}

// Gaseste catigatorul din fiecare Miniboard.
int check_winner(int n, int aux[10][10]) {
    int i, j, boo1, boo2;
    // Diagonala principala
    i = 0;
    boo1 = 1;
    boo2 = 1;
    for (j = 0; j < n; j++) {
        if (aux[i][j] == 1) boo2 = 0;
        if (aux[i][j] == 2) boo1 = 0;
        if (aux[i][j] == 0) {
            boo1 = 0;
            boo2 = 0;
        }
        i++;
    }
    if (boo1 == 1) return 1;
    if (boo2 == 1) return 2;
    // Diagonala secundara
    i = 0;
    boo1 = 1;
    boo2 = 1;
    for (j = n-1; j >= 0; j--) {
        if (aux[i][j] == 1) boo2 = 0;
        if (aux[i][j] == 2) boo1 = 0;
        if (aux[i][j] == 0) {
            boo1 = 0;
            boo2 = 0;
        }
        i++;
    }
    if (boo1 == 1) return 1;
    if (boo2 == 1) return 2;
    // Fiecare linie
    i = 0;
    while (i < n) {
        boo1 = 1;
        boo2 = 1;
        for (j = 0; j < n; j++) {
            if (aux[i][j] == 1) boo2 = 0;
            if (aux[i][j] == 2) boo1 = 0;
            if (aux[i][j] == 0) {
                boo1 = 0;
                boo2 = 0;
            }
        }
        if (boo1 == 1) return 1;
        if (boo2 == 1) return 2;
        i++;
    }
    // Fiecare coloana
    j = 0;
    while (j < n) {
        boo1 = 1;
        boo2 = 1;
        for (i = 0; i < n; i++) {
            if (aux[i][j] == 1) boo2 = 0;
            if (aux[i][j] == 2) boo1 = 0;
            if (aux[i][j] == 0) {
                boo1 = 0;
                boo2 = 0;
            }
        }
        if (boo1 == 1) return 1;
        if (boo2 == 1) return 2;
        j++;
    }
    return 0;
}

// Gaseste castigatorul din Macroboard.
int check_final_winner(int n, int aux[10][10]) {
    int i, j, boo1, boo2, WinnerX = 0, Winner0 = 0;
    // Diagonala principala
    i = 0;
    boo1 = 1;
    boo2 = 1;
    for (j = 0; j < n; j++) {
        if (aux[i][j] == 1) boo2 = 0;
        if (aux[i][j] == 2) boo1 = 0;
        if (aux[i][j] == 0) {
            boo1 = 0;
            boo2 = 0;
        }
        i++;
    }
    if (boo1 == 1) WinnerX = 1;
    if (boo2 == 1) Winner0 = 1;
    // Diagonala secundara
    i = 0;
    boo1 = 1;
    boo2 = 1;
    for (j = n-1; j >= 0; j--) {
        if (aux[i][j] == 1) boo2 = 0;
        if (aux[i][j] == 2) boo1 = 0;
        if (aux[i][j] == 0) {
            boo1 = 0;
            boo2 = 0;
        }
        i++;
    }
    if (boo1 == 1) WinnerX = 1;
    if (boo2 == 1) Winner0 = 1;
    // Fiecare linie
    i = 0;
    while (i < n) {
        boo1 = 1;
        boo2 = 1;
        for (j = 0; j < n; j++) {
            if (aux[i][j] == 1) boo2 = 0;
            if (aux[i][j] == 2) boo1 = 0;
            if (aux[i][j] == 0) {
                boo1 = 0;
                boo2 = 0;
            }
        }
        if (boo1 == 1) WinnerX = 1;
        if (boo2 == 1) Winner0 = 1;
        i++;
    }
    // Fiecare coloana
    j = 0;
    while (j < n) {
        boo1 = 1;
        boo2 = 1;
        for (i = 0; i < n; i++) {
            if (aux[i][j] == 1) boo2 = 0;
            if (aux[i][j] == 2) boo1 = 0;
            if (aux[i][j] == 0) {
                boo1 = 0;
                boo2 = 0;
            }
        }
        if (boo1 == 1) WinnerX = 1;
        if (boo2 == 1) Winner0 = 1;
        j++;
    }
    if (WinnerX == 1 && Winner0 == 1) return 0;
    if (WinnerX == 1 && Winner0 == 0) return 1;
    if (WinnerX == 0 && Winner0 == 1) return 2;
    if (WinnerX == 0 && Winner0 == 0) return 0;
    return 0;
}

// Functie pentru completarea Macroboardului.
void completare_macro(int n, int board[100][100],
int macroboard[][10], int robin) {
    int ii, jj, i, j, aux[10][10] = {{0}};
    for (i = 0; i < n; i++) {
        j = 0;
        // Ia randul i de miniboarduri si pune fiecare miniboard in aux.
        while (j < n) {
            for (ii = i * n; ii < (i + 1) * n; ii++) {
                for (jj = j * n; jj < (j + 1) * n; jj++) {
                    aux[ii % n][jj % n] = board[ii][jj];
                }
            }
            if (macroboard[i][j] == 0) {
                macroboard[i][j] = check_winner(n, aux);
                if (macroboard[i][j] != 0) {
                    if (robin == 1) {
                        macroboard[i][j] -= 3;
                                /*  Valoarea -2 pentru cand castiga
                                X, dar nu prin alegerea lui,
                                respectiv -1 pentru 0, in acelasi caz. */ 
                    }
                }
            }
            j++;
        }
    }
}

/* Citeste si pune in board "1" pentru X si "2" pentru 0.
De asemenea afiseaza erorile si atribuie automat o mutare 
in cazul celor invalide, creand astfel si Macroboardul. */ 
void citire_erori_macro(int n, int m, int board[100][100],
int macroboard[10][10], int *pX, int *p0) {
    int i, j, x, y, mutari = 1, empty, limits, order, space,
    before, robin = 0;
    char c;
    for (i = 0; i < m; i++) {
        robin = 0; // Tine minte daca sa facut round_robin sau nu.
        scanf("%s %d %d", &c, &x, &y);
        space = check_space(n, mutari);
        limits = check_limits(x, y, n);
        order = check_order(c, i, before);
        if (limits) {
            empty = check_empty(x, y, board);
            } else {
                empty = 0;
                }
        before = c;
        // Afisarea erorilor.
        if (space == 0) {
            if (limits == 0) {
                printf("INVALID INDEX\n");
            } else {
                printf("NOT AN EMPTY CELL\n");
            }
            printf("FULL BOARD\n");
            for (j = i; j < m; j++) {
                scanf("%s %d %d", &c, &x, &y);
                }
            break;
            }
        if (order == 0) {
            printf("NOT YOUR TURN\n");
        } else {
            if (limits == 0) printf ("INVALID INDEX\n");
            }
        if ((limits == 1) && (order == 1)) {
            if (empty == 0) printf ("NOT AN EMPTY CELL\n");
            }
        // Cazul in care mutarea este valida.
        if ((space == 1) && (limits == 1) &&
            (order == 1) && (empty == 1)) {
            if (c == 88) {
                board[x][y] = 1;
                *pX+=1;
                } else {
                    board[x][y] = 2;
                    *p0+=1;
                    }
            mutari++;
            }
        // Cazul in care mutarea este invalida.
        if ((limits == 0) || (empty == 0)) {
            if ((order == 1) && (space == 1)) {
                mutari++;
                if (c == 88) {
                    *pX += 1;
                } else {
                    *p0 += 1;
                }
                round_robin(c, n, board);
                robin = 1;
                }
            }
        // Doar dupa minim 5 mutari poate fi castigat un miniboard.
        if (mutari >= 5) completare_macro(n, board, macroboard, robin);
    }
}

// Copiaza Macroboardul in matricea aux pentru verificarea castigatorului.
void macro_aux(int n, int aux[10][10], int macroboard[10][10]) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            if (macroboard[i][j] >= 0) {
                aux[i][j] = macroboard[i][j];
            } else {
                aux[i][j] = macroboard[i][j] + 3;
            }
        }
}

// Afiseaza rezultatul meciului.
int who_won(int n, int aux[10][10]) {
    int check;
    check = check_final_winner(n, aux);
    if (check == 0) {
        printf("Draw again! Let's play darts!\n");
    }
    if (check == 1) {
        printf("X won\n");
    }
    if (check == 2) {
        printf("0 won\n");
    }
    return 0;
}

// Calculeaza cate miniboarduri a castigat fiecare jucator.
void wins_per_person(int n, int macroboard[10][10], int *pWinX, int *pWin0) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            if (macroboard[i][j] == 1) {
                *pWinX += 1;
            }
            if (macroboard[i][j] == 2) {
                *pWin0 += 1;
            }
        }
}

// Calculeaza si afiseaza coeficientul de atentie al jucatorilor.
void attention(int winX, int contorX, int win0, int contor0) {
    double attentionX, attention0;
    if (contorX != 0) {
        attentionX = (double) winX / contorX;
    } else {
        attentionX = -1;
    }
    if (contor0 != 0) {
        attention0 = (double) win0 / contor0;
    } else {
        attention0 = -1;
    }
    if (attentionX != -1) {
        printf("X %.10f\n", attentionX);
    } else {
        printf("X N/A\n");
    }
    if (attention0 != -1) {
        printf("0 %.10f\n", attention0);
    } else {
        printf("0 N/A\n");
    }
}

int main() {
    int board[100][100] = {{0}}, n, m,
    aux[10][10], macroboard[10][10] = {{0}},
    contorX = 0, contor0 = 0, winX = 0, win0 = 0;
    int *pX, *p0, *pWinX, *pWin0;
    pX = &contorX;     // Contoare catre variabilele care contorizeaza
    p0 = &contor0; // numarul de runde jucate de fiecare jucator.
    pWinX = &winX;     // Contoare catre varibilele care contorizeaza numarul
    pWin0 = &win0; // de winuri (prin alegerea sa) ale fiecare jucator.
    scanf("%d %d", &n, &m);
    citire_erori_macro(n, m, board, macroboard, pX, p0);
    afisare_macro(n, macroboard);
    macro_aux(n, aux, macroboard);
    who_won(n, aux);
    wins_per_person(n, macroboard, pWinX, pWin0);
    attention(winX, contorX, win0, contor0);
return 0;
}
