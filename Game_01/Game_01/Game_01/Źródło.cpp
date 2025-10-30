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
    char znak;

    err = fopen_s(&plik, nazwa_obrazka, "r");
    if (err != 0 || plik == NULL) {
        printf("The file is not opened.");
    }

    while ((znak = fgetc(plik)) != EOF) {
        putchar(znak);
    }
    
    fclose(plik);

}

void ramka_ini(int w)
{
    image();
    int i;
    for (i = 1; i <= w; ++i) {
        


        gotoxy(0, 10);
        Sleep(1000);    
        std::cout << " Welcome to " << std::endl;
        std::cout << "           " << std::endl;
        Sleep(1000);
        std::cout << " DEEP SPACE" << std::endl;
        std::cout << "  " << std::endl;
        Sleep(1000);
        std::cout << " Loading in progress";
        Sleep(1000);
        std::cout << ".";
        Sleep(1000);
        std::cout << ".";

        Sleep(1000);

        for (int i = 25; i >= 0; i--) {
            gotoxy(1, i); printf("                                                          ");
            Sleep(50);
        }
    }
}


void ramka_ini2(int w)
{
    //PRZECHOWUJE HISTORIE INTRO JAKO LISTA
    char arr[6][50] = {"Space... the final frontier...", "In the deep space full of foes and enemies", "the lonely ship tries to find its way home", "facing many challenges", " ... ", "PRESS S TO START, SPACE TO MOVE THE SHIP"};

    int i;
    for (i = 0; i <= w; ++i) {
        gotoxy(0, 0);
        gotoxy(1, 1);

        printf("                                                          ");

        gotoxy(0, 0);
        gotoxy(1, 1);

        printf(arr[i]);

        if (i<5)
            Sleep(2000);

    }


    while (1) {
        char ch = _getch();  
        if (ch == 's') {
            break;  
        }
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
}

//GAMEPLAY


//RND
int rnd() {
    
    int max = 70;
    int min = 3;
    int r = (rand() % (max - min + 1)) + min;
    return r;
}

//ENERGY counter
void showPoints(int* p) {
    gotoxy(25, 1);
    const int punktyMax = 10;

    printf("WARP ENERGY LEVEL:");
    printf("[");
    // punkty_gorne[1]  //tab[1]
    // Wype�nione miejsca
    for (int i = 0; i < punktyMax; i++) {
        if (i < *p)
            printf("O");
        else
            printf("X");  // puste miejsce
    }

    printf("]\n");
}
//ganme endings

void outro(int* gratrwa) {
 
    gotoxy(0, 3);

    FILE* plik2;
    errno_t err;
    char nazwa_obrazka[] = "Image_end.txt";
    char znak;

    err = fopen_s(&plik2, nazwa_obrazka, "r");
    if (err != 0 || plik2 == NULL) {
        printf("The file is not opened.");
    }

    while ((znak = fgetc(plik2)) != EOF) {
        putchar(znak);
    }

    fclose(plik2);

    Sleep(2000);
    gotoxy(40, 40);
    *gratrwa = 0;
}

void gameOver(int *gratrwa, int *p) {
    outro(&*gratrwa);
    gotoxy(20, 15);
    printf("GAME OVER");
    gotoxy(20, 18);
    printf("Your total score is %d\n", *p);
    Sleep(4000);
    *gratrwa = 0;
}

void youWon(int* gratrwa, int* p) {
    outro(&*gratrwa);
    gotoxy(20, 15);
    printf("YOU HAVE REACHED THE EARTH");
    gotoxy(20, 18);
    printf("Your total score is %d\n", *p);
    Sleep(4000);
    *gratrwa = 0;
}


//Punkty do zbierania
void plansza(int ekran[80][20]) {
    int i, j;
    for (i = 0; i < 20; i++)
        for (j = 0; j < 70; j++) {
            ekran[j][i] = 0;
        }
    for (int i = 4; i < 6; i++)
        for (int j = 4; j < 70; j++) {
            ekran[j][i] = 2;
        }
    for (int i = 15; i < 16; i++)
        for (int j = 40; j < 70; j++) {
            ekran[j][i] = 1;
        }
}

//STAEK, PRZECIWNICY, ENERGY
void ruch(int* x, int* y, int* vx, int* vy, int* xp, int* yp, int* vxp, int* gratrwa, int* xo, int* yo, int* vyo, int* p) {
    

    char ch = ' ';

    gotoxy(*x, *y); printf("XXX");
    gotoxy(*xp, *yp); printf("-(-O-)-");
    Sleep(20);
    gotoxy(*xo, *yo); printf("O");
    Sleep(10);
    gotoxy(*x, *y); printf("   ");
    gotoxy(*xp, *yp); printf("       ");
    gotoxy(*xo, *yo); printf(" ");


    *y = *y + *vy;
    if (*y > 23) {
        *y = 2;
        *x = rnd();
    }
    *yo = *yo + *vyo;
    if (*yo > 23) {
        *yo = 2;
        *xo = rnd();
    }

    *xp = *xp + *vxp;
    if ((*xp > 64) || (*xp < 3)) *vxp = -(*vxp);
    if ((*yo == *yp) && ((*xo >= *xp) && (*xo <= *xp + 6))) {
        (*p)++;
        showPoints(&*p);

    }
    if ((*y == *yp) && ((*x >= *xp) && (*x <= *xp + 6))){
        gameOver(&*gratrwa, &*p);

    }
    
    if (*p > 9) {
        youWon(&*gratrwa, &*p);
    }

}

char klawiatura(int* vxp) {
    char ch = ' ';
    while (_kbhit()) {
        ch = _getch();
        if (ch == ' ') *vxp = -(*vxp);
    }
    return ch;
}

void menu() {
    printf("******* DEEP SPACE ******** \n");
    printf("\n");
    printf("1 - Name \n");
    printf("2 - Raport \n");
    printf("3 - Play \n");
    printf("4 - Exit \n");
    printf("5 - RESET \n");
    printf("6 - Read data \n");
    printf("\n");
    printf("Press number to choose option");
}

void gra() {
    int p = 0;
    srand(time(NULL));
    rnd();
    int x, y, vx = 1, vy = 1, i, xp = 5, yp = 20, vxp = 1, xo = 10, yo = 10, vyo = 2;
    x = 10; y = 10;
    char ch = ' ';
    int gratrwa = 1;

    
    
    ramka();
    int ekran[80][20];
    plansza(ekran);

    while ((ch != 'q') && (gratrwa == 1)) {


        ruch(&x, &y, &vx, &vy, &xp, &yp, &vxp, &gratrwa, &xo, &yo, &vyo, &p);
        ch = klawiatura(&vxp);

    }

}

int main() {
   
    char choice;

    ramka_ini(1);

    int r = 1;
    while (r == 1) {
        menu();
        scanf_s("%c", &choice);
        system("CLS");

        switch (choice)
        {
        case('1'):
            break;
        case('2'):
            break;
        case('3'): 
        {
            gra();
            break;
        }
        case('4'):
            r = 0;
            break;
        default:
            break;
        }
    }



}

// korekta: tablica ma by� ze wskazywaniem konkretnego indeksu, menu odpalane casami, wprowadzanie imienia, pi�ka ma sie odbijac od paletki, pi�ki maj� by� w funkcji, kilka pi�eczek
