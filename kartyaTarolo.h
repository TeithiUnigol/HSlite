/** @file kartyaTarolo.h
  *  @brief Kártya tároló osztály
  *
  *  A minionok, a húzópakli és a kézben levő paklit tároló heterogén kollekcióért felelős osztály
  *  A tároló működéséhez szükséges, hogy annyi elemmel hozzák létre, amennyit tárolni szeretne
  *
  *  @author Albitz Csanád
  *  @date 2025-04-20
*/
#ifndef KARTYATAROLO_H
#define KARTYATAROLO_H

#include "kartya.h"

class KartyaTarolo{
    Kartya** tomb;
    size_t kapacitas;
    size_t meret;
public:
    /// @brief Tároló alapkonstruktora
    KartyaTarolo();
    /// @brief Kártya tároló kapacítás szerinti konstruktora.
    /// @param kapacitas Az a méret amekkorára szükség lesz.
    KartyaTarolo(size_t kapacitas);
    /// @brief Kártyatároló másolókonstruktora
    /// @param  a másolandó tároló referenciája
    KartyaTarolo(const KartyaTarolo& t);
    /// @brief Értékadó operátor
    /// @param rhs forrás
    KartyaTarolo& operator=(const KartyaTarolo& rhs);
    /// @brief Feltöltés
    ///A kártyapakli összekeveréséért felel.
    /// @param Kartya A behelyezendő kártya
    void randomBeszur(Kartya* kartya);
    /// @brief Soros feltöltés
    /// Csak sorba feltöltött tároló esetén működik (pl fájlbetöltésnél)
    /// @param kartya A következő elem
    ///@param index A hely ahova berakja az adott elemet
    void berak(Kartya* kartya,size_t index);
    /// @brief Kihúzás megadott indexről
    /// @param index A megadott index
    /// @return A kihúzott kártya adatai.
    Kartya* kihuz(size_t index);
    /// @brief Tárolóban levő tényleges elemek számának lekérése
    /// @return Ezeknek a száma
    size_t getMeret() const;
    /// @brief Tároló kapacításának lekérése
    /// @return Tároló kapacítása
    size_t getKapacitas()const;
    /// @brief Indexelő operátor
    /// @param index 
    /// @return 
    Kartya* operator[](size_t index);
    /// @brief Tároló ürítése
    void kiurites();
    /// @brief Tároló destruktora
    ~KartyaTarolo();
};
#endif