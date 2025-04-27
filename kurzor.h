/** @file kurzor.h
  *  @brief 
  *
  *  
  *  
  *
  *  @author Albitz Csanád
  *  @date 2025-04-20
*/

#ifndef KURZOR_H
#define KURZOR_H

#include "kartya.h"
#include "boss.h"
#include "kartyaTarolo.h"
#include "jatekos.h"

enum irany{
    jobbra,balra,fel,le 
};

class Kurzor{
    Jatekos p1;
        Jatekos p2;
        Kartya* sel1;
        Kartya* sel2;
        int jatekos;
        int Fazis;
        int selSzint;

public:
    Kurzor();
    Kurzor(Boss boss,KartyaTarolo huzoPakli,KartyaTarolo kezPakli,KartyaTarolo MinionPakli,int maxMana);
    void lepes(irany);
    void kivalaszt();
};

#endif