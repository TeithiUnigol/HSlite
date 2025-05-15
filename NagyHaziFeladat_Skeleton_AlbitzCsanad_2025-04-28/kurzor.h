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
    /// @brief lépő
    ///A léptetés során ez
    Kartya *mov;
    /// @brief Aktív jatekos
    /// megadja melyik az aktív játékos
    int jatekos;
    int fazis;
    /// @brief Melyik sorban van a kurzor
    /// A különböző fázisokban különböző szintek vannak:
    ///Az első fázisban a sel1-et csak a kézből lehet kiválasztani,
    ///míg a sel2-t minionkártya esetén csak a játékos saját minion tárolójából, onnan is csak az üres helyre.
    ///Varázskártyát pedig bármelyik karakterre kijátszható (mind az ellenség, mind a saját minionjaira és bossaira)
    ///A második fázisban a sel1 a boss vagy a minionok közül való, a sel2 pedig az ellenség minionjai és bossa közül.
    int selSzint;

public:
    /// @brief Kurzor alapkonstruktor
    Kurzor();
    /// @brief Kurzor konstruktor adattagokkal
    /// @param p1 egyes számú játékos
    /// @param p2 kettes számú játékos
    /// @param jatekos melyik játékos van éppen körön
    /// @param fazis a játékos melyik fázisban van
    Kurzor(const Jatekos& p1,const Jatekos& p2,int jatekos,int fazis);
    /// @brief Lépés kezelése
    /// A feladata vezérelni a fazis1Lepes és fazis2Lepes függvényt
    /// @param ir inputnak kapott lépés irány
    void lepes(irany ir);
    /// @brief Első fázis mozgás
    /// Ekkor történik akártyák kijátszása a kézből.
    /// @param ir inputnak kapott lépés irány
    void fazis1Lepes(irany ir);
    /// @brief Második fázis mozgás
    /// Ekkor történik a minionokkal illetve a bossal való támadás
    /// @param ir inputnak kapott lépés irány 
    void fazis2Lepes(irany ir);
    /// @brief Kiválaszt
    /// Akkor hívódik meg, amikor a felhasználó arra a kártyára mozgatta a kurzort, amelyiket ki akarja választani.
    void kivalaszt();
    /// @brief Következő fázis
    ///Akkor hívódik meg, amikor a felhasználó már nem kíván több dolgot csinálni az aktuális fázisban.
    void kovFazis();
    /// @brief Aktuális játékos getter
    /// @return Aktuális játékos referencia
    Jatekos& aktJatekos();
};

#endif