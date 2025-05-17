#include "boss.h"

Boss::Boss():Karakter(),specialSebzes(0){}

Boss::Boss(Karakter &karakter,int special):Karakter(karakter),specialSebzes(special){}

Boss::Boss(const Boss &boss):Karakter(boss),specialSebzes(boss.specialSebzes){}

Boss::Boss(const char *nev, int mana, char ikon, int hp, int maxhp, bool aktiv, int special)
    : Karakter(nev,mana,ikon,hp,maxhp,aktiv),specialSebzes(special) {}

void Boss::special(Karakter &k){
    if (aktiv)
    {       
        k.sebzodik(specialSebzes,nullptr);
        this->aktiv = false;
    }
}

int Boss::getSpecial() const{
    return specialSebzes;
}

void Boss::mentes(std::ostream& os){
    os << "BOSS " << nev << " " << manaKoltseg << " " << ikon << " " << hp <<" " << maxHp << " " << aktiv << " " << specialSebzes<<std::endl;
}

Kartya* Boss::clone() {
    return new Boss(*this);
}