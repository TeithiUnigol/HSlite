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

class Jatekos{
    int maxMana;
    int mana;
    Boss boss;
    KartyaTarolo kez;
    /// @brief húzópakli
    KartyaTarolo huzo;
    ///@brief asztalon levő minionok
    KartyaTarolo minionok;
    /// @brief amiből keveri a húzópaklit
    KartyaTarolo csomag;

public:
    Jatekos();
    /// @brief Játékos konstruktor betöltéshez 
    /// @param boss 
    /// @param huzoPakli 
    /// @param kezPakli 
    /// @param MinionPakli 
    /// @param csomag 
    /// @param maxMana 
    Jatekos(Boss boss,KartyaTarolo huzoPakli,KartyaTarolo kezPakli,KartyaTarolo MinionPakli,KartyaTarolo csomag,int maxMana);
    /// @brief Játékos konstruktor
    /// Játék kezdetekor, használandó. Paraméterklnt a kötelező adatok vannak csak megadva.
    /// @param boss 
    /// @param MinionPakliMeret 
    /// @param kezMeret 
    /// @param csomag 
    /// @param maxMana 
    Jatekos(Boss boss,size_t MinionPakliMeret,size_t kezMeret,KartyaTarolo csomag,int maxMana);
    /// @brief Játékos másoló konstruktor
    /// @param j másolandó
    Jatekos(const Jatekos& j);

    /// @brief Kézben levő kártyák feltöltése a húzópaklibóly
    void kezfeltolt();

    /// @brief Új kör indítása
    /// újra aktiválja a minionokat
    void ujKor();
    /// @brief Húzópakli keverés
    /// A csomag lapjait megkeveri és belerakja a húzópakliba.
    ///A megkevert pakliból feltölti a húzópaklit
    void huzopakliKever();
    
    //TODO dolgok, amikkel a kurzor megkapja az infokat
    bool Kijatszas(Kartya* k1,Kartya* k2);

};
#endif