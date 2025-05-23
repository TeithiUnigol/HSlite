#include "GameManager.h"

#include "memtrace.h"

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

GameManager::GameManager(size_t screenW, size_t blokkW, size_t blokkH, size_t separatorS, std::string pakliforras)
    : screenW(screenW), blokkW(blokkW), blokkH(blokkH), separatorS(separatorS),pakliFile(pakliforras) {}
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
    cout << "Kilepes\n";

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
            case 'e':
            case '\n':
            case '\r':
                if (kiv == 0)
                {
                    isKerdez = false;
                    try
                    {
                        loadPakli();
                    }
                    catch (...)
                    {
                        econio_clrscr();
                        changeTxt(red);
                        cout << "Sikertelen beolvasas";
                        econio_sleep(1.5);
                        changeTxt(white);
                        econio_clrscr();
                        return;
                    }
                    j1.kezfeltolt();
                    j2.kezfeltolt();
                    jatekos = 0;
                    kurz.getMov().szint = 1;
                    kurz.getMov().pointer = j1.getTarolo(TaroloTipus::Kez)[0];
                    kurz.getSel1().szint = -1;
                    isJatek = true;
                    game();
                }
                else
                {
                    isKerdez = false;
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
                cout << "Kilepes\n";
            }
            else
            {
                changeBG(black);
                cout << "Uj Jatek\n";
                changeBG(green);
                cout << "Kilepes\n";
                changeBG(black);
            }
        }
    }
    econio_clrscr();
}

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
    if (k->getIkon() != ' ')
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

void GameManager::printTarolo(int yKezd, int yMeret, KartyaTarolo &tarolo, bool isKez, int melyikJatekose)
{
    size_t kap = tarolo.getKapacitas();
    int fal = ((screenW - kap * blokkW - (kap - 1) * separatorS) / 2);
    for (size_t i = 0; i < kap; ++i)
    {
        if (melyikJatekose == 0)
        {
            if (isKez) // szint 1 kez
            {
                if (kurz.getMov().szint == 1 && kurz.getMov().index == i)
                {
                    KartyaKiir(fal, yKezd, tarolo[i], isKez, false, true);
                }
                else if (kurz.getSel1().szint == 1 && kurz.getSel1().index == i)
                {
                    KartyaKiir(fal, yKezd, tarolo[i], isKez, true, false);
                }
                else
                {
                    KartyaKiir(fal, yKezd, tarolo[i], isKez, false, false);
                }
            }
            else // szint 2 minion
            {
                if (kurz.getMov().szint == 2 && kurz.getMov().index == i)
                {
                    KartyaKiir(fal, yKezd, tarolo[i], isKez, false, true);
                }
                else if (kurz.getSel1().szint == 2 && kurz.getSel1().index == i)
                {
                    KartyaKiir(fal, yKezd, tarolo[i], isKez, true, false);
                }
                else
                {
                    KartyaKiir(fal, yKezd, tarolo[i], isKez, false, false);
                }
            }
        }
        else
        {
            if (!isKez) // szint 3 minion
            {
                if (kurz.getMov().szint == 3 && kurz.getMov().index == i)
                {
                    KartyaKiir(fal, yKezd, tarolo[i], isKez, false, true);
                }
                else if (kurz.getSel1().szint == 3 && kurz.getSel1().index == i)
                {
                    KartyaKiir(fal, yKezd, tarolo[i], isKez, true, false);
                }
                else
                {
                    KartyaKiir(fal, yKezd, tarolo[i], isKez, false, false);
                }
            }
            else // szint 4 kez
            {
                if (kurz.getMov().szint == 4 && kurz.getMov().index == i)
                {
                    KartyaKiir(fal, yKezd, tarolo[i], isKez, false, true);
                }
                else if (kurz.getSel1().szint == 4 && kurz.getSel1().index == i)
                {
                    KartyaKiir(fal, yKezd, tarolo[i], isKez, true, false);
                }
                else
                {
                    KartyaKiir(fal, yKezd, tarolo[i], isKez, false, false);
                }
            }
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
    econio_gotoxy(0, y++);
    cout << "Fazis: " << fazis;
    if (jatekos == 0)
    {
        changeBG(green);
    }
    econio_gotoxy(0, y++);
    cout << "Jatekos 1";
    changeBG(black);
    econio_gotoxy(0, y++);
    cout << "Mana: " << j1.getMana();

    Kartya *b1 = j1.Getboss();
    KartyaKiir((screenW - blokkW) / 2, y, b1, false, kurz.getSel1().pointer == b1, kurz.getMov().szint == 0);

    y += 3 + 2 + blokkH;

    printTarolo(y, blokkH, j1.getTarolo(TaroloTipus::Kez), true, 0);
    y += 3 + 2 + blokkH;
    printTarolo(y, blokkH, j1.getTarolo(TaroloTipus::Minionok), false, 0);
    y += 3 + 2 + blokkH;

    econio_gotoxy(0, y++);
    for (size_t i = 0; i < screenW; i++)
    {
        cout << "-";
    }

    printTarolo(y, blokkH, j2.getTarolo(TaroloTipus::Minionok), false, 1);
    y += 3 + 2 + blokkH;
    printTarolo(y, blokkH, j2.getTarolo(TaroloTipus::Kez), true, 1);
    y += 3 + 2 + blokkH;

    Kartya *b2 = j2.Getboss();
    KartyaKiir((screenW - blokkW) / 2, y, b2, false, kurz.getSel1().pointer == b2, kurz.getMov().szint == 5);
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


    cout << "\nJ1Huzo:" <<j1.getTarolo(TaroloTipus::Huzo).getMeret()<<"/"<<j1.getTarolo(TaroloTipus::Huzo).getKapacitas()<<std::endl;
    cout << "J2Huzo:" <<j2.getTarolo(TaroloTipus::Huzo).getMeret()<<"/"<<j2.getTarolo(TaroloTipus::Huzo).getKapacitas();

    cout << "\nJ1Minion:" <<j1.getTarolo(TaroloTipus::Minionok).getMeret()<<"/"<<j1.getTarolo(TaroloTipus::Minionok).getKapacitas()<<std::endl;
    cout << "J2Minion:" <<j2.getTarolo(TaroloTipus::Minionok).getMeret()<<"/"<<j2.getTarolo(TaroloTipus::Minionok).getKapacitas();

    cout << "\nJ1Kez:" <<j1.getTarolo(TaroloTipus::Kez).getMeret()<<"/"<<j1.getTarolo(TaroloTipus::Kez).getKapacitas()<<std::endl;
    cout << "J2Kez:" <<j2.getTarolo(TaroloTipus::Kez).getMeret()<<"/"<<j2.getTarolo(TaroloTipus::Kez).getKapacitas();
    if(kurz.getSel1().pointer!=nullptr){
        cout<< "\nselP:" <<kurz.getSel1().pointer->getIkon();
    }



}

//------------Játéklogika--------------
void GameManager::kivalaszt()
{

    bool sikeres = kurz.kivalaszt(fazis, JatekosKivalaszt(jatekos), JatekosKivalaszt(1 - jatekos), jatekos);
    if (!sikeres)
    {
        econio_clrscr();
        changeTxt(red);
        cout << "Nem lehet a kivalasztott helyrol a kivalasztott helyre kartyat kijatszani vagy keves a rendelkezesre allo mana."<<std::endl;
        econio_sleep(1.5);
        changeTxt(white);
    }
    if (j1.Getboss()->getIkon()==' ')
    {
        endGameScreen(1);
    }else if (j2.Getboss()->getIkon() == ' ')
    {
        endGameScreen(0);
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
    cout << "Nyomj egy gombot a kilepeshez.";
    int isRunning = 1;
    while (isRunning)
    {
        if (econio_kbhit())
        {
            isRunning = false;
        }
    }
    return false;
}

void GameManager::kovFazis()
{
    kurz.getSel1().pointer = nullptr;
    kurz.getSel1().szint = -1;
    fazis += 1;
    if (fazis == 1)
    {
        kurz.getMov().szint = jatekos == 0 ? 1 : 4;
        kurz.getMov().pointer = jatekos == 0 ? j1.getTarolo(TaroloTipus::Kez)[0] : j2.getTarolo(TaroloTipus::Kez)[0];
    }
    else if (fazis == 2)
    {
        kurz.getMov().szint = jatekos == 0 ? 0 : 5;
        kurz.getMov().index = 0;
        kurz.getMov().pointer = jatekos == 0 ? j1.Getboss() : j2.Getboss();
    }
    else if (fazis == 3)
    {
        jatekos = (jatekos + 1) % 2;
        jatekos==1?j2.ujKor():j1.ujKor();
        kurz.getMov().szint = jatekos == 0 ? 1 : 4;
        kurz.getMov().pointer = jatekos == 0 ? j1.getTarolo(TaroloTipus::Kez)[0] : j2.getTarolo(TaroloTipus::Kez)[0];


        fazis = 1;
    }
}


void GameManager::loadPakli()
{
    std::ifstream File(pakliFile.c_str());

    if (!File.is_open()) {
        throw "Sikertelen filemegnyitas";
    }

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

        Boss tempBoss1;
        try
        {
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
                    tempBoss1.betoltes(File);
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
        }
        catch (...)
        {
            File.close();
            throw;
        }
        
        j1 = Jatekos(tempBoss1, minionokMeret, kezMeret, kt, mana);
    }
    else
    {
        File.close();
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
            File.close();
            throw "Helytelen bemenetfile";
        }
        KartyaTarolo kt(csomagmeret);

        Boss tempBoss2;
        try
        {
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
                    tempBoss2.betoltes(File);
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
        }
        catch (...)
        {
            File.close();
            throw;
        }
        j2 = Jatekos(tempBoss2, minionokMeret, kezMeret, kt, mana);

    }
    else
    {
        File.close();
        throw "Helytelen bemenetfile";
    }
    kurz = Kurzor(&j1, &j2);
    
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
            case 'e':
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
