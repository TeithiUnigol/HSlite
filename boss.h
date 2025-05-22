/** @file boss.h
 *  @brief A játékosok főkaraktere
 *
 *  Ezen karakter védelme a legfontosabb a játékban.
 *  Az a játékos veszít, akié meghal.
 *
 *  @author Albitz Csanád
 *  @date 2025-04-20
 */

#ifndef BOSS_H
#define BOSS_H
#include "karakter.h"


class Boss : public Karakter
{
  int specialSebzes;

public:
  /// @brief Alap konstruktor
  Boss();
  /// @brief Boss konstruktora karakter és speciális megadásával
  /// @param karakter
  Boss(Karakter &karakter, int special);
  /// @brief Karakter konstruktor adatokkal
  /// @param nev karakter neve
  /// @param mana karakter kijátszásához szükséges manaszint (egy bossbál ez elhanyagolható,
  /// mivel bossból csak egy van, ami a játék elejétől kezdve létezik)
  /// @param ikon
  ///@param hp
  /// @param maxhp
  /// @param aktiv
  Boss(const char *nev, int mana, char ikon, int hp, int maxhp, bool aktiv, int special);
  /// @brief Boss másoló konstruktor
  /// @param boss  másolandó
  Boss(const Boss &boss);

  /// @brief Speciális támadás
  /// A megtámadott minion nem tud visszatámadni
  /// @param celpont A célpont
  void tamadas(Kartya *celpont);

  void mentes(std::ostream &os) override;
  void betoltes(std::istream &is) override;

void tartalomkiir(int xBehuz,int Ykezd,bool inKez);

  Kartya *clone() override;
};

#endif