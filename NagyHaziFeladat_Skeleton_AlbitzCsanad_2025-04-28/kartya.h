/** @file kartya.h
  *  @brief Kartya osztály 
  *
  *  Absztrakt ős, amely tartalmazza a minden kártya általános adatait.
  *  
  *
  *  @author Albitz Csanád
  *  @date 2025-04-16
*/
#ifndef KARTYA_H
#define KARTYA_H

#include <string>
#include <iostream>

class Kartya
{
protected:
    const static int maxNevMeret;
    
    const static int maxManaMeret;
    
    std::string nev;
    
    int manaKoltseg;
    
    char ikon;

public:
    /// @brief Kartya alap konstruktora
    Kartya();
    /// @brief Konstruktor adattagokkal
    /// @param nev A kártya neve 
    /// @param mana A kártya kijátszásának manaköltsége
    /// @param ikon A karakter megjelenítése során megjelenő ikon
    Kartya(const char *nev, int mana, char ikon);
    /// @brief Másoló konstruktor
    /// @param k A másolandó objektum
    Kartya(const Kartya &k);
    /// @brief Kártya kijátszása
    /// @param mana A jelenleg rendelkezésre álló mana mennyisége. 
    ///@param kiv A kiválasztott célpont kártya, amire kifejti hatását. 
    /// @return Kijátszható-e a rendelkezésre álló manából.
    virtual bool kijatszas(int* mana,Kartya* kiv);
    /// @brief Értékadó operátor
    /// @param kartya Amelyik kártya adatait másolja
    /// @return Aktuális objektum referencia
    Kartya &operator=(const Kartya &kartya);

    /// @brief Mana kiírása
    /// @param os Az output stream ahova kiírja
    void manaKiir(std::ostream& os)const;
    /// @brief Név kiírása
    /// @param os Az output stream ahova kiírja
    void nevKiir(std::ostream& os) const;
    /// @brief Ikon kiírása
    /// @param os Az output stream ahova kiírja
    void ikonKiir(std::ostream& os) const;

    /// @brief Kártya destruktor
    virtual ~Kartya();

};
#endif