/** @file kartya.h
 *  @brief Kartya osztály
 *
 *  Absztrakt ős, amely tartalmazza a minden kártya általános adatait.
 *
 *
 *  @author Albitz Csanád
 *  @date 2025-04-16
 */
#ifndef KARTYA_H
#define KARTYA_H

#include <string>
#include <iostream>
#include <fstream>
#include "econio.h"

class Kartya
{
protected:
  std::string nev;

  int manaKoltseg;

  char ikon;

public:
  /// @brief Kartya alap konstruktora
  Kartya();
  /// @brief Konstruktor adattagokkal
  /// @param nev A kártya neve
  /// @param mana A kártya kijátszásának manaköltsége
  /// @param ikon A karakter megjelenítése során megjelenő ikon
  Kartya(const char *nev, int mana, char ikon);
  /// @brief Másoló konstruktor
  /// @param k A másolandó objektum
  Kartya(const Kartya &k);
  /// @brief Kártya kijátszása
  /// @param mana A jelenleg rendelkezésre álló mana mennyisége.
  ///@param kiv A kiválasztott célpont kártya, amire kifejti hatását.
  /// @return Kijátszható-e a rendelkezésre álló manából.
  virtual bool kijatszas(int *mana, Kartya *kiv);
  /// @brief Értékadó operátor
  /// @param kartya Amelyik kártya adatait másolja
  /// @return Aktuális objektum referencia
  Kartya &operator=(const Kartya &kartya);

  /// @brief Mana getters
  int getMana() const;

  /// @brief Név kiírása
  /// @param os Az output stream ahova kiírja
  void nevKiir(std::ostream &os, size_t maxW) const;
  /// @brief Ikon kiírása
  /// @param os Az output stream ahova kiírja
  void ikonKiir(std::ostream &os) const;

  /// @brief Visszaadja a karakter ikonját 
  /// Ezzel ellenőrzi, hogy a karakter ténylegesen létezik. Ezt egy whitespace karakterrel jelöli.
  char getIkon() const;

  /// @brief Virtuális függvények a karakterekhez 
  virtual int getElet() const;
/// @brief Virtuális függvények a karakterekhez
  virtual void vedelemValt(int d);
  /// @brief Virtuális függvények a karakterekhez
  virtual bool regen(int hp);
/// @brief Virtuális függvények a karakterekhez
  virtual void sebzodik(int sebzes, Kartya *tamado);
  /// @brief Virtuális függvények a karakterekhez
  virtual void tamadas(Kartya *celpont);
/// @brief Tartalom ürítése
  void ures();

  /// @brief Minion-e
  /// @return igaz, ha a karakter minion
  virtual bool isMinion();

  /// @brief Másoló
  /// @return másolat
  virtual Kartya *clone();

  /// @brief Név karakterszáma
  size_t nevMeret();

  /// @brief Kiírást segíti
  virtual bool getAktiv();

  /// @brief Mentés
  /// @param os A megadott folyam, ahova menteni szeretnénk.
  //virtual void mentes(std::ostream &os);
  /// @brief Betöltés
  /// @param os A megadott folyam, ahova menteni szeretnénk.
  virtual void betoltes(std::istream &is);
  /// @brief Virtuális függvények a karakterekhez
  virtual void reaktiv();
  /// @brief Virtuális függvények a karakterek kiírásához
  virtual void tartalomkiir(int xBehuz, int Ykezd, bool inKez);

  /// @brief Kártya destruktor
  virtual ~Kartya();
};
#endif
