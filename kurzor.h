/** @file kurzor.h
 *  @brief Kurzor osztály
 *
 *
 *
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

enum irany
{
    jobbra,
    balra,
    fel,
    le
};

class Kurzor
{
    Jatekos p1;
    Jatekos p2;
    Kartya *sel1;
    Kartya *sel2;
    /// @brief Aktív jatekos
    /// megadja melyik az aktív játékos
    int jatekos;
    int fazis;
    /// @brief Melyik sorban van a kurzor
    /// pl: kártyákat válogat vagy minionokat utasít
    int selSzint;

public:
    Kurzor();
    Kurzor(const Jatekos& p1,const Jatekos& p2,int jatekos,int fazis);
    void lepes(irany);
    void kivalaszt();
};

#endif