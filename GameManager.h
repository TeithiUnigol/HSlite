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

typedef enum colors
{
    white,
    black,
    red,
    green,
    gray
} colors;

typedef enum menuState
{
    mainMenu,
    game,
    quit
} menuState;

/// @brief Game Manager
/// A grafika kezeléséért, mentéséért felelős. Összeköti a játéklogikát a felhasználói bemenetekkel és kimenetekkel.
class GameManager
{
private:
    /// @brief Aktív jatekos
    /// megadja melyik az aktív játékos
    int jatekos;
    int fazis;

    Jatekos j1;
    Jatekos j2;
    Kurzor kurz;

    void printMinionDeck(size_t size, KartyaTarolo k);

    void printBoss(Boss b);


    void printPakli(KartyaTarolo pakli);

public:
    GameManager();
    ~GameManager();
};

#endif