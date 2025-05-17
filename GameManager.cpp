#include "GameManager.h"

using std::cout;
void GameManager::changeBG(colors color)
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
    case yellow:
        econio_textbackground(COL_YELLOW);
        break;
    }
}

void GameManager::changeTxt(colors color)
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
        case yellow:
        econio_textcolor(COL_YELLOW);
        break;
    }
}

size_t GameManager::intHossz(int n)
{
    if (n == 0)
    {
        return 0;
    }
    else
    {
        return floor(log10(n)) + 1;
    }
}

Jatekos *GameManager::JatekosKivalaszt(int j)
{
    if (j == 0)
    {
        return j1;
    }
    else
    {
        return j2;
    }
}

GameManager::GameManager(size_t screenW, size_t blokkW, size_t separatorS)
    : screenW(screenW), blokkW(blokkW), separatorS(separatorS) {}
GameManager::GameManager(Jatekos *jat1, Jatekos *jat2, size_t screenW, size_t blokkW, size_t separatorS)
    : j1(jat1), j2(jat2), kurz(j1, j2), screenW(screenW), blokkW(blokkW), separatorS(separatorS) {}

//------------UI rész--------------
void GameManager::bossKartya(int jatekos,int startY){
    int fal = (screenW - blokkW) / 2;
    int y = startY;
    econio_gotoxy(fal,y);
    changeBG(black);
    changeTxt(white);
    for (size_t i = 0; i < blokkW; ++i)
    {
        cout << "-";
    }
    econio_gotoxy(fal,++y);

    Boss& b = JatekosKivalaszt(jatekos)->Getboss();

    cout << "|";
    econio_gotoxy((screenW/2)-1,y);
    b.ikonKiir(cout);
    econio_gotoxy(fal+blokkW-1,y);
    cout << "|";

    econio_gotoxy(fal,++y);
    cout << "|";
    size_t nevM = b.nevMeret();
    if (nevM < (blokkW - 2))
    {
        econio_gotoxy(fal+(blokkW-nevM)/2,y);
        if (kurz.getMov().szint == jatekos * 3)
        {
            changeBG(green);
        }
        else if (kurz.getSel1().szint==jatekos*3)
        {
            changeBG(yellow);
        }
        if (b.getAktiv())
        {
            changeTxt(gray);
        }
        b.nevKiir(std::cout, blokkW - 2);
        changeTxt(white);
        changeBG(black);
        econio_gotoxy(fal+blokkW-1,y);
    }
    else
    {
        econio_gotoxy(fal,y);
        if (kurz.getMov().szint == jatekos * 3)
        {
            changeBG(green);
        }
        if (b.getAktiv())
        {
            changeTxt(gray);
        }
        b.nevKiir(std::cout, blokkW - 2);
        changeTxt(white);
        changeBG(black);
        econio_gotoxy(fal+blokkW-1,y);
    }
    cout << "|";
    econio_gotoxy(fal,++y);
    for (size_t i = 0; i < blokkW; ++i)
    {
        cout << "-";
    }
    econio_gotoxy(fal,++y);

}

void GameManager::bossvonal()
{
    for (size_t i = 0; i < (screenW - blokkW) / 2; i++)
    {
        cout << " ";
    }

    for (size_t i = 0; i < blokkW; i++)
    {
        cout << "-";
    }
    for (size_t i = 0; i < (screenW - blokkW) / 2; i++)
    {
        cout << " ";
    }
    cout << std::endl;
}

void GameManager::taroloVonal(size_t fal,size_t cap){
    for (size_t i = 0; i < fal; i++)
    {
        cout << " ";
    }
    for (size_t i = 0; i < cap; i++)
    {
        for (size_t i = 0; i < blokkW; i++)
        {
            cout << "-";
        }
        if (i!=cap-1)
        {   
            for (size_t i = 0; i < separatorS; i++)
            {
                cout << " ";
            }
        }
    }
    for (size_t i = 0; i < fal; i++)
    {
        cout << " ";
    }
    
    
}

void GameManager::bossSzel(size_t s1, size_t s2)
{

    for (size_t i = 0; i < s1; i++)
    {
        cout << " ";
    }
    cout << "|";
    for (size_t i = 0; i < s2; i++)
    {
        cout << " ";
    }
}
void GameManager::printBoss(int jatekos)
{
    changeBG(black);
    changeTxt(white);
    size_t fal = (screenW - blokkW) / 2;
    size_t falBelso;

    // kártya teteje
    bossvonal();

    Jatekos *aktJ = JatekosKivalaszt(jatekos);

    // boss ikon kiírása
    falBelso = (blokkW - 3) / 2;
    bossSzel(fal, falBelso);
    aktJ->Getboss().ikonKiir(std::cout);
    bossSzel(falBelso, fal);
    cout << std::endl;

    size_t nevM = aktJ->Getboss().nevMeret();
    // boss nevének kiírása

    if (nevM < (blokkW - 2))
    {
        bossSzel(fal, (blokkW - nevM - 2) / 2);
        if (kurz.getMov().szint == jatekos * 3)
        {
            changeBG(green);
        }
        else if (kurz.getSel1().szint==jatekos*3)
        {
            changeBG(yellow);
        }
        if (!aktJ->Getboss().getAktiv())
        {
            changeTxt(gray);
        }
        aktJ->Getboss().nevKiir(std::cout, blokkW - 2);
        changeTxt(white);
        changeBG(black);
        bossSzel((blokkW - nevM - 2) / 2, fal);
    }
    else
    {
        bossSzel(fal, 0);
        if (kurz.getMov().szint == jatekos * 3)
        {
            changeBG(green);
        }
        if (!aktJ->Getboss().getAktiv())
        {
            changeTxt(gray);
        }
        aktJ->Getboss().nevKiir(std::cout, blokkW - 2);
        changeTxt(white);
        changeBG(black);
        bossSzel(0, fal);
    }
    cout << std::endl;

    falBelso = (blokkW - 3) / 2;
    bossSzel(fal, 0);
    int n = aktJ->Getboss().getElet();
    cout << "Hp:" << n;
    bossSzel(blokkW - 5 - intHossz(n), fal);
    cout << std::endl;
    bossvonal();
    falBelso = (blokkW - 3) / 2;
    bossSzel(fal, 0);
    n = aktJ->Getboss().getSpecial();
    cout << "Sp:" << n;
    bossSzel(blokkW - 5 - intHossz(n), fal);
    cout << std::endl;
    bossvonal();
    cout << std::endl;
}

void printPakli(KartyaTarolo pakli);

void GameManager::printKartyak(KartyaTarolo &k)
{

}
void GameManager::printMinion(KartyaTarolo &m)
{
    size_t meret = m.getKapacitas();
    size_t fal = (screenW-(blokkW*meret+separatorS*(meret-1)))/2;
    taroloVonal(fal,meret);
}
void GameManager::printGame()
{
    changeBG(black);
    changeTxt(white);
    econio_clrscr();
    if (jatekos==0)
    {
        changeBG(green);
    }
    
    cout<<"Jatekos 1\n";
    changeBG(black);
    
    cout<<"Mana: "<<j1->getMana()<<std::endl;

    printBoss(0);
    cout<<j1->getTarolo(TaroloTipus::Minionok).getKapacitas()<<std::endl;
    //printMinion(j1->getTarolo(TaroloTipus::Minionok));
    for (size_t i = 0; i < screenW; i++)
    {
        cout<<"-";
    }
    cout<<std::endl;
    
    printBoss(1);
    cout<<"Mana: "<<j2->getMana()<<std::endl;
    if (jatekos==1)
    {
        changeBG(green);
    }
    
    cout<<"Jatekos 2";
    changeBG(black);

}

//------------Játéklogika--------------
void GameManager::kivalaszt()
{
    if (kurz.getSel1().pointer == nullptr)
    {
        kurz.getSel1().pointer = kurz.getMov().pointer;
    }
    else
    {
        if (!JatekosKivalaszt(jatekos)->Kijatszas(kurz.getSel1().pointer, kurz.getMov().pointer))
        {
            econio_clrscr();
            changeTxt(red);
            cout << "helytelen";
        }

        kurz.getSel1().pointer = nullptr;
        kurz.getMov().pointer = nullptr;
    }
}

void GameManager::kovFazis(int fazis)
{
    kurz.getSel1().pointer = nullptr;
    fazis += 1;
    if (fazis == 3)
    {
        jatekos = (jatekos + 1) % 2;
        if (jatekos == 0)
        {
            kurz.getMov().szint = 0;
            j1->ujKor();
        }
        else
        {
            kurz.getMov().szint = 3;
            j2->ujKor();
        }
    }
}

void GameManager::loadPakli(char *fileName)
{
    std::ofstream File("filename.txt");

    File.close();
}
void GameManager::savePakli(char *fileName)
{
    std::ofstream File("filename.txt");

    File.close();
}

GameManager::~GameManager()
{
    changeBG(black);
    changeTxt(white);
}

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
