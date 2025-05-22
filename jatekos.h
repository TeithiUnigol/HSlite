/** @file jatekos.h
  *  @brief 
  *
  *  A két játékos adatait tároló osztály.
  *  Ő felel a játékosok személyes kártyáiért.
  *  A játéktáblán két játékos helyezkedik el, szimmetrikusan.
  *  Minden játékosnak van egy húzópaklija,
  *  egy minionokat tároló paklija, amiben a lehelyezett minionok vannak.
  *  A csomag az amiből az osztály felépíti a húzőpaklit.
  *  Minden körben meghatározott mennyiségű mana áll rendelkezésére a játékosoknak. Ez minden körben egyel nő.
  * 
  *  @author Albitz Csanád
  *  @date 2025-04-20
*/

#ifndef JATEKOS_H
#define JATEKOS_H

#include "kartya.h"
#include "boss.h"
#include "kartyaTarolo.h"

/// @brief A tároló kiválasztásában segít 
enum class TaroloTipus {
  Kez,
  Huzo,
  Minionok
};

class Jatekos{
    /// @brief Maximális mana abban a körben
    int maxMana;
    /// @brief Játékos rendelkezésére álló mana
    int mana;
    ///@brief játékos bossa
    Boss boss;
    KartyaTarolo kez;
    /// @brief húzópakli
    KartyaTarolo huzo;
    ///@brief asztalon levő minionok
    KartyaTarolo minionok;
    /// @brief amiből keveri a húzópaklit
    KartyaTarolo csomag;

public:
    /// @brief Játékos alap konstruktora
    Jatekos();
    /// @brief Játékos konstruktor betöltéshez 
    /// @param boss 
    /// @param huzoPakli 
    /// @param kezPakli 
    /// @param MinionPakli 
    /// @param csomag 
    /// @param maxMana 
    Jatekos(const Boss& boss,const KartyaTarolo& huzoPakli,const KartyaTarolo& kezPakli,const KartyaTarolo& MinionPakli,const KartyaTarolo& csomag,int maxMana,int mana);
    /// @brief Játékos konstruktor
    /// Játék kezdetekor, használandó. Paraméterként a kötelező adatok vannak csak megadva.
    /// @param boss 
    /// @param MinionPakliMeret 
    /// @param kezMeret 
    /// @param csomag 
    /// @param maxMana 
    Jatekos(const Boss& boss,size_t MinionPakliMeret,size_t kezMeret,const KartyaTarolo& csom,int maxMana);
    /// @brief Játékos másoló konstruktor
    /// @param j másolandó
    Jatekos(const Jatekos& j);

    /// @brief Játékos értékadó operátora
    Jatekos& operator=(const Jatekos& forras);

    /// @brief Kézben levő kártyák feltöltése a húzópakliból
    void kezfeltolt();

    /// @brief Új kör indítása
    /// újra aktiválja a minionokat
    void ujKor();
    /// @brief Húzópakli keverés
    /// A csomag lapjait megkeveri és belerakja a húzópakliba.
    ///A megkevert pakliból feltölti a húzópaklit
    void huzopakliKever();
    
    /// @brief Kártya kijátszása
    /// @param k1 kijátszandó kártya memória helye
    /// @param k2 ahova kijátszák a kártyát 
    /// @return sikeres volt-e a kijátszás
    bool Kijatszas(Kartya* k1,size_t index1,Kartya* k2,size_t index2);

  /// @brief Boss getter
  /// @return 
  Boss* Getboss();

  /// @brief Tároló getter
  /// @param tipus 
  /// @return 
  KartyaTarolo& getTarolo(TaroloTipus tipus);

  int getMana()const;

  void mentes(std::ostream& os);

  ~Jatekos();

};
#endif