/** @file minion.h
  *  @brief Minion osztály
  *
  *  Minionok viselkedését írja le. 
  *  A miniionok az asztalon elhelyezkedő (vagy még kártyaként jelenlevő) karakterek.
  *
  *  @author Albitz Csanád
  *  @date 2025-04-20
*/
#ifndef MINION_H
#define MINION_H

#include "karakter.h"

class Minion:public Karakter{
private:
    double ero;
    double vedelem;
public:
    /// @brief Minion alapkonstruktora
    Minion();
    /// @brief Minion konstruktora karakter és erő megadásával
    /// @param k 
    /// @param ero 
    Minion(Karakter k,double ero);
    /// @brief Minion konstruktora minion referenciával 
    /// @param m 
    Minion(Minion& m);

    /// @brief Értékadó operátor
    /// @param minion Amelyik minion adatait másolja
    /// @return Aktuális objektum referencia
    Minion &operator=(const Minion &minion);

    /// @brief Sebződés
    /// Ellentétben a bossal, a minion rendelkezik védelemmel, amely csökkenti a rá kijátszott sebzés mértékét.
    /// A minion (hacsak nem halott) vissza is tud támadni.
    /// @param sebzes A minionra kifejtett sebzés mértéke
    /// @param tamado A karakter, aki megtámadta az adott miniont.
    void sebzodik(double sebzes,Karakter* tamado);
    /// @brief Karakter megtámadása
    ///Megtámadja a kiválasztott karaktert
    /// @param celpont A célpont
    void tamadas(Karakter* celpont);
    /// @brief Védelem változtatása
    ///A támadások esetén először a védelem csökken és csak aztán az élets
    /// @param d a védelem megváltoztatásának mértéke
    /// @return sikeres volt-e a védelem változtatása 
    void vedelemValt(double d);
    /// @brief Minion lehelyezése
    /// @param mana 
    /// @param kiv Az az üres karakterlap, ahova 
    bool kijatszas(int* mana,Kartya* kiv);
    /// @brief A minion reaktiválása
    /// A minion minden újraaktiválásnál elveszíti a védelmét is.
    void reaktiv();
};

#endif