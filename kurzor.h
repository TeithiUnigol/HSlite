/** @file kurzor.h
 *  @brief Kurzor osztály
 *
 *  Ő felel a felhasználótól érkező inputok feldolgozásáért.
 *  Nyomonköveti a játék állását.
 *  Egyszerre funkcionál játék managerként és inputmanagerként.
 *
 *  @author Albitz Csanád
 *  @date 2025-04-20
 */

#ifndef KURZOR_H
#define KURZOR_H

#include "kartya.h"
#include "boss.h"
#include "kartyaTarolo.h"
#include "jatekos.h"
#include "memtrace.h"

enum irany
{
    jobbra,
    balra,
    fel,
    le
};


/// @brief A kurzor pozícióját és az aktuálisan kijelölt kártyát tárolja.
/// A szint tag különböző játékszakaszokban (fázisokban) eltérő értelmezést kap.
struct mozgo
{
    Kartya *pointer;
    size_t index;
    int szint;//TODO átírni
    mozgo()
    {
        pointer = nullptr;
        index = 0;
        szint = -1;
    }
    mozgo(mozgo& moz){
        pointer = moz.pointer;
        index = moz.index;
        szint = moz.szint;
    }
};

class Kurzor
{
    Jatekos* p1;
    Jatekos* p2;

    mozgo mov_a;
    mozgo sel1_a;


    
    public:
    /// @brief Kurzor alapkonstruktor
    Kurzor();
    /// @brief Kurzor konstruktor adattagokkal
    /// @param p1 egyes számú játékos
    /// @param p2 kettes számú játékos
    Kurzor(Jatekos* p1,  Jatekos* p2);
    /// @brief Lépés kezelése
    /// A feladata vezérelni a fazis1Lepes és fazis2Lepes függvényt
    /// @param ir inputnak kapott lépés irány
    void lepes(irany ir,int fazis,int jatekos,Jatekos* aktJ);
    
    /// @brief kurzor értékadó operátora
    /// @param kurz 
    /// @return 
    Kurzor& operator=(const Kurzor &kurz);
    
    /// @brief Moz gettere
    /// @return moz
    mozgo& getMov();
    /// @brief sel1 gettere
    /// @return sel1
    mozgo& getSel1();
    
    /// @brief Kiválasztás
    /// @return 
    bool kivalaszt(int fazis,Jatekos* aktJ,Jatekos* ellenfelJ,int jatekos);
    private:
    /// A privát segédfüggvények
    
    /// @brief Első fázis mozgás
    /// Ekkor történik akártyák kijátszása a kézből.
    /// @param ir inputnak kapott lépés irány
    void fazis1Lepes(irany ir,int jatekos,Jatekos* aktJ);
    /// @brief Minion lerakás segédfüggvény
    /// Az 1. fázis lerakásának könnyebb átláthatósága érdekében
    /// @param ir
    void MinionLerakas(irany ir, size_t &index,int jatekos,Jatekos* aktJ);
    /// @brief Második fázis mozgás
    /// Ekkor történik a minionokkal illetve a bossal való támadás
    /// @param ir inputnak kapott lépés irány
    void fazis2Lepes(irany ir,int jatekos);

    /// @brief A megfelelő szinten levő kártya kiválasztása
    /// A meghatározott kártyára állítja a movot
    ///@param A horizontális koordináta
    void SzintDekoder();

    /// @brief körkörös léptető segédfüggvény
    /// @tparam T Egy egész szám
    /// @param gorgetendo görgetendő
    /// @param poz növelje, vagy csökentse
    /// @param maxT a határ
    template <typename T>
    void gorgeto(T &gorgetendo, bool poz, T maxT);


    
};

#endif