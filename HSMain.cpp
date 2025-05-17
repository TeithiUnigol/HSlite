#include "memtrace.h"
#include "gtest_lite.h"
#include "kartya.h"
#include "karakter.h"
#include "minion.h"
#include "boss.h"
#include "kartyaTarolo.h"
#include "jatekos.h"
#include "kurzor.h"
#include "varazslat.h"
#include "GameManager.h"
#include <iostream>

//#define CPORTA
int main()
{
#ifdef CPORTA
    GTINIT(std::cout);

    std::cout << "\n=== Kartya tesztek ===\n"
              << std::endl;
    TEST(Kartya, isminion)
    {
        Kartya kartya("kobold", 2, 'k');
        EXPECT_FALSE(kartya.isMinion());
    }
    ENDM
    TEST(Kartya, Konstruktorok)
    {
        std::stringstream strs;
        Kartya kartya("Tuzgolyo", 3, 'f');
        kartya.nevKiir(strs, kartya.nevMeret());
        kartya.manaKiir(strs);
        kartya.ikonKiir(strs);
        EXPECT_STREQ("Tuzgolyo3f", strs.str().c_str());
        Kartya l = kartya;
        std::stringstream strs2;
        l.nevKiir(strs2, l.nevMeret());
        l.manaKiir(strs2);
        l.ikonKiir(strs2);
        EXPECT_STREQ("Tuzgolyo3f", strs2.str().c_str());
        Kartya m;
        std::stringstream strs3;
        m.nevKiir(strs3, m.nevMeret());
        m.manaKiir(strs3);
        m.ikonKiir(strs3);
        EXPECT_STREQ("0 ", strs3.str().c_str());

        try
        {
            EXPECT_THROW_THROW(l.vedelemValt(10), const char *p);
        }
        catch (const char *p)
        {
        }
        try
        {
            EXPECT_THROW_THROW(l.regen(10), const char *p);
        }
        catch (const char *p)
        {
        }
        try
        {
            EXPECT_THROW_THROW(l.sebzodik(10, &l), const char *p);
        }
        catch (const char *p)
        {
        }
    }
    ENDM
            std::cout
        << "\n=== Karakter tesztek ===\n"
        << std::endl;
    TEST(Karakter, Kijatszas)
    {
        Karakter karakter("kobold", 2, 'k', 10, 10, true);
        int mana = 3;
        EXPECT_TRUE(karakter.kijatszas(&mana, &karakter));
        EXPECT_FALSE(karakter.kijatszas(&mana, &karakter));
    }
    ENDM
    TEST(Karakter, isminion)
    {
        Karakter karakter("kobold", 2, 'k', 10, 10, true);
        EXPECT_FALSE(karakter.isMinion());
    }
    ENDM
    TEST(Karakter, Sebzes)
    {
        std::stringstream strs;
        std::stringstream strs2;
        Karakter karakter("kobold", 2, 'k', 10, 10, true);
        karakter.sebzodik(9, nullptr);
        karakter.nevKiir(strs, karakter.nevMeret());
        EXPECT_STREQ("kobold", strs.str().c_str());
        karakter.sebzodik(2, nullptr);
        karakter.nevKiir(strs2, karakter.nevMeret());
        EXPECT_STREQ(" ", strs2.str().c_str());
    }
    ENDM
    TEST(Karakter, Regeneracio)
    {
        std::stringstream strs;
        Karakter karakter("kobold", 2, 'k', 10, 10, true);
        karakter.sebzodik(9, nullptr);
        EXPECT_TRUE(karakter.regen(10));
        karakter.sebzodik(9, nullptr);
        karakter.nevKiir(strs, karakter.nevMeret());
        EXPECT_STREQ("kobold", strs.str().c_str());
        karakter.sebzodik(20, nullptr);
        EXPECT_FALSE(karakter.regen(10));
    }
    ENDM
    TEST(Karakter, Aktiv)
    {
        Karakter karakter("kobold", 2, 'k', 10, 10, true);
        EXPECT_TRUE(karakter.getAktiv());
        karakter.sebzodik(10, nullptr);
        EXPECT_FALSE(karakter.getAktiv());
        karakter.reaktiv();
        EXPECT_FALSE(karakter.getAktiv());
        Minion m(karakter, 20);
        m.tamadas(&karakter);
        EXPECT_FALSE(m.getAktiv());
        m.reaktiv();
        EXPECT_TRUE(m.getAktiv());
    }
    ENDM
            std::cout
        << "\n=== Minion tesztek ===\n"
        << std::endl;
    TEST(Minion, visszatamadas)
    {
        Minion kobold("kobold", 2, 'k', 10, 10, true, 3, 0);
        Minion lovag("lovag", 4, 'l', 20, 20, true, 20, 0);
        kobold.tamadas(&lovag);
        std::stringstream strs;
        kobold.nevKiir(strs, kobold.nevMeret());
        EXPECT_STREQ(" ", strs.str().c_str());
    }
    ENDM
    TEST(Minion, vedelem & vedelemValt)
    {
        Karakter karakterK("kobold", 2, 'k', 10, 10, true);
        Karakter karakterL("lovag", 4, 'l', 20, 20, true);
        Minion kobold(karakterK, 3);
        Minion lovag(karakterL, 20);
        lovag.tamadas(&kobold);
        EXPECT_FALSE(kobold.regen(10));
    }
    ENDM
    TEST(Minion, Isminion)
    {
        Karakter karakterK("kobold", 2, 'k', 10, 10, true);
        Minion kobold(karakterK, 3);
        EXPECT_TRUE(kobold.isMinion());
    }
    ENDM

            std::cout
        << "\n=== Boss tesztek ===\n"
        << std::endl;
    TEST(Boss, konstruktor)
    {
        Karakter karakterL("Hos Lovag", 0, 'L', 1, 1, true);
        Boss hosLovag(karakterL, 2000);
        std::stringstream strs;
        hosLovag.nevKiir(strs, hosLovag.nevMeret());
        hosLovag.ikonKiir(strs);
        EXPECT_STREQ("Hos LovagL", strs.str().c_str());
    }
    ENDM
    TEST(Boss, isminion)
    {
        Boss boss("kobold", 2, 'k', 10, 10, true, 1);
        EXPECT_FALSE(boss.isMinion());
    }
    ENDM
    TEST(Boss, special)
    {
        Karakter karakterK("kobold", 2, 'k', 10, 10, true);
        Karakter karakterL("Hos Lovag", 0, 'L', 1, 1, true);
        Minion kobold(karakterK, 3);
        Boss hosLovag(karakterL, 2000);
        hosLovag.special(kobold);
        std::stringstream strs;
        kobold.nevKiir(strs, kobold.nevMeret());
        EXPECT_STREQ(" ", strs.str().c_str());
        strs.clear();
        hosLovag.nevKiir(strs, hosLovag.nevMeret());
        EXPECT_STREQ(" Hos Lovag", strs.str().c_str());
        EXPECT_FALSE(hosLovag.getAktiv());
    }
    ENDM

            std::cout
        << "\n=== Varazslat tesztek ===\n"
        << std::endl;
    TEST(Varazslat, konstruktor)
    {
        std::stringstream strs;
        Varazslat v("Tuzgolyo", 3, 'f', 20, 10, 10);
        Minion kobold("kobold", 2, 'k', 10, 10, true, 3, 0);
        v.nevKiir(strs, v.nevMeret());
        v.manaKiir(strs);
        v.ikonKiir(strs);
        EXPECT_STREQ("Tuzgolyo3f", strs.str().c_str());
        int mana = 20;
        v.kijatszas(&mana, &kobold);
        EXPECT_EQ(17, mana);
        EXPECT_EQ(0, kobold.getElet());
    }
    ENDM

            std::cout
        << "\n=== Tarolo tesztek ===\n"
        << std::endl;
    TEST(KartyaTarolo, konstruktor)
    {
        KartyaTarolo T(4);
        std::stringstream strs;
        Kartya ka1("a", 10, 10);
        Kartya ka2("b", 10, 10);
        Kartya ka3("c", 10, 10);
        Kartya ka4("d", 10, 10);
        T.randomBeszur(&ka1);
        T.randomBeszur(&ka2);
        T.randomBeszur(&ka3);
        T.randomBeszur(&ka4);
        for (size_t i = 0; i < 4; i++)
        {
            T[i]->nevKiir(strs, T[i]->nevMeret());
        }
        EXPECT_STREQ("dacb", strs.str().c_str());
        try
        {
            EXPECT_THROW(T.berak(&ka4, 2), const char *p);
        }
        catch (const char *p)
        {
        }
    }
    ENDM

        Boss sotetLovag("Sotet Lovag", 0, 'L', 30, 30, true, 2000);

    Minion kobold("kobold", 2, 'k', 10, 10, true, 3, 0);

    Minion sari("Sarkany", 2, 'S', 40, 40, true, 15, 0);

    Varazslat nekro("nekromanta", 2, 'n', 0, 3, 10);
    Varazslat savasE("savas eso", 2, 's', 10, 0, 0);

    Boss hosLovag("Hos Lovag", 0, 'L', 30, 30, true, 2000);

    Minion gyalog("gyalog", 2, 'g', 10, 10, true, 3, 0);

    Minion sariOlo("Sarkanyolo", 2, 'S', 40, 40, true, 15, 0);

    Varazslat gyogy("gyogyitas", 2, 'n', 0, 3, 10);
    Varazslat nyilz("nyilzapor", 2, 's', 10, 0, 0);

    KartyaTarolo csomag1(20);
    size_t i1 = 0;
    // Ez majd fájlból ovasással lesz megoldva
    csomag1.berak(&sari, i1++);
    for (size_t i = 0; i < 2; i++)
    {
        csomag1.berak(&nekro, i1++);
    }
    for (size_t i = 0; i < 2; i++)
    {
        csomag1.berak(&savasE, i1++);
    }
    for (size_t i = 0; i < 5; i++)
    {
        csomag1.berak(&kobold, i1++);
    }
    /*size_t kezmeret = 5;
    Jatekos jteszt(hosLovag, 5, kezmeret, csomag1, 3);
    std::cout << "\n=== Jatekos tesztek ===\n"<< std::endl;
    TEST(Jatekos, konstruktor)
    {
        EXPECT_EQ(3, jteszt.getMana());
        EXPECT_EQ(30, jteszt.Getboss().getElet());
        }
        ENDM*/
    /*TEST(Jatekos, kezfeltolt&meret&kapacitas)
    {
        EXPECT_EQ(0, jteszt.getTarolo(TaroloTipus::Kez).getMeret());
        jteszt.kezfeltolt();
        EXPECT_EQ(kezmeret, jteszt.getTarolo(TaroloTipus::Kez).getMeret());
        }
        ENDM*/
#endif

#ifndef CPORTA

GameManager gm(50, 15, 5, 2, "pakli.txt", "jatek.txt");
//gm.MenuSelect();
gm.loadPakli();
gm.printGame();

#endif

    return 0;
}