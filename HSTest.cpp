

#include "memtrace.h"
#include "gtest_lite.h"
#include "kartya.h"
#include "karakter.h"
#include "minion.h"
#include "boss.h"
#include <iostream>

int main(){
    GTINIT(std::cout);
    std::cout << "\n=== Kartya tesztek ===\n" << std::endl;
    Kartya kartya("Tuzgolyo",3,'f');
    TEST(Kartya,Konstruktorok){
        std::stringstream strs;
        kartya.nevKiir(strs);
        kartya.manaKiir(strs);
        kartya.ikonKiir(strs);
        EXPECT_STREQ("Tuzgolyo3f", strs.str().c_str());
        Kartya l = kartya;
        std::stringstream strs2;
        l.nevKiir(strs2);
        l.manaKiir(strs2);
        l.ikonKiir(strs2);
        EXPECT_STREQ("Tuzgolyo3f", strs2.str().c_str());
        Kartya m;
        std::stringstream strs3;
        m.nevKiir(strs3);
        m.manaKiir(strs3);
        m.ikonKiir(strs3);
        EXPECT_STREQ("0 ", strs3.str().c_str());
    }ENDM
    std::cout << "\n=== Karakter tesztek ===\n" << std::endl;
    TEST(Karakter,Kijatszas){
        Karakter karakter("kobold",2,'k',10,10,true);
        int mana = 3;
        EXPECT_TRUE(kartya.kijatszas(&mana,&karakter));
        EXPECT_FALSE(kartya.kijatszas(&mana,&karakter));
    }ENDM
    TEST(Karakter,Sebzes){
        std::stringstream strs;
        std::stringstream strs2;
        Karakter karakter("kobold",2,'k',10,10,true);
        karakter.sebzodik(9,nullptr);
        karakter.nevKiir(strs);
        EXPECT_STREQ("kobold", strs.str().c_str());
        karakter.sebzodik(2,nullptr);
        karakter.nevKiir(strs2);
        EXPECT_STREQ("", strs2.str().c_str());
        
    }ENDM
    TEST(Karakter,Regeneracio){
        std::stringstream strs;
        Karakter karakter("kobold",2,'k',10,10,true);
        karakter.sebzodik(9,nullptr);
        EXPECT_TRUE(karakter.regen(10));
        karakter.sebzodik(9,nullptr);
        karakter.nevKiir(strs);
        EXPECT_STREQ("kobold", strs.str().c_str());
        karakter.sebzodik(20,nullptr);
        EXPECT_FALSE(karakter.regen(10));

    }ENDM
    TEST(Karakter,Aktiv){
        Karakter karakter("kobold",2,'k',10,10,true);
        EXPECT_TRUE(karakter.getAktiv());
        karakter.sebzodik(10,nullptr);
        EXPECT_FALSE(karakter.getAktiv());
        karakter.reaktiv();
        EXPECT_FALSE(karakter.getAktiv());
        Minion m(karakter,20);
        m.tamadas(&karakter);
        EXPECT_FALSE(m.getAktiv());
        m.reaktiv();
        EXPECT_TRUE(m.getAktiv());
    }ENDM
    std::cout << "\n=== Minion tesztek ===\n" << std::endl;
    TEST(Minion,visszatamadas){
        Karakter karakterK("kobold",2,'k',10,10,true);
        Karakter karakterL("lovag",4,'l',20,20,true);
        Minion kobold(karakterK,3);
        Minion lovag(karakterL,20);
        kobold.tamadas(&lovag);
        std::stringstream strs;
        kobold.nevKiir(strs);
        EXPECT_STREQ("", strs.str().c_str());
        
    }ENDM
    TEST(Minion,vedelem&vedelemValt){
        Karakter karakterK("kobold",2,'k',10,10,true);
        Karakter karakterL("lovag",4,'l',20,20,true);
        Minion kobold(karakterK,3);
        Minion lovag(karakterL,20);
        kobold.vedelemValt(20);
        EXPECT_EQ(20,kobold.minionVedelem());
        kobold.sebzodik(10,nullptr);
        EXPECT_EQ(10,kobold.minionVedelem());
        kobold.vedelemValt(20);
        lovag.tamadas(&kobold);
        EXPECT_EQ(10,kobold.minionVedelem());
        kobold.tamadas(&lovag);
        EXPECT_EQ(0,kobold.minionVedelem());
    }ENDM

    std::cout << "\n=== Boss tesztek ===\n" << std::endl;
    TEST(Boss,konstruktor){
        Karakter karakterL("Hos Lovag",0,'L',1,1,true);
        Boss hosLovag(karakterL,2000);
        std::stringstream strs;
        hosLovag.nevKiir(strs);
        hosLovag.ikonKiir(strs);
        EXPECT_STREQ("Hos LovagL", strs.str().c_str());
    }ENDM
    TEST(Boss,special){
        Karakter karakterK("kobold",2,'k',10,10,true);
        Karakter karakterL("Hos Lovag",0,'L',1,1,true);
        Minion kobold(karakterK,3);
        Boss hosLovag(karakterL,2000);
        hosLovag.special(kobold);
        std::stringstream strs;
        kobold.nevKiir(strs);
        EXPECT_STREQ("", strs.str().c_str());
        strs.clear();
        hosLovag.nevKiir(strs);
        EXPECT_STREQ("Hos Lovag", strs.str().c_str());

    }ENDM
    return 0;
}