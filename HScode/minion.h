/** @file minion.h
 *  @brief Minion osztály
 *
 *  Minionok viselkedését írja le.
 *  A minionok az asztalon elhelyezkedő (vagy még kártyaként jelenlevő) karakterek.
 *
 *  @author Albitz Csanád
 *  @date 2025-04-20
 */
#ifndef MINION_H
#define MINION_H

#include "karakter.h"

class Minion : public Karakter
{
private:
  int ero;
  int vedelem;

public:
  /// @brief Minion alapkonstruktora
  Minion();
  /// @brief Minion konstruktora karakter és erő megadásával
  /// @param k
  /// @param ero
  Minion(Karakter &k, int ero);

  ///@brief Konstruktor adattagokkal
  Minion(const char *nev, int mana, char ikon, int hp, int maxhp, bool aktiv, int ero,int vedelem);
  /// @brief Minion konstruktora minion referenciával
  /// @param m
  Minion(Minion &m);

  /// @brief Értékadó operátor
  /// @param minion Amelyik minion adatait másolja
  /// @return Aktuális objektum referencia
  Minion &operator=(const Minion &minion);

  /// @brief Sebződés
  /// Ellentétben a bossal, a minion rendelkezik védelemmel, amely csökkenti a rá kijátszott sebzés mértékét.
  /// A minion (hacsak nem halott) vissza is tud támadni.
  /// @param sebzes A minionra kifejtett sebzés mértéke
  /// @param tamado A karakter, aki megtámadta az adott miniont.
  void sebzodik(int sebzes, Kartya *tamado) override;
  /// @brief Karakter megtámadása
  /// Megtámadja a kiválasztott karaktert
  /// @param celpont A célpont
  void tamadas(Karakter *celpont);
  /// @brief Védelem változtatása
  /// A támadások esetén először a védelem csökken és csak aztán az élets
  /// @param d a védelem megváltoztatásának mértéke
  /// @return sikeres volt-e a védelem változtatása
  void vedelemValt(int d);
  /// @brief Minion lehelyezése
  /// @param mana
  /// @param kiv Az az üres karakterlap, ahova
  bool kijatszas(int *mana, Kartya *kiv);
  /// @brief A minion reaktiválása
  /// A minion minden újraaktiválásnál elveszíti a védelmét is.
  void reaktiv();


  /// @brief Védelem getter
  /// Tesztekzez használt getter
  /// @return védelem
  int minionVedelem();
  /// @brief élet getter
  /// Tesztekzez használt getter
  ///  @return minion élete
  int minionhp();
  /// @brief Karakterből származó minion lekérő
  /// @return true, mivel minion
  bool isMinion();
  void mentes(std::ostream& os) override;
  void betoltes(std::istream &is) override;
  virtual void tartalomkiir(int xBehuz,int Ykezd,bool inKez);
  Kartya* clone() override;
};

#endif