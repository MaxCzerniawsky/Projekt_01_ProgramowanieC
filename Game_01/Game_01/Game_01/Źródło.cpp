#include <iostream>
#include "windows.h"
#include <conio.h>
#include <time.h> 
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void image() {
    gotoxy(0, 0);
    gotoxy(1, 1);

    //const int sz = 255;
    //char str[sz];

    FILE* fp;
    fp = fopen("Image.txt", "r");

    if (fp == NULL) {
        printf("The file is not opened.");
    }

    //while (fgets(str, sz, fp) != NULL) {
    //    printf("%s", str);
    //};

    Sleep(4000);
}

void ramka_ini(int w)
{

    int i;
    for (i = 1; i <= w; ++i) {
        gotoxy(0, 0);
        gotoxy(1, 1);
        //printf("                     `. ___\n");
        //printf("                    __,' __`.                _..----....___\n");
        //std::cout << "        __...--.'``;.   ,.   ;``--..__     .'    ,-._     " << std::endl;
        //std::cout << "  _..-''-------'   `'   `'   `'     O ``-''._   (,;') _,'" << std::endl;
        //std::cout << ",'________________                          \`-._`-','" << std::endl;
        //std::cout << " `._              ```````````------...___   '-.._'-:" << std::endl;
        //std::cout << "    ```--.._      ,.                     ````--...__\-." << std::endl;
        //std::cout << "            `.--. `-`                       ____    |  |`" << std::endl;
        //std::cout << "              `. `.                       ,'`````.  ;  ;`" << std::endl;
        //std::cout << "                `._`.        __________   `.      \'__/`" << std::endl;
        //std::cout << "                   `-:._____/______/___/____`.     \  `" << std::endl;
        //std::cout << "                               |       `._    `.    \ " << std::endl;
        //std::cout << "                               `._________`-.   `.   `." << std::endl;
        //std::cout << "                                             SSt  `------'`" << std::endl;
        //std::cout << "                           " << std::endl;
        std::cout << " Welcome to " << std::endl;
        std::cout << "           " << std::endl;
        std::cout << " DEEP SPACE" << std::endl;
        std::cout << "  " << std::endl;
        std::cout << " Loading in progress.." << std::endl;
        std::cout << "  " << std::endl;
  
        //ZWIEKSZAM CZAS OCZEKIWANIA
        Sleep(4000);

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


//POCISK
void ruch(int* x, int* y, int* vx, int* vy, int* xp, int* yp, int* vxp, int* gratrwa, int* xo, int* yo, int* vyo, int* p) {
    

    gotoxy(20, 1);
    printf("POINTS %d\n", *p);

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
        gotoxy(20, 1);
        printf("POINTS %d\n", *p);
    }
    if ((*y == *yp) && ((*x >= *xp) && (*x <= *xp + 6))){
        gotoxy(20, 1);
        printf("GAME OVER");
        gotoxy(20, 3);
        printf("Your total score is %d\n", *p);
        Sleep(2000);
        *gratrwa = 0;
    }
    
    if (*p > 19) {
        gotoxy(20, 1);
        printf("YOU HAVE REACHED THE EARTH");
        gotoxy(20, 3);
        printf("Your total score is %d\n", *p);
        Sleep(2000);
        *gratrwa = 0;
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

void outro(int* gratrwa) {
    gotoxy(40, 8);
    printf("            _____\n");
    printf("        ,-:` n;',`'-, \n");
    printf("      .'-;_,;  ':-;_,'.\n");
    printf("     /;   '/    ,  _`.-n \n");
    printf("    | '`. (`     /` ` n`|\n");
    printf("    |:.  `n`-.   n_   / |\n");
    printf("    |     (   `,  .`n ;'|\n");
    printf("     n     | .'     `-'/\n");
    printf("     `.   ;/        .'\n");
    printf("       `'-._____.\n");
    gotoxy(40, 20);
    printf("Earth...");
    gotoxy(40, 40);
    Sleep(2000);
    *gratrwa = 0;
}

int main() {
    int p = 0;
    srand(time(NULL));
    rnd();
    int x, y, vx = 1, vy = 1, i, xp = 5, yp = 20, vxp = 1, xo = 10, yo = 10, vyo = 2;
    x = 10; y = 10;
    char ch = ' ';
    int gratrwa = 1;
    image();
    ramka_ini(1);
    ramka_ini2(5);
    ramka();
    while ((ch != 'q') && (gratrwa == 1)) {
        ruch(&x, &y, &vx, &vy, &xp, &yp, &vxp, &gratrwa, &xo, &yo , &vyo, &p);
        ch = klawiatura(&vxp); 
        
    }
    outro(&gratrwa);
}
