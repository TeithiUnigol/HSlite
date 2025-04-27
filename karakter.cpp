#include "karakter.h"

Karakter::Karakter() : Kartya(), hp(0), maxHp(0), aktiv(false) {}

Karakter::Karakter(Karakter &v):hp(v.hp),maxHp(v.maxHp),aktiv(v.aktiv) {}

Karakter::Karakter(const char *nev, int mana, char ikon, double hp, double maxhp, bool aktiv)
    : Kartya(nev, mana, ikon), hp(maxhp), maxHp(maxhp), aktiv(true) {}

void Karakter::vedelemValt(double d) {}

void Karakter::sebzodik(double sebzes, Karakter *tamado)
{
    hp -= sebzes;
    if (hp <= 0)
    {
        halal();
    }
}

bool Karakter::regen(int hp)
{
    if (this->hp <= 0)
    {
        return false;
    }
    this->hp += hp;
    if (this->hp > this->maxHp)
    {
        this->hp = this->maxHp;
    }
    return true;
}

bool Karakter::getAktiv()
{
    return aktiv;
}

void Karakter::reaktiv()
{
    if (this->hp>0)
    {   
        aktiv = true;
    }
}

Karakter &Karakter::operator=(const Karakter &karakter)
{
    if (this != &karakter)
    {
        Kartya::operator=(karakter);
        this->hp = karakter.hp;
        this->maxHp = karakter.maxHp;
        this->aktiv = karakter.aktiv;
    }
    return *this;
}

void Karakter::halal()
{
    Kartya null;
    Kartya::operator=(null);
    this->aktiv = false;
    this->hp = 0;
    this->maxHp = 0;
}


double Karakter::elet(){
    return hp;
    
}
