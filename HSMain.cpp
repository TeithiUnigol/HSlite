

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

int main(){
    //#ifdef CPORTA
    //#endif
    /*
    GTINIT(std::cout);
    
    std::cout << "\n=== Kartya tesztek ===\n" << std::endl;
    TEST(Kartya,isminion){
        Kartya kartya("kobold",2,'k');
        EXPECT_FALSE(kartya.isMinion());
    }ENDM
    TEST(Kartya,Konstruktorok){
        std::stringstream strs;
        Kartya kartya("Tuzgolyo",3,'f');
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
        EXPECT_TRUE(karakter.kijatszas(&mana,&karakter));
        EXPECT_FALSE(karakter.kijatszas(&mana,&karakter));
    }ENDM
    TEST(Karakter,isminion){
        Karakter karakter("kobold",2,'k',10,10,true);
        EXPECT_FALSE(karakter.isMinion());
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
        EXPECT_STREQ(" ", strs2.str().c_str());
        
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
        EXPECT_STREQ(" ", strs.str().c_str());
        
    }ENDM
    TEST(Minion,vedelem&vedelemValt){
        Karakter karakterK("kobold",2,'k',10,10,true);
        Karakter karakterL("lovag",4,'l',20,20,true);
        Minion kobold(karakterK,3);
        Minion lovag(karakterL,20);
        lovag.tamadas(&kobold);
        EXPECT_FALSE(kobold.regen(10));
    }ENDM
    TEST(Minion,Isminion){
        Karakter karakterK("kobold",2,'k',10,10,true);
        Minion kobold(karakterK,3);
        EXPECT_TRUE(kobold.isMinion());
        
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
    TEST(Boss,isminion){
        Boss boss("kobold",2,'k',10,10,true,1);
        EXPECT_FALSE(boss.isMinion());
    }ENDM
    TEST(Boss,special){
        Karakter karakterK("kobold",2,'k',10,10,true);
        Karakter karakterL("Hos Lovag",0,'L',1,1,true);
        Minion kobold(karakterK,3);
        Boss hosLovag(karakterL,2000);
        hosLovag.special(kobold);
        std::stringstream strs;
        kobold.nevKiir(strs);
        EXPECT_STREQ(" ", strs.str().c_str());
        strs.clear();
        hosLovag.nevKiir(strs);
        EXPECT_STREQ(" Hos Lovag", strs.str().c_str());

    }ENDM
*/




    #ifndef CPORTA

    


    #endif
    /*std::cout << "\n=== Egyszerubb jatek pelda ===\n" << std::endl;
    ///Egyszerűbb játék    
    Karakter karakterS("Sotet Lovag",0,'L',1,1,true);
    Boss sotetLovag(karakterS,2000);
    
    Karakter karakterK("kobold",2,'k',10,10,true);
    Minion kobold(karakterK,3);

    Karakter karakterSar("Sarkany",2,'S',40,40,true);
    Minion sari(karakterSar,15);

    Varazslat nekro("nekromanta",2,'n',0,3,10);
    Varazslat savasE("savas eso",2,'s',10,0,0);



    Karakter karakterL("Hos Lovag",0,'L',1,1,true);
    Boss hosLovag(karakterL,2000);

    Karakter karakterG("gyalog",2,'g',10,10,true);
    Minion gyalog(karakterG,3);

    Karakter karakterSO("Sarkanyolo",2,'S',40,40,true);
    Minion sariOlo(karakterSO,15);

    Varazslat gyogy("gyogyitas",2,'n',0,3,10);
    Varazslat nyilz("nyilzapor",2,'s',10,0,0);

    KartyaTarolo csomag1(10);
    KartyaTarolo csomag2(10);
    size_t i1;
    //Ez majd fájlból ovasással lesz megoldva 
    csomag1.berak(&sari,i1++);
    for (size_t i = 0; i < 2; i++)
    {
        csomag1.berak(&nekro,i1++);
    }
    for (size_t i = 0; i < 2; i++)
    {
        csomag1.berak(&savasE,i1++);
    }
    for (size_t i = 0; i < 5; i++)
    {
        csomag1.berak(&kobold,i1++);
    }

    csomag2.berak(&sariOlo,i1++);
    for (size_t i = 0; i < 2; i++)
    {
        csomag2.berak(&gyogy,i1++);
    }
    for (size_t i = 0; i < 2; i++)
    {
        csomag2.berak(&nyilz,i1++);
    }
    for (size_t i = 0; i < 5; i++)
    {
        csomag2.berak(&gyalog,i1++);
    }
    
    Jatekos j1(sotetLovag,5,5,csomag1,3);
    Jatekos j2(hosLovag,5,5,csomag2,3);
    Kurzor k(j1,j2,0,0);
    //billentyűlenyomásokkal navigálás rész: nyilakkat a lépésbe, entert pedig a kiválasztba
    

*/
    return 0; 
}