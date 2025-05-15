#include "GameManager.h"

void changeBG(colors color)
{
    switch (color)
    {
    case white:
        econio_textbackground(COL_WHITE);
        break;
    case black:
        econio_textbackground(COL_BLACK);
        break;
    case red:
        econio_textbackground(COL_RED);
        break;
    case green:
        econio_textbackground(COL_GREEN);
        break;
    case gray:
        econio_textbackground(COL_LIGHTGRAY);
        break;
    }
}

void changeTxt(colors color)
{
    switch (color)
    {
    case white:
        econio_textcolor(COL_WHITE);
        break;
    case black:
        econio_textcolor(COL_BLACK);
        break;
    case red:
        econio_textcolor(COL_RED);
        break;
    case green:
        econio_textcolor(COL_GREEN);
        break;
    case gray:
        econio_textcolor(COL_LIGHTGRAY);
        break;
    }
}

void printMinionDeck(int size, KartyaTarolo k);

void GameManager::printBoss(Boss b){
    
}

void printPakli(KartyaTarolo pakli);



/*
econio_rawmode();
    int isRunning = 1;
    int input = 0;
    ListChunk *lastVisited = last;
    printMaze(matrix, size, lastVisited->coordinates, startingPoint);
    availableDirections(matrix, lastVisited->coordinates);
    printf("Kilepeshez nyomd meg az escape vagy b billentyut\n");
    while (isRunning) {
        if (econio_kbhit()) {
            input = econio_getch();
            coordinates currentPos = lastVisited->coordinates;
            switch (input) {
                case 27: //escape
                case 'b': //b
                    econio_normalmode();
                    isRunning = 0;
                    break;
                case -20:
                case 'w':
                    //up
                    if (currentPos.y == 0 && currentPos.x == startingPoint) {
                        printColorLine("Nem lehet kimenni a bejaraton",COL_YELLOW);
                        econio_sleep(0.75);
                    } else if (currentPos.y > 0 && canGoThere(matrix, currentPos, (coordinates){0, 1})) {
                        currentPos.y = currentPos.y - 1;
                        lastVisited = addNewCoordinate(lastVisited, currentPos);
                    }
                    break;
                case -22:
                case 'a':
                    //left
                    if (currentPos.x > 0 && canGoThere(matrix, currentPos, (coordinates){-1, 0})) {
                        currentPos.x = currentPos.x - 1;
                        lastVisited = addNewCoordinate(lastVisited, currentPos);
                    }
                    break;
                case -21:
                case 's':
                    //down
                    if (canGoThere(matrix, currentPos, (coordinates){0, -1})) {
                        currentPos.y = currentPos.y + 1;
                        if (currentPos.y == size.y) {
                            printColorLine("Gratulalok! Kijutottal a labirintusbol",COL_GREEN);
                            econio_sleep(1);
                            return lastVisited;
                        }else {
                            lastVisited = addNewCoordinate(lastVisited, currentPos);
                        }
                    }
                    break;
                case -23:
                case 'd':
                    //right
                    if (canGoThere(matrix, currentPos, (coordinates){1, 0})) {
                        currentPos.x = currentPos.x + 1;
                        lastVisited = addNewCoordinate(lastVisited, currentPos);
                    }
                    break;
                default:
                    break;
            }
            printMaze(matrix, size, lastVisited->coordinates, startingPoint);
            availableDirections(matrix, lastVisited->coordinates);
            printf("Kilepeshez nyomd meg az escape vagy b billentyut\n");
        }
    }
    return lastVisited;*/