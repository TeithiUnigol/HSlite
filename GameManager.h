/** @file GameManager.h
 *  @brief GameManager
 *
 *  Ő felel a felhasználótól érkező inputok feldolgozásáért.
 *  Nyomonköveti a játék állását.
 *  Egyszerre funkcionál játék managerként és inputmanagerként.
 *
 *  @author Albitz Csanád
 *  @date 2025-05-7
 */

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "econio.h"
#include "kartya.h"
#include "karakter.h"
#include "minion.h"
#include "boss.h"
#include "kartyaTarolo.h"
#include "jatekos.h"
#include "kurzor.h"
#include "varazslat.h"

#include <iostream>
#include <fstream>


typedef enum menuState
{
    mainMenu,
    game,
    quit
} menuState;



/// @brief Game Manager
/// Az UI kezeléséért, adatok mentésének vezérléséért felelős. Összeköti a játéklogikát a felhasználói bemenetekkel és kimenetekkel.
class GameManager
{
private:
    /// @brief Aktív jatekos
    /// megadja melyik az aktív játékos
    int jatekos;
    int fazis;

    Jatekos *j1;
    Jatekos *j2;
    Kurzor kurz;

    /// @brief Kiíráshoz szükséges konstans adattagok
    /// képernyő szélessége
    const size_t screenW;
    /// egy blokk szélessége
    const size_t blokkW;
    /// két blokk közti távolság
    const size_t separatorS;

    //------------Segédfüggvények--------------
    Jatekos *JatekosKivalaszt(int j);
    size_t intHossz(int n);

    //------------UI rész--------------
    public:
    void bossKartya(int jatekos,int startY);


    private:
    void bossvonal();
    void taroloVonal(size_t fal, size_t cap);
    void bossSzel(size_t s1, size_t s2);
    void printBoss(int jatekos);
    void printKartyak(KartyaTarolo &k);
    void printMinion(KartyaTarolo &m);

    //------------Játéklogika--------------
    /// @brief Kiválaszt
    /// Akkor hívódik meg, amikor a felhasználó arra a kártyára mozgatta a kurzort, amelyiket ki akarja választani.
    void kivalaszt();
    /// @brief Következő fázis
    /// Akkor hívódik meg, amikor a felhasználó már nem kíván több dolgot csinálni az aktuális fázisban.
    void kovFazis(int fazis);

public:
    void printGame();
    //------------Mentés logika--------------
    void loadPakli(char *fileName);
    void savePakli(char *fileName);

    GameManager(size_t screenW, size_t blokkW, size_t separatorS);
    GameManager(Jatekos *jat1, Jatekos *jat2, size_t screenW, size_t blokkW, size_t separatorS);

    ~GameManager();
};

#endif