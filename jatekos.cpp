#include "jatekos.h"
#include "minion.h"

Jatekos::Jatekos():maxMana(0),boss(),kez(0),huzo(0),minionok(0),csomag(0){}

Jatekos::Jatekos(Boss boss,KartyaTarolo huzoPakli,KartyaTarolo kezPakli,KartyaTarolo MinionPakli,KartyaTarolo csomag,int maxMana):
        maxMana(maxMana),boss(boss),kez(kezPakli),huzo(huzoPakli),minionok(MinionPakli),csomag(csomag){}
Jatekos:: Jatekos(Boss boss,size_t MinionPakliMeret,size_t kezMeret,KartyaTarolo csomag,int maxMana):
        maxMana(maxMana),boss(boss),kez(kezMeret),huzo(csomag.getKapacitas()),minionok(MinionPakliMeret),csomag(csomag){
    huzopakliKever();
}
Jatekos::Jatekos(const Jatekos& j):maxMana(j.maxMana), boss(j.boss), kez(j.kez), huzo(j.huzo), minionok(j.minionok), csomag(j.csomag){}

void Jatekos::kezfeltolt(){
    int index = 0;
    
    while(kez.getMeret()!=kez.getKapacitas()&&huzo.getMeret()>0){
        kez.berak(huzo.kihuz(huzo.getMeret()-1),index);
        ++index;
    }
}


void Jatekos::ujKor(){
    for (size_t i = 0; i < minionok.getKapacitas(); i++)
    {
        //Másik ötlet: kartyaTarolo módosítása
        
        Minion* M =dynamic_cast<Minion*>(minionok[i]);
        if (M!=nullptr)
        {
            M->reaktiv();
        }
        
    }
    kezfeltolt();
    ++maxMana;
    mana = maxMana;

}


void Jatekos::huzopakliKever(){
    huzo.kiurites();
    for (size_t i = 0; i < csomag.getMeret(); i++)
    {
        huzo.randomBeszur(csomag[i]);
    }
    
}

bool Jatekos::Kijatszas(Kartya* k1,Kartya* k2){
    bool ret = k1->kijatszas(&mana,k2);
    return ret;
}

Boss& Jatekos::Getboss(){
    return this->boss;
}

KartyaTarolo& Jatekos::getTarolo(TaroloTipus tipus) {
    switch (tipus) {
        case TaroloTipus::Kez:
            return kez;
        case TaroloTipus::Huzo:
            return huzo;
        case TaroloTipus::Minionok:
            return minionok;
        default:
            throw "NincsIlyen";
    }
}