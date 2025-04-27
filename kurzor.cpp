#include "kurzor.h"
#include "boss.h"
#include "kartyaTarolo.h"

/*Jatekos p1;
Jatekos p2;
    Kartya sel1;
    Kartya sel2;
    int jatekos;
    int Fazis;
    int selSzint;*/


Kurzor::Kurzor(): p1(), p2(),jatekos(0),fazis(0), selSzint(0), sel1(nullptr), sel2(nullptr) {}

Kurzor::Kurzor(const Jatekos& p1,const Jatekos& p2,int jatekos,int fazis):
    p1(p1),p2(p2), jatekos(jatekos),fazis(fazis), selSzint(0), sel1(nullptr), sel2(nullptr){

}
void Kurzor::lepes(irany){

}
void Kurzor::kivalaszt(){
    
}