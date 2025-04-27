#include "kartya.h"


Kartya::Kartya() : nev(""), manaKoltseg(0), ikon(' ') {}

Kartya::Kartya(const char *nev, int mana, char ikon) : nev(nev), manaKoltseg(mana), ikon(ikon) {}

Kartya::Kartya(Kartya &k) : nev(k.nev), manaKoltseg(k.manaKoltseg), ikon(k.ikon) {}

bool Kartya::kijatszas(int* mana,Kartya* kiv)
{
    if (this->manaKoltseg <= *mana)
    {
        *mana-=manaKoltseg;
        return true;
    }
    
    return false;
}

Kartya &Kartya::operator=(const Kartya &kartya)
{
    if (this != &kartya)
    {
        this->ikon = kartya.ikon;
        this->manaKoltseg = kartya.manaKoltseg;
        this->nev = kartya.nev;
    }
    return *this;
}

void Kartya::manaKiir(std::ostream& os)const{
    os<<manaKoltseg;
}
void Kartya::nevKiir(std::ostream& os) const{
    os<<nev;
}
void Kartya::ikonKiir(std::ostream& os) const{
    os<<ikon;
}