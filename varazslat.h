/** @file varazslat.h
  *  @brief Varázylatok
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

class Varazslat:public Kartya{
    double sebzes;
    double gyogyitas;
    double vedelem;     
public:
    /// @brief Alap konstruktor
    Varazslat();
    /// @brief Másoló konstruktor
    /// @param v másolandó objektum
    Varazslat(Varazslat& v);
    /// @brief Konstruktor adattagokkal
    /// @param nev Varázslat neve
    /// @param mana Varázslat manaköltsége
    /// @param ikon Varázslat ikonja
    /// @param sebzes Varázslat sebzése
    /// @param gyogyitas Varázslat gyógyítása
    /// @param vedelem Varázslat védelem növelése
    Varazslat(const char *nev, int mana, char ikon,double sebzes,double gyogyitas,double vedelem);
    /// @brief kijátszás
    /// @param mana A rendelkezésre álló mana mennyisége
    /// @param kiv a célpont
    /// @return skeres volt-e a kijátszás 
    bool kijatszas(int* mana,Karakter& kiv);
};

#endif