/** @file varazslat.h
 *  @brief Varázslat osztály
 *
 *  Kartya egy alosztálya. Célja az egyszeri hatású mágiák definiálása.
 *
 *
 *  @author Albitz Csanád
 *  @date 2025-04-20
 */
#ifndef VARAZSLAT_H
#define VARAZSLAT_H

#include "kartya.h"
#include "karakter.h"
#include "memtrace.h"

class Varazslat : public Kartya
{
  int sebzes;
  int gyogyitas;
  int vedelem;

public:
  /// @brief Alap konstruktor
  Varazslat();
  /// @brief Másoló konstruktor
  /// @param v másolandó objektum
  Varazslat(Varazslat &v);
  /// @brief Konstruktor adattagokkal
  /// @param nev Varázslat neve
  /// @param mana Varázslat manaköltsége
  /// @param ikon Varázslat ikonja
  /// @param sebzes Varázslat sebzése
  /// @param gyogyitas Varázslat gyógyítása
  /// @param vedelem Varázslat védelem növelése
  Varazslat(const char *nev, int mana, char ikon, int sebzes, int gyogyitas, int vedelem);
  /// @brief kijátszás
  /// @param mana A rendelkezésre álló mana mennyisége
  /// @param kiv a célpont
  /// @return skeres volt-e a kijátszás
  bool kijatszas(int *mana, Kartya *kiv);
  void mentes(std::ostream &os) override;
  void betoltes(std::istream &is) override;
  void tartalomkiir(int xBehuz, int Ykezd, bool inKez) override;
  Kartya *clone() override;
};

#endif