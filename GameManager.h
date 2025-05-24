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

typedef enum colors
{
    white,
    black,
    red,
    green,
    gray,
    yellow
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
    
    /// fut-e a játék
    bool isJatek;
    
    /// @brief Kiíráshoz szükséges konstans adattagok
    /// képernyő szélessége
    const size_t screenW;
    /// egy blokk szélessége
    const size_t blokkW;
    ///Belső adattagok magassága 
    const size_t blokkH;
    /// két blokk közti távolság
    const size_t separatorS;
    
    /// @brief Forrásfile
    std::string pakliFile;
    //------------Segédfüggvények--------------
    void changeBG(colors color);
    void changeTxt(colors color);
    Jatekos *JatekosKivalaszt(int j);
    size_t intHossz(int n);
    
    //------------UI rész--------------
    public:
    //void bossKartya(int jatekos,int startY);
    void MenuSelect();
    
    
    private:
    /// @brief Egy kártya kiírása
    void KartyaKiir(int xBehuz, int yKezd,Kartya* k,bool inkez,bool isSel,bool isMov);
    /// @brief Egy egész sor tároló kiírása
    void printTarolo(int yKezd,int yMeret,KartyaTarolo& tarolo,bool isKez,int melyikJatekose);
    /// @brief Játékvége üzenet
    bool endGameScreen(int gyoz);
    /// @brief kártya vízszintes szegélye
    void felsoVonal(int xBehuz,int yKezd);
    /// @brief Egy kártya horizontáslis szegélye
    void belsoFal(int behuzasX,int yKezd);
    /// @brief Üres kártya minta 
    /// @param xBehuz mennyivel legyen beljebb
    /// @param yMeret Hány karakter hosszú legyen az adattagok sáv
    void printUresKartya(int xBehuz,int yMeret,int yKezd);
    
    //------------Játéklogika--------------
    /// @brief Kiválaszt
    /// Akkor hívódik meg, amikor a felhasználó arra a kártyára mozgatta a kurzort, amelyiket ki akarja választani.
    void kivalaszt();
    /// @brief Következő fázis
    /// Akkor hívódik meg, amikor a felhasználó már nem kíván több dolgot csinálni az aktuális fázisban.
    void kovFazis();
    
    public:
    GameManager(size_t screenW, size_t blokkW,size_t blokkH, size_t separatorS,std::string pakliforras);
    GameManager(const Jatekos& jat1,const Jatekos &jat2, size_t screenW, size_t blokkW,size_t blokkH, size_t separatorS);
    /// @brief Játékvezérlő logika
    void game();
    /// @brief Játék grafikus megjelenítése
    void printGame();
    //------------filekezelés logika--------------
    void loadPakli();
    ~GameManager();
};


#endif