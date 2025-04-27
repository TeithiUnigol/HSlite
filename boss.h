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
#include "varazslat.h"

class Boss:public Karakter{
  double specialSebzes;
public:
    /// @brief Alap konstruktor
    Boss();
    /// @brief 
    /// @param karakter 
    Boss(Karakter& karakter,double special);

    /// @brief Speciális támadás
    /// A megtámadott minion nem tud visszatámadni 
    /// @param k A célpont
    void special(Karakter& k);
};

#endif