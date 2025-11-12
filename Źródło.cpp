#include <iostream>
#include "windows.h"
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

using namespace std;


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void image() {
    gotoxy(0, 0);
    gotoxy(1, 1);

    FILE* plik;
    errno_t err;
    char nazwa_obrazka[] = "Image.txt";
    int znak;

    err = fopen_s(&plik, nazwa_obrazka, "r");
    if (err != 0 || plik == NULL) {
        printf("The file is not opened.\n");
        return;
    }

    while ((znak = fgetc(plik)) != EOF) {
        putchar(znak);
    }

    fclose(plik);
}

void clean() {
    for (int i = 25; i >= 0; i--) {
        gotoxy(0, i);
        printf("                                                                                     ");
        Sleep(50);
    }
}

void ramka_ini(int w) {
    image();
    for (int i = 1; i <= w; ++i) {
        gotoxy(0, 10);
        Sleep(1000);
        cout << " Welcome to " << endl;
        cout << endl;
        Sleep(1000);
        cout << " DEEP SPACE" << endl;
        cout << endl;
        Sleep(1000);
        cout << " Loading in progress";
        Sleep(1000);
        cout << ".";
        Sleep(1000);
        cout << ".";
        Sleep(1000);

    }
}

void ramka() {
    char aa;
    aa = 218; gotoxy(1, 1); printf("%c", aa);
    aa = 191; gotoxy(80, 1); printf("%c", aa);
    aa = 192; gotoxy(1, 24); printf("%c", aa);
    aa = 217; gotoxy(80, 24); printf("%c", aa);
    aa = 196;
    for (int i = 2; i < 80; i++) {
        gotoxy(i, 1); printf("%c", aa);
        gotoxy(i, 24); printf("%c", aa);
    }
    aa = 179;
    for (int i = 2; i < 24; i++) {
        gotoxy(1, i); printf("%c", aa);
        gotoxy(80, i); printf("%c", aa);
    }
    gotoxy(2, 25);
    printf("Space changes direction, S stops, R runs, P adds up to 3 balls");
}



int rnd() {
    int max = 70;
    int min = 3;
    int r = (rand() % (max - min + 1)) + min;
    return r;
}

// pasek energii
void showPoints(int* p) {
    gotoxy(15, 1);
    const int punktyMax = 20;

    printf("WARP ENERGY LEVEL:");
    printf("[");
    for (int i = 0; i < punktyMax; i++) {
        if (i < *p)
            printf("O");
        else
            printf("X");
    }
    printf("]\n");
}

// outro / zakoñczenia
void outro(int* gratrwa) {
    gotoxy(0, 3);

    FILE* plik2;
    errno_t err;
    char nazwa_obrazka[] = "Image_end.txt";
    int znak;

    err = fopen_s(&plik2, nazwa_obrazka, "r");
    if (err != 0 || plik2 == NULL) {
        printf("The file is not opened.\n");
        return;
    }

    while ((znak = fgetc(plik2)) != EOF) {
        putchar(znak);
    }

    fclose(plik2);
    Sleep(2000);
    gotoxy(40, 40);
    //*gratrwa = 0;
}

void gameOver(int* gratrwa, int* p) {
    clean();
    outro(gratrwa);
    gotoxy(20, 15);
    printf("GAME OVER");
    gotoxy(20, 18);
    printf("Your total score is %d\n", *p);
    Sleep(4000);
    //*gratrwa = 0;
}

void youWon(int* gratrwa, int* p) {
    clean();
    outro(gratrwa);
    gotoxy(20, 15);
    printf("YOU HAVE REACHED THE EARTH");
    gotoxy(20, 18);
    printf("Your total score is %d\n", *p);
    Sleep(4000);
    //*gratrwa = 0;
}

// Funkcja do rysowania bloków na planszy
void rysujBloki(int ekran[80][20]) {
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 80; x++) {
            if (ekran[x][y] == 1) {
                gotoxy(x + 2, y + 2);
                printf("#");
            }
        }
    }
}

void plansza(int ekran[80][20]) {
    // Inicjalizacja ekranu - tylko przy pierwszym wywo³aniu
    static bool pierwsze_wywolanie = true;
    if (pierwsze_wywolanie) {
        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 80; x++) {
                ekran[x][y] = 0;
            }
        }
        pierwsze_wywolanie = false;
    }

    int offsetX = 25;  // przesuniêcie w poziomie 
    int offsetY = 3;   // przesuniêcie w pionie 

    // Linia 1
    for (int x = 0; x < 8; x++) {
        ekran[offsetX + x][offsetY + 0] = 1;
    }

    // Linia 2
    for (int x = 4; x < 8; x++) {
        ekran[offsetX + x][offsetY + 1] = 1;
    }

    // Linia 3
    for (int x = 0; x < 8; x++) {
        ekran[offsetX + x][offsetY + 2] = 1;
    }

    rysujBloki(ekran);
}




// ruch statku / kolizje
void ruch(int* x, int* y, int* vx, int* vy, int* xp, int* yp, int* vxp,
    int* gratrwa, int* p, int W, int H, int ekran[80][20], int* pilka, int* x2, int* y2, int* vx2, int* vy2, int* x3, int* y3, int* vx3, int* vy3) {

    // Usuñ poprzednie pozycje TYLKO aktywnych pi³ek
    gotoxy(*x, *y); printf(" ");
    if (*pilka >= 2 && *y2 < H) {  // Druga pi³ka tylko jeœli nie spad³a
        gotoxy(*x2, *y2); printf(" ");
    }
    if (*pilka >= 3 && *y3 < H) {  // Trzecia pi³ka tylko jeœli nie spad³a
        gotoxy(*x3, *y3); printf(" ");
    }
    gotoxy(*xp, *yp); printf("       ");

    int nextX = *x + *vx;
    int nextY = *y + *vy;
    int nextX2 = *x2 + *vx2;
    int nextY2 = *y2 + *vy2;
    int nextX3 = *x3 + *vx3;
    int nextY3 = *y3 + *vy3;

    // Odbicia od œcian dla PIERWSZEJ pi³ki (tylko jeœli nie spad³a)
    if (*y < H) {
        if (nextX <= 2 || nextX >= W - 2) *vx = -*vx;
        if (nextY <= 2) *vy = -*vy;
    }

    // Odbicia od œcian dla DRUGIEJ pi³ki (tylko jeœli istnieje i nie spad³a)
    if (*pilka >= 2 && *y2 < H) {
        if (nextX2 <= 2 || nextX2 >= W - 2) *vx2 = -*vx2;
        if (nextY2 <= 2) *vy2 = -*vy2;
    }

    // Odbicia od œcian dla TRZECIEJ pi³ki (tylko jeœli istnieje i nie spad³a)
    if (*pilka >= 3 && *y3 < H) {
        if (nextX3 <= 2 || nextX3 >= W - 2) *vx3 = -*vx3;
        if (nextY3 <= 2) *vy3 = -*vy3;
    }

    // SprawdŸ kolizje w nowej pozycji
    bool kolizja = false;

    // SprawdŸ kolizjê z blokami dla PIERWSZEJ pi³ki (tylko jeœli nie spad³a)
    if (*y < H) {
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                int checkX = nextX + dx;
                int checkY = nextY + dy;

                if (checkX >= 0 && checkX < 80 && checkY >= 0 && checkY < 20) {
                    if (ekran[checkX][checkY] == 1) {
                        ekran[checkX][checkY] = 0;  // usuñ bloczek
                        gotoxy(checkX + 2, checkY + 2); printf(" "); // usuñ z ekranu
                        kolizja = true;
                        (*p)++; // dodaj punkt
                        showPoints(p);
                    }
                }
            }
        }
    }

    // SprawdŸ kolizjê z blokami dla DRUGIEJ pi³ki (tylko jeœli istnieje i nie spad³a)
    if (*pilka >= 2 && *y2 < H) {
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                int checkX2 = nextX2 + dx;
                int checkY2 = nextY2 + dy;

                if (checkX2 >= 0 && checkX2 < 80 && checkY2 >= 0 && checkY2 < 20) {
                    if (ekran[checkX2][checkY2] == 1) {
                        ekran[checkX2][checkY2] = 0;  // usuñ bloczek
                        gotoxy(checkX2 + 2, checkY2 + 2); printf(" "); // usuñ z ekranu
                        kolizja = true;
                        (*p)++; // dodaj punkt
                        showPoints(p);
                    }
                }
            }
        }
    }

    // SprawdŸ kolizjê z blokami dla TRZECIEJ pi³ki (tylko jeœli istnieje i nie spad³a)
    if (*pilka >= 3 && *y3 < H) {
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                int checkX3 = nextX3 + dx;
                int checkY3 = nextY3 + dy;

                if (checkX3 >= 0 && checkX3 < 80 && checkY3 >= 0 && checkY3 < 20) {
                    if (ekran[checkX3][checkY3] == 1) {
                        ekran[checkX3][checkY3] = 0;  // usuñ bloczek
                        gotoxy(checkX3 + 2, checkY3 + 2); printf(" "); // usuñ z ekranu
                        kolizja = true;
                        (*p)++; // dodaj punkt
                        showPoints(p);
                    }
                }
            }
        }
    }

    // Jeœli by³a kolizja, odbij tylko odpowiednie pi³ki (które nie spad³y)
    if (kolizja) {
        if (*y < H) {
            *vx = -*vx;
            *vy = -*vy;
        }
        if (*pilka >= 2 && *y2 < H) {
            *vx2 = -*vx2;
            *vy2 = -*vy2;
        }
        if (*pilka >= 3 && *y3 < H) {
            *vx3 = -*vx3;
            *vy3 = -*vy3;
        }
        // Po odbiciu przelicz now¹ pozycjê
        nextX = *x + *vx;
        nextY = *y + *vy;
        if (*pilka >= 2 && *y2 < H) {
            nextX2 = *x2 + *vx2;
            nextY2 = *y2 + *vy2;
        }
        if (*pilka >= 3 && *y3 < H) {
            nextX3 = *x3 + *vx3;
            nextY3 = *y3 + *vy3;
        }
    }

    // Aktualizuj pozycje tylko pi³ek które nie spad³y
    if (*y < H) {
        *x = nextX;
        *y = nextY;
    }
    if (*pilka >= 2 && *y2 < H) {
        *x2 = nextX2;
        *y2 = nextY2;
    }
    if (*pilka >= 3 && *y3 < H) {
        *x3 = nextX3;
        *y3 = nextY3;
    }

    // Ruch statku
    *xp += *vxp;

    // Odbicia statku od œcian
    if (*xp <= 2) { *xp = 2; *vxp = -*vxp; }
    if (*xp >= W - 8) { *xp = W - 8; *vxp = -*vxp; }

    // Kolizja pi³ki ze statkiem (tylko dla pi³ek które nie spad³y)
    if (*y < H && (*y == *yp - 1) && (*x >= *xp) && (*x <= *xp + 7)) {
        *vy = -*vy;
    }
    if (*pilka >= 2 && *y2 < H && (*y2 == *yp - 1) && (*x2 >= *xp) && (*x2 <= *xp + 7)) {
        *vy2 = -*vy2;
    }
    if (*pilka >= 3 && *y3 < H && (*y3 == *yp - 1) && (*x3 >= *xp) && (*x3 <= *xp + 7)) {
        *vy3 = -*vy3;
    }

    // Rysujemy tylko pi³ki które nie spad³y
    if (*y < H) {
        gotoxy(*x, *y); printf("O");
    }
    if (*pilka >= 2 && *y2 < H) {
        gotoxy(*x2, *y2); printf("O");
    }
    if (*pilka >= 3 && *y3 < H) {
        gotoxy(*x3, *y3); printf("O");
    }
    gotoxy(*xp, *yp); printf("=(=O=)=");

    // Wygrana / przegrana - gra koñczy siê gdy WSZYSTKIE pi³ki spadn¹
    bool wszystkie_pilki_spadly = true;

    if (*y < H) {  // Jeœli pierwsza pi³ka jest jeszcze na ekranie
        wszystkie_pilki_spadly = false;
    }
    if (*pilka >= 2 && *y2 < H) {  // Jeœli druga pi³ka jest jeszcze na ekranie
        wszystkie_pilki_spadly = false;
    }
    if (*pilka >= 3 && *y3 < H) {  // Jeœli trzecia pi³ka jest jeszcze na ekranie
        wszystkie_pilki_spadly = false;
    }

    if (wszystkie_pilki_spadly) {
        gameOver(gratrwa, p);
        *gratrwa = 0;
        return;
    }
    if (*p >= 20) {
        youWon(gratrwa, p);
        *gratrwa = 0;
        return;
    }

    Sleep(40);
}

char klawiatura(int* vxp, int* pilka) {
    char ch = ' ';
    while (_kbhit()) {
        ch = _getch();
        if (ch == ' ') *vxp = -(*vxp);
        if (ch == 's') *vxp = 0;
        if (ch == 'r') *vxp = 1;
        if (ch == 'p') {
            if (*pilka <= 3) {
                *pilka += 1;
            }
        }

    }
    return ch;
}

void gra(char tablica[20]) {
    int pilka = 1;
    int p = 0;
    // paletka
    int xp = 5, yp = 19, vxp = 1;
    //pilki 1, 2 i 3
    int x = 10, y = 10, vx = 1, vy = 1;
    int x2 = 14, y2 = 8, vx2 = 1, vy2 = 1;
    int x3 = 18, y3 = 6, vx3 = 1, vy3 = 1;

    int W = 80, H = 20;
    srand(time(NULL));
    char ch = ' ';
    int gratrwa = 1;

    int ekran[80][20];
    ramka();
    plansza(ekran);
    showPoints(&p);

    while ((ch != 'q') && (gratrwa == 1)) {
        ruch(&x, &y, &vx, &vy, &xp, &yp, &vxp, &gratrwa, &p, W, H, ekran, &pilka, &x2, &y2, &vx2, &vy2, &x3, &y3, &vx3, &vy3);
        ch = klawiatura(&vxp, &pilka);
    }


    if (gratrwa == 0) {

        Sleep(2000);
    }

    system("CLS");

    printf("\nReturning to main menu...\n");
    Sleep(1000);
    system("CLS");


}



void menu(const char* imieGracza) {

    clean();

    gotoxy(3, 5);
    printf("*");
    gotoxy(5, 5);
    if (imieGracza[0] == '\0' || imieGracza[0] == ' ') {
        printf("COMMANDER");  // domyœlna nazwa
    }
    else {
        printf("%s", imieGracza);
    }

    gotoxy(15, 5);
    printf("* \n");
    printf("\n");
    printf("    1 - Name \n");
    printf("    2 - Raport \n");
    printf("    3 - Play \n");
    printf("    4 - Exit \n");
    printf("    5 - RESET \n");
    printf("    6 - Read data \n");
    printf("\n");
    gotoxy(0, 0);
    ramka();
    gotoxy(4, 15);
    printf("    Press number to choose option");

}



int main() {
    struct dd {
        int p;
        char t[20];
    };
    dd rr;
    dd baza[30];

    FILE* stream = NULL;
    errno_t err;
    char tekst[20] = " ";
    char choice;
    int r = 1, i = 0;

    ramka_ini(1);
    system("CLS");

    while (r == 1) {
        menu(tekst);
        scanf_s(" %c", &choice, 1); // spacja przed %c usuwa znaki nowej linii
        system("CLS");

        switch (choice) {
        case('1'):
            gotoxy(25, 6); printf("Podaj imie -> ");
            scanf_s("%s", tekst, (unsigned)_countof(tekst));
            system("CLS");
            break;

        case('2'): {
            err = fopen_s(&stream, "data2.dat", "r");
            if (err != 0 || stream == NULL) {
                printf("Nie udalo sie otworzyc pliku data2.dat!\n");
                printf("Nacisnij dowolny przycisk...");
                while (!_kbhit()) {}
                break;
            }

            printf("=== RAPORT WYNIKOW ===\n\n");
            int liczba1;
            char temp_tekst[20];

            while (fscanf_s(stream, "%d %19s", &liczba1, temp_tekst, (unsigned)_countof(temp_tekst)) == 2) {
                printf("%d %s\n", liczba1, temp_tekst);
            }

            fclose(stream);
            printf("\nNacisnij dowolny przycisk...");
            while (!_kbhit()) {}
            break;
        }

        case('3'):
            gra(tekst);
            break;

        case('4'):
            r = 0;
            break;

        case('5'): {
            err = fopen_s(&stream, "data2.dat", "r");
            if (err != 0 || stream == NULL) {
                printf("Nie udalo sie otworzyc pliku data2.dat!\n");
                printf("Nacisnij dowolny przycisk...");
                while (!_kbhit()) {}
                break;
            }

            i = 0;
            while (fscanf_s(stream, "%d %19s", &baza[i].p, baza[i].t, (unsigned)_countof(baza[i].t)) == 2) {
                i++;
                if (i >= 30) break;
            }
            fclose(stream);

            printf("Przed sortowaniem:\n");
            for (int j = 0; j < i; j++) {
                printf("%d %s\n", baza[j].p, baza[j].t);
            }

            for (int k = 0; k < i - 1; k++) {
                for (int j = 0; j < i - k - 1; j++) {
                    if (baza[j].p < baza[j + 1].p) {
                        rr = baza[j];
                        baza[j] = baza[j + 1];
                        baza[j + 1] = rr;
                    }
                }
            }

            printf("\nPo sortowaniu:\n");
            for (int j = 0; j < i; j++) {
                printf("%d %s\n", baza[j].p, baza[j].t);
            }
            printf("\nNacisnij dowolny przycisk...");
            while (!_kbhit()) {}
            break;
        }

        default:
            break;
        }

        while (getchar() != '\n'); // czyœci bufor
    }

    return 0;
}