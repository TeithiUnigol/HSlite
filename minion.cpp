#include "minion.h"

Minion::Minion() : Karakter(), ero(0), vedelem(0){}

Minion::Minion(Karakter k,double ero):Karakter(k),ero(ero){}

Minion::Minion(Minion& m):Karakter(m),ero(m.ero),vedelem(m.vedelem){}

Minion& Minion::operator=(const Minion &minion){
    if (this != &minion)
    {
        Karakter::operator=(minion);
        this->ero = minion.ero;
        this->vedelem = minion.vedelem;
    }
    return *this;
}


void Minion::sebzodik(double sebzes, Karakter *tamado)
{
    if (vedelem>=sebzes)
    {
        vedelem-=sebzes;
    }else if(vedelem>0){
        int s = sebzes;
        s-=vedelem;
        hp-=s;
    }else{
        hp -= sebzes;
    }
    
    if (hp <= 0)
    {
        halal();
    }
    else if (tamado != nullptr)
    {
        tamado->sebzodik(this->ero, nullptr);
    }
}

void Minion::vedelemValt(double d)
{
    vedelem += d;

    if (d < 0 && this->vedelem < 0)
    {
        this->vedelem = 0;
    }
}

bool Minion::kijatszas(int* mana,Kartya* kiv){
    if (this->manaKoltseg <= *mana&&kiv==nullptr)
    {
        *kiv = *this;
        *mana-=manaKoltseg;
        return true;
    }
    
    return false;
}

void Minion::tamadas(Karakter* celpont){
    celpont->sebzodik(ero,this);
}

void Minion::reaktiv()
{
    this->aktiv = true;
    this->vedelem = 0;
}