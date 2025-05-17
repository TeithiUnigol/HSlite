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

Jatekos *GameManager::JatekosKivalaszt(int j)
{
    if (j == 0)
    {
        return &j1;
    }
    else
    {
        return &j2;
    }
}

GameManager::GameManager(size_t screenW, size_t blokkW,size_t blokkH, size_t separatorS, std::string pakliforras, std::string GameForras)
    : screenW(screenW), blokkW(blokkW),blokkH(blokkH), separatorS(separatorS) {}
GameManager::GameManager(const Jatekos &jat1, const Jatekos &jat2, size_t screenW, size_t blokkW,size_t blokkH, size_t separatorS)
    : j1(jat1), j2(jat2), kurz(&j1, &j2), screenW(screenW), blokkW(blokkW),blokkH(blokkH), separatorS(separatorS) {}

//------------UI rész--------------
void GameManager::bossKartya(int jatekos, int startY)
{
    int fal = (screenW - blokkW) / 2;
    int y = startY;
    changeBG(black);
    changeTxt(white);
    econio_clrscr();
    printUresKartya(fal,3,startY);
    Boss &b = JatekosKivalaszt(jatekos)->Getboss();
    econio_gotoxy((screenW / 2) - 1, ++y);
    b.ikonKiir(cout);

    
    size_t nevM = b.nevMeret();
    if (nevM < (blokkW - 2))
    {
        econio_gotoxy(fal + (blokkW - nevM) / 2, ++y);
        if (kurz.getMov().szint == jatekos * 3)
        {
            changeBG(green);
        }
        else if (kurz.getSel1().szint == jatekos * 3)
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
        econio_gotoxy(fal + blokkW - 1, y);
    }
    else
    {
        econio_gotoxy(fal, y+3);
        if (kurz.getMov().szint == jatekos * 3)
        {
            changeBG(green);
        }
        else if (kurz.getSel1().szint == jatekos * 3)
        {
            changeBG(yellow);
        }
        if (!b.getAktiv())
        {
            changeTxt(gray);
        }
        b.nevKiir(std::cout, blokkW - 2);
        changeTxt(white);
        changeBG(black);
    }
    ++y;
    
}

void GameManager::printUresKartya(int xBehuz, int yMeret,int yKezd)
{
    int y = yKezd;
    felsoVonal(xBehuz, y++);
    belsoFal(xBehuz,y++);
    felsoVonal(xBehuz, y++);
    for (size_t i = 0; i < yMeret; i++)
    {
        belsoFal(xBehuz,y++);
    }
    felsoVonal(xBehuz, y++);
}

void GameManager::felsoVonal(int xBehuz, int yKezd)
{
    econio_gotoxy(xBehuz, yKezd);
    for (size_t i = 0; i < blokkW; ++i)
    {
        cout << "-";
    }
}
void GameManager::belsoFal(int behuzasX, int yKezd)
{
    econio_gotoxy(behuzasX, yKezd);
    cout << "|";
    econio_gotoxy(behuzasX + blokkW - 1, yKezd);
    cout << "|";
}
/*

void GameManager::taroloVonal(size_t fal, size_t cap)
{
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
        if (i != cap - 1)
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
        else if (kurz.getSel1().szint == jatekos * 3)
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
    // bossSzel(blokkW - 5 - intHossz(n), fal);
    cout << std::endl;
    bossvonal();
    falBelso = (blokkW - 3) / 2;
    bossSzel(fal, 0);
    n = aktJ->Getboss().getSpecial();
    cout << "Sp:" << n;
    // bossSzel(blokkW - 5 - intHossz(n), fal);
    cout << std::endl;
    bossvonal();
    cout << std::endl;
}
*/
void printPakli(KartyaTarolo pakli);

void GameManager::printKartyak(KartyaTarolo &k)
{
}
void GameManager::printMinion(KartyaTarolo &m)
{
    size_t meret = m.getKapacitas();
    size_t fal = (screenW - (blokkW * meret + separatorS * (meret - 1))) / 2;
    //taroloVonal(fal, meret);
}
void GameManager::printGame()
{
    changeBG(black);
    changeTxt(white);
    econio_clrscr();
    if (jatekos == 0)
    {
        changeBG(green);
    }
    econio_gotoxy(0,0);
    cout << "Jatekos 1";
    changeBG(black);
    econio_gotoxy(0,1);
    cout << "Mana: " << j1.getMana() << std::endl;

    bossKartya(0,2);
    cout << j1.getTarolo(TaroloTipus::Minionok).getKapacitas() << std::endl;
    // printMinion(j1->getTarolo(TaroloTipus::Minionok));
    for (size_t i = 0; i < screenW; i++)
    {
        cout << "-";
    }
    cout << std::endl;

    //printBoss(1);
    cout << "Mana: " << j2.getMana() << std::endl;
    if (jatekos == 1)
    {
        changeBG(green);
    }

    cout << "Jatekos 2";
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
        else
        {
            if (fazis == 1)
            {
                JatekosKivalaszt(jatekos)->getTarolo(TaroloTipus::Kez).kihuz(kurz.getSel1().index);
            }
            else
            {
                switch (kurz.getMov().szint)
                {
                case 0:
                    if (j1.Getboss().getElet() == 0)
                    {
                        isJatek = false;
                    }

                    break;
                case 1:
                    if (j1.getTarolo(TaroloTipus::Kez).kihuz(kurz.getSel1().index)->getElet() == 0)
                    {
                        JatekosKivalaszt(0)->getTarolo(TaroloTipus::Minionok).kihuz(kurz.getSel1().index);
                    }
                    break;
                case 2:
                    if (j1.getTarolo(TaroloTipus::Kez).kihuz(kurz.getSel1().index)->getElet() == 0)
                    {
                        JatekosKivalaszt(0)->getTarolo(TaroloTipus::Minionok).kihuz(kurz.getSel1().index);
                    }
                    break;
                case 3:

                    break;

                default:
                    break;
                }
            }
            kurz.getSel1().pointer = nullptr;
            kurz.getMov().pointer = nullptr;
        }
    }
}

bool GameManager::endGameScreen(int gyoz)
{
    econio_clrscr();
    changeTxt(white);
    changeBG(black);

    if (gyoz == 0)
    {
        cout << "Jatekos 1 gyozott\n";
    }
    else
    {
        cout << "Jatekos 2 gyozott\n";
    }
    cout << "Uj jatek inditasa: E gomb, Kilepes: X gomb";
    int isRunning = 1;
    int input;
    while (isRunning)
    {
        if (econio_kbhit())
        {
            input = econio_getch();
            if (input == 'x')
            {
                econio_normalmode();
                return false;
            }
            else if (input == 'e')
            {
                return true;
            }
        }
    }
    return false;
}

void GameManager::kovFazis()
{
    kurz.getSel1().pointer = nullptr;
    fazis += 1;
    if (fazis == 3)
    {
        jatekos = (jatekos + 1) % 2;
        if (jatekos == 0)
        {
            kurz.getMov().szint = 0;
            j1.ujKor();
        }
        else
        {
            kurz.getMov().szint = 3;
            j2.ujKor();
        }
        fazis = 0;
    }
}

/*
void GameManager::savePakli()
{
    std::ofstream File(pakliFile);
    File << "J1 ";
    j2->mentes(File);

    File << "J2 ";
    j1->mentes(File);
    File << "END";
    File.close();
}*/

void GameManager::saveGame()
{
    std::ofstream File(mentesFile);

    File.close();
}
void GameManager::loadGame()
{
}

void GameManager::loadPakli()
{
    std::ifstream File("pakli.txt");

    std::string tipus;
    File >> tipus;

    cout << tipus;
    if (tipus == "J1")
    {
        size_t csomagmeret;
        size_t minionokMeret;
        size_t kezMeret;
        int mana;
        size_t csomagindex = 0;
        if (!(File >> csomagmeret >> minionokMeret >> kezMeret >> mana))
        {
            throw "Helytelen bemenetfile";
        }
        KartyaTarolo kt(csomagmeret);

        Boss tempBoss;

        while (File >> tipus && tipus != "J2")
        {
            if (tipus == "MINION")
            {
                Minion *m = new Minion();
                m->betoltes(File);
                kt.berak(m, csomagindex);
                ++csomagindex;
                delete m;
            }
            else if (tipus == "BOSS")
            {
                tempBoss.betoltes(File);
            }
            else if (tipus == "VARAZSLAT")
            {
                Varazslat *v = new Varazslat();
                v->betoltes(File);
                kt.berak(v, csomagindex);
                ++csomagindex;

                delete v;
            }
        }
        Jatekos tempJatekos1(tempBoss, minionokMeret, kezMeret, kt, mana);
        j1 = tempJatekos1;
    }
    else
    {
        throw "Helytelen bemenetfile";
    }

    File.close();
}

GameManager::~GameManager()
{
    changeBG(black);
    changeTxt(white);
}

bool GameManager::game()
{
    econio_rawmode();
    isJatek = true;
    int input = 0;
    while (isJatek)
    {
        if (econio_kbhit())
        {
            input = econio_getch();
            switch (input)
            {
            case 27:  // escape
            case 'x': // b
                econio_normalmode();
                saveGame();
                return false;
                break;
            case -20:
            case 'w':
                // up
                kurz.lepes(irany::fel, fazis, jatekos, JatekosKivalaszt(jatekos));
                break;
            case -22:
            case 'a':
                // left
                kurz.lepes(irany::balra, fazis, jatekos, JatekosKivalaszt(jatekos));
                break;
            case -21:
            case 's':
                // down
                kurz.lepes(irany::le, fazis, jatekos, JatekosKivalaszt(jatekos));
                break;
            case -23:
            case 'd':
                // right
                kurz.lepes(irany::jobbra, fazis, jatekos, JatekosKivalaszt(jatekos));
                break;
            case 'l':
                kovFazis();
                break;
            case 'E':
                kivalaszt();
                break;
            default:
                break;
            }
        }
    }
    return false;
}
