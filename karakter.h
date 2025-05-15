/** @file karakter.h
 *  @brief Karakterek
 *
 *  A karakterek definíciója.
 *  Ez egy absztrakt osztály, mely elősegíti a minion és boss definiálását.
 *
 *  @author Albitz Csanád
 *  @date 2025-04-20
 */
#ifndef KARAKTER_H
#define KARAKTER_H

#include "kartya.h"

class Karakter : public Kartya
{
protected:
  double hp;
  double maxHp;
  bool aktiv;

public:
  /// @brief Karakter alap konstruktora
  Karakter();
  /// @brief Karakter másoló konstruktor
  /// @param v a másolandó karakter
  Karakter(const Karakter &v);
  /// @brief Karakter konstruktor adatokkal
  /// @param nev karakter neve
  /// @param mana karakter kijátszásához szükséges manaszint (egy bossbál ez elhanyagolható,
  /// mivel bossból csak egy van, ami a játék elejétől kezdve létezik)
  /// @param ikon
  ///@param hp
  /// @param maxhp
  /// @param aktiv
  Karakter(const char *nev, int mana, char ikon, double hp, double maxhp, bool aktiv);
  /// @brief Támadás
  /// A karakterre meghatározott mértékű sebzést okoz. A minion védelemmel csökkentheti a sebződést, de a boss nem.
  /// @param sebzes a sebzés mértéke
  /// @param tamado a támadó
  virtual void sebzodik(double sebzes,Kartya* tamado);
  /// @brief gyógyítás
  /// @param hp gyógyítás mértéke
  /// @return
  bool regen(int hp);
  /// @brief Aktív lekérése
  /// @return aktív-e az állapot.
  bool getAktiv();
  ///@brief Újra aktiválás
  /// Újra aktívra állítja a karaktert. Ezt minden kör végén meghívódik
  virtual void reaktiv();
  /// @brief Értékadó operátor
  /// @param karakter Amelyik karakter adatait másolja
  /// @return Aktuális objektum referencia
  Karakter &operator=(const Karakter &karakter);
  /// @brief Halál
  /// Ha elfogyott az élete az adott karakternek, üres karakterré válik.
  void halal();
  
  /// @brief Élet lekérdezése
  /// pusztán a teszteléshez szükséges
  /// @return S karakter élete.
  double elet();


  
};
#endif