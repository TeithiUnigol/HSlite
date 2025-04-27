#include "minion.h"

Minion::Minion() : Karakter(), ero(0), vedelem(0){}

Minion::Minion(Karakter k,double ero):Karakter(k),ero(ero),vedelem(0){}

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
    if (this->vedelem>=sebzes)
    {
        this->vedelem-=sebzes;
    }else if(this->vedelem>0){
        double s = sebzes;
        s-=this->vedelem;
        this->vedelem = 0;
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
    if (this->aktiv)
    {   
        Minion* celpontMinion = dynamic_cast<Minion*>(celpont);
        if (celpontMinion ==nullptr)
        {
            celpont->sebzodik(ero,this);
        }else{
            celpontMinion->sebzodik(ero,this);
        }
        
        this->aktiv = false;
    }
}

void Minion::reaktiv()
{
    this->aktiv = true;
    this->vedelem = 0;
}

double Minion::minionVedelem(){
    return this->vedelem;
}