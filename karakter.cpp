#include "karakter.h"

Karakter::Karakter() : Kartya(), hp(0), maxHp(0), aktiv(false) {}

Karakter::Karakter(const Karakter &v):Kartya(v),hp(v.hp),maxHp(v.maxHp),aktiv(v.aktiv) {}

Karakter::Karakter(const char *nev, int mana, char ikon, int hp, int maxhp, bool aktiv)
    : Kartya(nev, mana, ikon), hp(maxhp), maxHp(maxhp), aktiv(true) {}


void Karakter::sebzodik(int sebzes, Kartya *tamado)
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
    ures();
    this->aktiv = false;
    this->hp = 0;
    this->maxHp = 0;
}


int Karakter::getElet()const{
    return hp;
}

void Karakter::mentes(std::ostream& os){
    os << "KARAKTER \"" << nev << "\" " << manaKoltseg << " " << ikon << " " << hp <<" " << maxHp << " " << aktiv <<std::endl;
}

void Karakter::betoltes(std::istream& is){
    Kartya::betoltes(is);
    is >> hp >> maxHp >> aktiv;

    if (!is) {
        throw std::runtime_error("Helytelen bemenetfile");
    }
}

void Karakter::tartalomkiir(int xBehuz,int Ykezd,bool inKez){
    int y = Ykezd;
    if(inKez){econio_gotoxy(xBehuz,y++);std::cout << "Man: " << manaKoltseg;}
    econio_gotoxy(xBehuz,y++);
    std::cout<<"HP: "<<hp;
}

Kartya* Karakter::clone() {
    return new Karakter(*this);
}