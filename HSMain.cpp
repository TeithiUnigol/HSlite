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

#ifndef CPORTA
#define CPORTA
#endif

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
        Kartya kartya("Tuzgolyo", 3, 'f');
        EXPECT_EQ('f', kartya.getIkon());
        Kartya l = kartya;
        EXPECT_EQ('f', kartya.getIkon());
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
        Karakter karakter("kobold", 2, 'k', 10, 10, true);
        karakter.sebzodik(9, nullptr);

        EXPECT_EQ('k', karakter.getIkon());

        karakter.sebzodik(2, nullptr);
        EXPECT_EQ(' ', karakter.getIkon());
    }
    ENDM
    TEST(Karakter, Regeneracio)
    {
        Karakter karakter("kobold", 2, 'k', 10, 10, true);
        karakter.sebzodik(9, nullptr);
        EXPECT_TRUE(karakter.regen(10));
        karakter.sebzodik(9, nullptr);
        EXPECT_EQ('k', karakter.getIkon());
        karakter.sebzodik(20, nullptr);
        EXPECT_FALSE(karakter.regen(10));
    }
    ENDM
    TEST(Karakter, Aktiv)
    {
        Karakter karakter("kobold", 2, 'k', 10, 10, true);
        EXPECT_TRUE(karakter.getAktiv());
        karakter.sebzodik(100, nullptr);
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
        EXPECT_EQ(' ', kobold.getIkon());
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
        EXPECT_EQ('L', hosLovag.getIkon());
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
        int mana = 10;
        hosLovag.tamadas(&kobold);
        EXPECT_EQ(' ', kobold.getIkon());
        EXPECT_FALSE(hosLovag.getAktiv());
        EXPECT_EQ(mana, 10);
    }
    ENDM

            std::cout
        << "\n=== Varazslat tesztek ===\n"
        << std::endl;
    TEST(Varazslat, konstruktor)
    {
        Varazslat v("Tuzgolyo", 3, 'f', 20, 10, 10);
        Minion kobold("kobold", 2, 'k', 10, 10, true, 3, 0);
        EXPECT_EQ('f', v.getIkon());
        int mana = 20;
        v.kijatszas(&mana, &kobold);
        EXPECT_EQ(17, mana);
        EXPECT_EQ(0, kobold.getElet());
    }
    ENDM
    TEST(Varazslat, kijatszas)
    {
        Varazslat v("Tuzgolyo", 3, 'f', 20, 10, 10);
        Minion kobold("kobold", 2, 'k', 10, 10, true, 3, 0);
        EXPECT_EQ('f', v.getIkon());
        int mana = 20;
        v.kijatszas(&mana, &kobold);
        EXPECT_EQ(17, mana);
        EXPECT_EQ(0, kobold.getElet());
    }
    ENDM

            std::cout
        << "\n=== Tarolo tesztek ===\n"
        << std::endl;
    KartyaTarolo T(4);
    std::stringstream strs;
    Kartya ka1("a", 10, 10);
    Kartya ka2("b", 10, 10);
    Kartya ka3("c", 10, 10);

    Kartya ka4("d", 10, 10);
    T.randomBeszur(&ka1);
    T.randomBeszur(&ka2);
    T.randomBeszur(&ka3);
    TEST(KartyaTarolo, Meret)
    {
        EXPECT_EQ(3, T.getMeret());
    }
    ENDM
        T.randomBeszur(&ka4);
    TEST(KartyaTarolo, konstruktor)
    {
        KartyaTarolo Ta(2);
        Kartya c0("a", 10, 'k');
        Kartya c1("b", 10, 't');

        Ta.berak(&c0, 0);
        Ta.berak(&c1, 1);
        EXPECT_EQ('t', Ta[1]->getIkon());
        try
        {
            Kartya asd("asd", 10, 'f');
            EXPECT_THROW(Ta.berak(&asd, 2), const char *p);
        }
        catch (const char *p)
        {
        }
    }
    ENDM

    TEST(KartyaTarolo, randomBeszur)
    {
        KartyaTarolo Ta(2);
        Kartya c0("a", 10, 'k');
        Kartya c1("b", 10, 't');
        std::stringstream strs1;
        strs1 << c0.getIkon() << c1.getIkon();
        EXPECT_STREQ("kt", strs1.str().c_str());
    }
    ENDM

    TEST(KartyaTarolo, Kapacitas)
    {
        EXPECT_EQ(4, T.getKapacitas());
    }
    ENDM

    TEST(KartyaTarolo, Errors)
    {
        KartyaTarolo Ta(0);
        Kartya ka5("ads", 10, 10);
        try
        {
            EXPECT_THROW(Ta.randomBeszur(&ka5), const char *p);
        }
        catch (const char *p)
        {
        }
    }
    ENDM
    TEST(KartyaTarolo, Kihuz)
    {
        KartyaTarolo Ta(1);
        Kartya ka5("ads", 10, 'a');
        Ta.berak(&ka5, 0);
        Kartya *ttemp = Ta.kihuz(0);
        EXPECT_EQ('a', ttemp->getIkon());
        delete ttemp;
    }
    ENDM

        Boss sotetLovag("Sotet Lovag", 0, 'V', 30, 30, true, 2000);

    Minion kobold("kobold", 2, 'k', 10, 10, true, 3, 0);

    Minion sari("Sarkany", 2, 'S', 40, 40, true, 15, 0);

    Varazslat nekro("nekromanta", 2, 'n', 0, 3, 10);
    Varazslat savasE("savas eso", 2, 's', 10, 0, 0);

    Boss hosLovag("Hos Lovag", 30, 'L', 30, 30, true, 2000);

    Minion gyalog("gyalog", 2, 'g', 10, 10, true, 3, 0);

    Minion sariOlo("Sarkanyolo", 2, 'S', 40, 40, true, 15, 0);

    Varazslat gyogy("gyogyitas", 2, 'n', 0, 3, 10);
    Varazslat nyilz("nyilzapor", 2, 's', 10, 0, 0);

    KartyaTarolo csomag1(10);
    KartyaTarolo csomag2(10);

    size_t i1 = 0;
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

    size_t i2 = 0;
    csomag2.berak(&sariOlo, i2++);
    for (size_t i = 0; i < 2; i++)
    {
        csomag2.berak(&gyogy, i2++);
    }
    for (size_t i = 0; i < 2; i++)
    {
        csomag2.berak(&nyilz, i2++);
    }
    for (size_t i = 0; i < 5; i++)
    {
        csomag2.berak(&gyalog, i2++);
    }

    size_t kezmeret = 5;
    Jatekos jteszt(hosLovag, 5, kezmeret, csomag1, 3);

    std::cout << "\n=== Jatekos tesztek ===\n"
              << std::endl;
    TEST(Jatekos, konstruktor)
    {
        EXPECT_EQ(3, jteszt.getMana());
        EXPECT_EQ('L', jteszt.Getboss()->getIkon());
    }
    ENDM
    TEST(Jatekos, kezfeltolt & meret & kapacitas)
    {
        EXPECT_EQ(0, jteszt.getTarolo(TaroloTipus::Kez).getMeret());
        jteszt.kezfeltolt();
        EXPECT_EQ(kezmeret, jteszt.getTarolo(TaroloTipus::Kez).getMeret());
        EXPECT_EQ(5, jteszt.getTarolo(TaroloTipus::Kez).getKapacitas());
    }
    ENDM
    TEST(Jatekos, Kijatszas)
    {
        Varazslat v1("savas eso", 2, 's', 20, 0, 0);
        Varazslat v2("savas eso", 10, 's', 20, 0, 0);
        Minion kobold("kobold", 2, 'k', 10, 10, true, 3, 0);
        Minion minion2("kobold", 2, 'k', 10, 10, true, 3, 0);

        Jatekos jteszt1(hosLovag, 5, kezmeret, csomag1, 3);

        jteszt1.getTarolo(TaroloTipus::Kez).berak(&v1, 2);
        jteszt1.getTarolo(TaroloTipus::Minionok).berak(&kobold, 1);

        EXPECT_FALSE(jteszt1.getTarolo(TaroloTipus::Kez)[2]->isMinion());
        EXPECT_TRUE(jteszt1.Kijatszas(jteszt1.getTarolo(TaroloTipus::Kez)[2], 2, jteszt1.getTarolo(TaroloTipus::Minionok)[1], 1));
        EXPECT_EQ(1, jteszt1.getMana());
        EXPECT_EQ(0, jteszt1.getTarolo(TaroloTipus::Kez).getMeret());

        EXPECT_EQ(' ', jteszt1.getTarolo(TaroloTipus::Minionok)[1]->getIkon());

        jteszt1.getTarolo(TaroloTipus::Kez).berak(&v2, 2);
        EXPECT_FALSE(jteszt1.Kijatszas(jteszt1.getTarolo(TaroloTipus::Kez)[2], 2, jteszt1.getTarolo(TaroloTipus::Minionok)[1], 1));
    }
    ENDM
    TEST(Jatekos, Kijatszas2)
    {
        Varazslat v1("savas eso", 2, 's', 20, 0, 0);
        Varazslat v2("savas eso", 10, 's', 20, 0, 0);
        Minion kobold("kobold", 2, 'k', 10, 10, true, 3, 0);
        Minion minion2("kobold", 2, 'k', 10, 10, true, 3, 0);

        Jatekos jteszt1(hosLovag, 5, kezmeret, csomag1, 10);

        jteszt1.getTarolo(TaroloTipus::Kez).berak(&kobold, 3);
        EXPECT_TRUE(jteszt1.Kijatszas(jteszt1.getTarolo(TaroloTipus::Kez)[3], 3, jteszt1.getTarolo(TaroloTipus::Minionok)[1], 1));
        EXPECT_EQ('k', jteszt1.getTarolo(TaroloTipus::Minionok)[1]->getIkon());
    }
    ENDM
    TEST(Jatekos, Ujkor)
    {
        Jatekos jteszt1(hosLovag, 5, kezmeret, csomag1, 3);
        Varazslat v1("savas eso", 2, 's', 20, 0, 0);
        Minion kobold("kobold", 2, 'k', 10, 10, true, 3, 0);
        jteszt1.getTarolo(TaroloTipus::Kez).berak(&v1, 2);
        jteszt1.getTarolo(TaroloTipus::Minionok).berak(&kobold, 1);
        jteszt1.Getboss()->tamadas(&kobold);
        EXPECT_FALSE(jteszt1.Getboss()->getAktiv());
        EXPECT_TRUE(jteszt1.Kijatszas(jteszt1.getTarolo(TaroloTipus::Kez)[2], 2, jteszt1.getTarolo(TaroloTipus::Minionok)[1], 1));
        jteszt1.ujKor();
        EXPECT_TRUE(jteszt1.Getboss()->getAktiv());
        EXPECT_EQ(5, jteszt1.getTarolo(TaroloTipus::Kez).getMeret());
    }
    ENDM

            std::cout
        << "\n=== Kurzor tesztek ===\n";
    TEST(Kurzor, AlapKezdoAllapot)
    {
        Kurzor k;
        EXPECT_EQ(k.getMov().pointer, nullptr);
        EXPECT_EQ(k.getMov().index, 0);
        EXPECT_EQ(k.getMov().szint, -1);
    }
    ENDM

    TEST(Kurzor, konstruktor)
    {
        Jatekos j1(hosLovag, 5, kezmeret, csomag2, 3);
        Jatekos j2(sotetLovag, 5, kezmeret, csomag1, 3);
        Kurzor kurz(&j1, &j2);
        j1.ujKor();
        kurz.getMov().index = 0;
        kurz.getMov().szint = 0;
        kurz.getMov().pointer = j1.getTarolo(TaroloTipus::Kez)[0];

        kurz.lepes(jobbra, 1, 0, &j1);
        EXPECT_EQ(0, kurz.getMov().szint);
        EXPECT_EQ(1, kurz.getMov().index);
        kurz.lepes(jobbra, 1, 0, &j1);
        EXPECT_EQ(0, kurz.getMov().szint);
        EXPECT_EQ(2, kurz.getMov().index);
    }
    ENDM
    TEST(Kurzor, masolas)
    {
        Jatekos j1(hosLovag, 5, kezmeret, csomag2, 3);
        Jatekos j2(sotetLovag, 5, kezmeret, csomag1, 3);
        Kurzor kurz(&j1, &j2);
        j1.ujKor();
        kurz.getMov().pointer = j1.Getboss();
        kurz.getMov().szint = 0;
        kurz.getMov().index = 0;
        kurz.getSel1() = kurz.getMov();
        EXPECT_EQ(kurz.getMov().pointer->getIkon(), kurz.getSel1().pointer->getIkon());
        EXPECT_EQ(kurz.getMov().szint, kurz.getSel1().szint);
        EXPECT_EQ(kurz.getMov().index, kurz.getSel1().index);
    }
    ENDM
    TEST(Kurzor, lepes1_1)
    {
        Jatekos j1(hosLovag, 5, kezmeret, csomag2, 3);
        Jatekos j2(sotetLovag, 5, kezmeret, csomag1, 3);
        // első fázis első fele
        Kurzor kurz(&j1, &j2);
        j1.ujKor();
        kurz.getMov().index = 0;
        kurz.getMov().szint = 0;
        kurz.getMov().pointer = j1.getTarolo(TaroloTipus::Kez)[0];
        kurz.lepes(jobbra, 1, 0, &j1);
        EXPECT_EQ(0, kurz.getMov().szint);
        EXPECT_EQ(1, kurz.getMov().index);
        kurz.lepes(jobbra, 1, 0, &j1);
        EXPECT_EQ(0, kurz.getMov().szint);
        EXPECT_EQ(2, kurz.getMov().index);
        kurz.lepes(balra, 1, 0, &j1);
        EXPECT_EQ(0, kurz.getMov().szint);
        EXPECT_EQ(1, kurz.getMov().index);
        kurz.lepes(fel, 1, 0, &j1);
        EXPECT_EQ(0, kurz.getMov().szint);
        EXPECT_EQ(1, kurz.getMov().index);
        kurz.lepes(le, 1, 0, &j1);
        EXPECT_EQ(0, kurz.getMov().szint);
        EXPECT_EQ(1, kurz.getMov().index);
    }
    ENDM
    TEST(Kurzor, lepes1_2Minion)
    {
        Jatekos j1(hosLovag, 5, kezmeret, csomag2, 3);
        Jatekos j2(sotetLovag, 5, kezmeret, csomag1, 3);
        // elso fázis celpont kereses lepes
        Kurzor kurz(&j1, &j2);
        j1.ujKor();
        delete j1.getTarolo(TaroloTipus::Kez).kihuz(0);
        j1.getTarolo(TaroloTipus::Kez).berak(&gyalog, 0);
        kurz.getSel1().pointer = j1.getTarolo(TaroloTipus::Kez)[0]; // egy minon
        kurz.getSel1().szint = 1;
        kurz.getSel1().index = 0;
        kurz.getMov().szint = 2;
        kurz.getMov().index = 0;
        kurz.getMov().pointer = j1.getTarolo(TaroloTipus::Minionok)[0];

        // std::cout<<j1.getTarolo(TaroloTipus::Kez)[0]->getIkon()<<":"<<j1.getTarolo(TaroloTipus::Kez)[0]->isMinion();//gyalog
        // std::cout<<j1.getTarolo(TaroloTipus::Kez)[2]->getIkon()<<":"<<j1.getTarolo(TaroloTipus::Kez)[2]->isMinion();//nyilzapor
        // Minion lepes
        kurz.lepes(jobbra, 1, 0, &j1);
        EXPECT_EQ(2, kurz.getMov().szint);
        EXPECT_EQ(1, kurz.getMov().index);
        kurz.lepes(balra, 1, 0, &j1);
        EXPECT_EQ(2, kurz.getMov().szint);
        EXPECT_EQ(0, kurz.getMov().index);
        kurz.lepes(le, 1, 0, &j1);
        EXPECT_EQ(2, kurz.getMov().szint);
        EXPECT_EQ(0, kurz.getMov().index);
        kurz.lepes(fel, 1, 0, &j1);
        EXPECT_EQ(2, kurz.getMov().szint);
        EXPECT_EQ(0, kurz.getMov().index);
        kurz.lepes(fel, 1, 0, &j1);
        EXPECT_EQ(2, kurz.getMov().szint);
        EXPECT_EQ(0, kurz.getMov().index);
    }
    ENDM

    TEST(Kurzor, lepes1_2Varazslat)
    {
        Jatekos j1(hosLovag, 5, kezmeret, csomag2, 3);
        Jatekos j2(sotetLovag, 5, kezmeret, csomag1, 3);
        // elso fázis celpont kereses lepes
        Kurzor kurz(&j1, &j2);
        j1.ujKor();
        delete j1.getTarolo(TaroloTipus::Kez).kihuz(2);
        j1.getTarolo(TaroloTipus::Kez).berak(&nyilz, 0);
        kurz.getSel1().pointer = j1.getTarolo(TaroloTipus::Kez)[2]; // egy minon
        kurz.getSel1().szint = 1;
        kurz.getSel1().index = 2;
        kurz.getMov().szint = 2;
        kurz.getMov().index = 0;
        kurz.getMov().pointer = j1.getTarolo(TaroloTipus::Minionok)[0];

        // std::cout<<j1.getTarolo(TaroloTipus::Kez)[0]->getIkon()<<":"<<j1.getTarolo(TaroloTipus::Kez)[0]->isMinion();//gyalog
        // std::cout<<j1.getTarolo(TaroloTipus::Kez)[2]->getIkon()<<":"<<j1.getTarolo(TaroloTipus::Kez)[2]->isMinion();//nyilzapor

        // Minion lepes
        kurz.lepes(jobbra, 1, 0, &j1);
        EXPECT_EQ(2, kurz.getMov().szint);
        EXPECT_EQ(1, kurz.getMov().index);
        kurz.lepes(balra, 1, 0, &j1);
        EXPECT_EQ(2, kurz.getMov().szint);
        EXPECT_EQ(0, kurz.getMov().index);
        kurz.lepes(le, 1, 0, &j1);
        EXPECT_EQ(3, kurz.getMov().szint);
        EXPECT_EQ(0, kurz.getMov().index);
        kurz.lepes(fel, 1, 0, &j1);
        EXPECT_EQ(2, kurz.getMov().szint);
        EXPECT_EQ(0, kurz.getMov().index);
        kurz.lepes(fel, 1, 0, &j1);
        EXPECT_EQ(0, kurz.getMov().szint);
        EXPECT_EQ(0, kurz.getMov().index);
        kurz.lepes(fel, 1, 0, &j1);
        EXPECT_EQ(5, kurz.getMov().szint);
        EXPECT_EQ(0, kurz.getMov().index);
        kurz.lepes(fel, 1, 0, &j1);
        EXPECT_EQ(3, kurz.getMov().szint);
        EXPECT_EQ(0, kurz.getMov().index);
    }
    ENDM

    TEST(Kurzor, lepes2_2)
    {
        Jatekos j1(hosLovag, 5, kezmeret, csomag2, 3);
        Jatekos j2(sotetLovag, 5, kezmeret, csomag1, 3);
        // második fázis lépések
        Kurzor kurz(&j1, &j2);
        j1.ujKor();
        kurz.getMov().pointer = j1.Getboss();
        kurz.getMov().szint = 0;
        kurz.getMov().index = 0;
        kurz.lepes(jobbra, 2, 0, &j1);
        EXPECT_EQ(0, kurz.getMov().szint);
        EXPECT_EQ(1, kurz.getMov().index);
        kurz.lepes(balra, 2, 0, &j1);
        EXPECT_EQ(0, kurz.getMov().szint);
        EXPECT_EQ(0, kurz.getMov().index);
        kurz.lepes(le, 2, 0, &j1);
        EXPECT_EQ(2, kurz.getMov().szint);
        EXPECT_EQ(0, kurz.getMov().index);
        kurz.lepes(fel, 2, 0, &j1);
        EXPECT_EQ(0, kurz.getMov().szint);
        EXPECT_EQ(0, kurz.getMov().index);
        kurz.lepes(fel, 2, 0, &j1);
        EXPECT_EQ(2, kurz.getMov().szint);
        EXPECT_EQ(0, kurz.getMov().index);
    }
    ENDM

    TEST(Kurzor, lepes2_2)
    {
        Jatekos j1(hosLovag, 5, kezmeret, csomag2, 3);
        Jatekos j2(sotetLovag, 5, kezmeret, csomag1, 3);
        // második fázis lépések
        Kurzor kurz(&j1, &j2);
        j1.ujKor();
        kurz.getSel1().pointer = j1.Getboss();
        kurz.getSel1().szint = 0;
        kurz.getSel1().index = 0;
        kurz.getMov().szint = 3;
        kurz.getMov().index = 0;
        kurz.getMov().pointer = j2.getTarolo(TaroloTipus::Minionok)[0];
        kurz.lepes(jobbra, 2, 0, &j1);
        EXPECT_EQ(1, kurz.getMov().index);
        EXPECT_EQ(3, kurz.getMov().szint);
        kurz.lepes(balra, 2, 0, &j1);
        EXPECT_EQ(0, kurz.getMov().index);
        EXPECT_EQ(3, kurz.getMov().szint);
        kurz.lepes(le, 2, 0, &j1);
        EXPECT_EQ(0, kurz.getMov().index);
        EXPECT_EQ(5, kurz.getMov().szint);
        kurz.lepes(fel, 2, 0, &j1);
        EXPECT_EQ(0, kurz.getMov().index);
        EXPECT_EQ(3, kurz.getMov().szint);
        kurz.lepes(fel, 2, 0, &j1);
        EXPECT_EQ(0, kurz.getMov().index);
        EXPECT_EQ(5, kurz.getMov().szint);
    }
    ENDM

    TEST(Kurzor, kijatszas)
    {
        Jatekos j1(hosLovag, 5, kezmeret, csomag2, 3);
        Jatekos j2(sotetLovag, 5, kezmeret, csomag1, 3);
        delete j1.getTarolo(TaroloTipus::Kez).kihuz(0);
        j1.getTarolo(TaroloTipus::Kez).berak(&gyalog, 0);

        // második fázis lépések
        Kurzor kurz(&j1, &j2);
        j1.ujKor();
        kurz.getSel1().pointer = j1.getTarolo(TaroloTipus::Kez)[0]; // egy minon
        kurz.getSel1().szint = 1;
        kurz.getSel1().index = 0;
        kurz.getMov().szint = 2;
        kurz.getMov().index = 0;
        kurz.getMov().pointer = j1.getTarolo(TaroloTipus::Minionok)[0];
        EXPECT_TRUE(kurz.kivalaszt(1, &j1, &j2, 0));
    }
    ENDM

            std::cout
        << "\n=== GameManager tesztek ===\n";

TEST(GameManager, betoltes)
    {
        GameManager gm1(100, 15, 4, 4, "helytelenNev.txt");
        try
        {
            EXPECT_THROW(gm1.loadPakli(),const char *p);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        GameManager gm2(100, 15, 4, 4, "pakli.txt");
        try
        {
            EXPECT_NO_THROW(gm2.loadPakli());
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        gm2.loadPakli();
    }
    ENDM


#endif

#ifndef CPORTA

    GameManager gm(100, 15, 4, 4, "pakli.txt");
    gm.MenuSelect();

#endif

    return 0;
}
