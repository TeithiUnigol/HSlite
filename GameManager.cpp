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

GameManager::GameManager(size_t screenW, size_t blokkW, size_t blokkH, size_t separatorS, std::string pakliforras, std::string GameForras)
    : screenW(screenW), blokkW(blokkW), blokkH(blokkH), separatorS(separatorS) {}
GameManager::GameManager(const Jatekos &jat1, const Jatekos &jat2, size_t screenW, size_t blokkW, size_t blokkH, size_t separatorS)
    : j1(jat1), j2(jat2), kurz(&j1, &j2), screenW(screenW), blokkW(blokkW), blokkH(blokkH), separatorS(separatorS) {}

//------------UI rész--------------
void GameManager::MenuSelect()
{
    econio_rawmode();
    changeBG(black);
    changeTxt(white);
    econio_clrscr();
    cout << "                       _         _                       __ _ _       \n  /\\  /\\___  __ _ _ __| |__  ___| |_ ___  _ __   ___    / /(_) |_ ___ \n / /_/ / _ \\/ _` | '__| '_ \\/ __| __/ _ \\| '_ \\ / _ \\  / / | | __/ _ \\\n/ __  /  __/ (_| | |  | | | \\__ \\ || (_) | | | |  __/ / /__| | ||  __/\n\\/ /_/ \\___|\\__,_|_|  |_| |_|___/\\__\\___/|_| |_|\\___| \\____/_|\\__\\___|\n                                                                      ";
    // bool selected1 = true;

    bool isKerdez = true;
    int input = 0;

    econio_gotoxy(0, 6);

    changeBG(green);
    cout << "Uj Jatek\n";
    changeBG(black);
    cout << "Betoltes\n";

    int kiv = 0;
    while (isKerdez)
    {
        if (econio_kbhit())
        {
            changeBG(black);
            changeTxt(white);
            econio_clrscr();
            cout << "                       _         _                       __ _ _       \n  /\\  /\\___  __ _ _ __| |__  ___| |_ ___  _ __   ___    / /(_) |_ ___ \n / /_/ / _ \\/ _` | '__| '_ \\/ __| __/ _ \\| '_ \\ / _ \\  / / | | __/ _ \\\n/ __  /  __/ (_| | |  | | | \\__ \\ || (_) | | | |  __/ / /__| | ||  __/\n\\/ /_/ \\___|\\__,_|_|  |_| |_|___/\\__\\___/|_| |_|\\___| \\____/_|\\__\\___|\n                                                                      ";
            input = econio_getch();
            switch (input)
            {
            case 27:  // escape
            case 'x': // b
                econio_normalmode();
                isKerdez = false;
                isJatek = true;
                break;
            case -20:
            case 'w':
                --kiv;
                kiv = kiv % 2;
                break;
            case -21:
            case 's':
                --kiv;
                if (kiv == -1)
                {
                    kiv = 1;
                }

                break;
            case 'E':
            case '\n':
            case '\r':
                if (kiv == 0)
                {
                    isKerdez = false;
                    loadPakli();
                    j1.kezfeltolt();
                    j2.kezfeltolt();
                    isJatek = true;

                    game();
                }
                else
                {
                    isKerdez = false;
                    loadGame();
                    // TODO
                }
                break;
            default:
                break;
            }
            econio_gotoxy(0, 6);
            if (kiv == 0)
            {
                changeBG(green);
                cout << "Uj Jatek\n";
                changeBG(black);
                cout << "Betoltes\n";
            }
            else
            {
                changeBG(black);
                cout << "Uj Jatek\n";
                changeBG(green);
                cout << "Betoltes\n";
                changeBG(black);
            }
        }
    }
    econio_clrscr();
}
/*
void GameManager::bossKartya(int jatekos, int startY)
{
    int fal = (screenW - blokkW) / 2;
    int y = startY;

    printUresKartya(fal, 3, startY);
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
        econio_gotoxy(fal, y + 3);
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
}*/

void GameManager::printUresKartya(int xBehuz, int yMeret, int yKezd)
{
    int y = yKezd;
    felsoVonal(xBehuz, y++);
    belsoFal(xBehuz, y++);
    belsoFal(xBehuz, y++);
    felsoVonal(xBehuz, y++);
    for (int i = 0; i < yMeret; i++)
    {
        belsoFal(xBehuz, y++);
    }
    felsoVonal(xBehuz, y++);
}

void GameManager::KartyaKiir(int xBehuz, int yKezd, Kartya *k, bool inkez, bool isSel, bool isMov)
{
    int y = yKezd;

    printUresKartya(xBehuz, blokkH, yKezd);
    econio_gotoxy(xBehuz + blokkW / 2, ++y);
    if (k != nullptr)
    {
        k->ikonKiir(cout);

        size_t nevM = k->nevMeret();
        if (nevM < (blokkW - 2))
        {
            econio_gotoxy(xBehuz + (blokkW - nevM) / 2, ++y);
            if (isMov)
            {
                changeBG(green);
            }
            else if (isSel)
            {
                changeBG(yellow);
            }
            if (!k->getAktiv())
            {
                changeTxt(gray);
            }
            k->nevKiir(std::cout, blokkW - 2);
            changeTxt(white);
            changeBG(black);
            econio_gotoxy(xBehuz + blokkW - 1, y++);
        }
        else
        {
            econio_gotoxy(xBehuz + 1, ++y);
            if (kurz.getMov().szint == jatekos * 3)
            {
                changeBG(green);
            }
            else if (kurz.getSel1().szint == jatekos * 3)
            {
                changeBG(yellow);
            }
            if (!k->getAktiv())
            {
                changeTxt(gray);
            }
            k->nevKiir(std::cout, blokkW - 2);
            changeTxt(white);
            changeBG(black);
            ++y;
        }
        ++y;
        k->tartalomkiir(xBehuz + 1, y, inkez);
    }
    else
    {
        econio_gotoxy(xBehuz + 1, ++y);
        if (isMov)
        {
            changeBG(green);
        }
        else if (isSel)
        {
            changeBG(yellow);
        }
        for (size_t i = 0; i < blokkW - 2; i++)
        {
            cout << " ";
        }
        changeTxt(white);
            changeBG(black);
    }
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
Korábbi próbálkozás, majd econiora váltottam
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
void GameManager::printTarolo(int yKezd, int yMeret, KartyaTarolo &tarolo, bool isKez, int melyikJatekose)
{
    size_t kap = tarolo.getKapacitas();
    int fal = ((screenW - kap * blokkW - (kap - 1) * separatorS) / 2);
    for (size_t i = 0; i < kap; i++)
    {

        if (fazis == 1 && isKez && melyikJatekose == jatekos)
        {
            if (kurz.getMov().index == i)
            {
                KartyaKiir(fal, yKezd, tarolo[i], isKez, false, true);
            }
            else if (kurz.getSel1().index)
            {
                KartyaKiir(fal, yKezd, tarolo[i], isKez, true, false);
            }
            else
            {
                KartyaKiir(fal, yKezd, tarolo[i], isKez, false, false);
            }
        }
        else if (fazis == 1 && !isKez)
        {
            if (kurz.getSel1().pointer != nullptr)
            {
                if (kurz.getMov().index == i && kurz.getMov().szint == melyikJatekose + 1)
                {
                    KartyaKiir(fal, yKezd, tarolo[i], isKez, false, true);
                }
                else
                {
                    KartyaKiir(fal, yKezd, tarolo[i], isKez, false, false);
                }
            }
            else
            {
                KartyaKiir(fal, yKezd, tarolo[i], isKez, false, false);
            }
        }
        else if (fazis == 2 && !isKez)
        {
            if (kurz.getMov().index == i && kurz.getMov().szint == melyikJatekose + 1)
            {
                KartyaKiir(fal, yKezd, tarolo[i], isKez, false, true);
            }
            else if (kurz.getSel1().index == i && kurz.getSel1().szint == melyikJatekose + 1)
            {
                KartyaKiir(fal, yKezd, tarolo[i], isKez, true, false);
            }
            else
            {

                KartyaKiir(fal, yKezd, tarolo[i], isKez, false, false);
            }
        }
        else
        {
            KartyaKiir(fal, yKezd, tarolo[i], isKez, false, false);
        }
        fal += blokkW + separatorS;
    }
}

void GameManager::printGame()
{
    int y = 0;
    changeBG(black);
    changeTxt(white);
    econio_clrscr();
    if (jatekos == 0)
    {
        changeBG(green);
    }
    econio_gotoxy(0, y++);
    cout << "Jatekos 1";
    changeBG(black);
    econio_gotoxy(0, y++);
    cout << "Mana: " << j1.getMana();

    // KartyaKiir((screenW - blokkW) / 2, y, &j1.Getboss(), false, kurz.getSel1().szint == 0, kurz.getMov().szint == 0);
    KartyaKiir((screenW - blokkW) / 2, y, &j1.Getboss(), false, false, false);

    y += 3 + 2 + blokkH;

    printTarolo(y, blokkH, j1.getTarolo(TaroloTipus::Kez), true, 0);
    y += 3 + 2 + blokkH;
    printTarolo(y, blokkH, j1.getTarolo(TaroloTipus::Minionok), false, 0);
    y += 3 + 2 + blokkH;
    // KartyaKiir(2,y,j1.getTarolo(TaroloTipus::Minionok)[0],false);

    econio_gotoxy(0, y++);
    for (size_t i = 0; i < screenW; i++)
    {
        cout << "-";
    }

    printTarolo(y, blokkH, j2.getTarolo(TaroloTipus::Minionok), false, 1);
    y += 3 + 2 + blokkH;
    printTarolo(y, blokkH, j2.getTarolo(TaroloTipus::Kez), true, 1);
    y += 3 + 2 + blokkH;

    KartyaKiir((screenW - blokkW) / 2, y, &j2.Getboss(), false, kurz.getSel1().szint == 3, kurz.getMov().szint == 3);
    y += 3 + 2 + blokkH;
    econio_gotoxy(0, y++);
    cout << "Mana: " << j2.getMana();
    econio_gotoxy(0, y++);

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
                isRunning = false;
                econio_normalmode();
                return false;
            }
            else if (input == 'e')
            {
                isRunning = false;
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

    if (tipus == "J2")
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

        while (File >> tipus && tipus != "END")
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
        Jatekos tempJatekos2(tempBoss, minionokMeret, kezMeret, kt, mana);
        j2 = tempJatekos2;
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

void GameManager::game()
{
    econio_rawmode();
    changeBG(black);
    changeTxt(white);
    econio_clrscr();
    fazis = 1;
    printGame();
    isJatek = true;
    int input = 0;
    while (isJatek)
    {
        if (econio_kbhit())
        {
            input = econio_getch();
            switch (input)
            {
            case 27: // escape
            case 'x':
                econio_normalmode();
                saveGame();
                isJatek = false;
                break;
            case -20:
            case 'w':
                kurz.lepes(irany::fel, fazis, jatekos, JatekosKivalaszt(jatekos));
                break;
            case -22:
            case 'a':
                kurz.lepes(irany::balra, fazis, jatekos, JatekosKivalaszt(jatekos));
                break;
            case -21:
            case 's':
                kurz.lepes(irany::le, fazis, jatekos, JatekosKivalaszt(jatekos));
                break;
            case -23:
            case 'd':
                kurz.lepes(irany::jobbra, fazis, jatekos, JatekosKivalaszt(jatekos));
                break;
            case 'l':
                kovFazis();
                break;
            case 'E':
            case '\n':
            case '\r':
                kivalaszt();
                break;
            default:
                break;
            }
            printGame();
        }
    }
    econio_clrscr();
}
