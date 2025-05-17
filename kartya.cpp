#include "kartya.h"

Kartya::Kartya() : nev(""), manaKoltseg(0), ikon(' ') {}

Kartya::Kartya(const char *nev, int mana, char ikon) : nev(nev), manaKoltseg(mana), ikon(ikon) {}

Kartya::Kartya(const Kartya &k) : nev(k.nev), manaKoltseg(k.manaKoltseg), ikon(k.ikon) {}

bool Kartya::kijatszas(int *mana, Kartya *kiv)
{
    if (this->manaKoltseg <= *mana)
    {
        *mana -= manaKoltseg;
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

int Kartya::getElet()const{
    return 0;
}

void Kartya::manaKiir(std::ostream &os) const
{
    os << manaKoltseg;
}
void Kartya::nevKiir(std::ostream &os,size_t maxW) const
{
    if (nev.length() <= maxW)
        os << nev;
    else
        os << nev.substr(0, maxW);
}
void Kartya::ikonKiir(std::ostream &os) const
{
    os << ikon;
}

bool Kartya::isMinion()
{
    return false;
}
void Kartya::ures()
{
    ikon = ' ';
    nev = " ";
    manaKoltseg = 0;
}

void Kartya::sebzodik(int sebzes, Kartya *tamado)
{
    throw "nem tud ilyet";
}
void Kartya::vedelemValt(int d)
{
    throw "nem tud ilyet";
}
bool Kartya::regen(int hp)
{
    throw "nem tud ilyet";
}

size_t Kartya::nevMeret(){
    return nev.size();
}

Kartya *Kartya::clone()
{
    return new Kartya(*this);
}

bool Kartya::getAktiv(){
    return true;
}

void Kartya::printKartya(int screenW,int blokkW,int startX,int startY){
    int y = startY;
    econio_gotoxy(startX,y);
    changeBG(black);
    changeTxt(white);
    for (size_t i = 0; i < blokkW; ++i)
    {
        cout << "-";
    }
}

void Kartya::mentes(std::ostream& os){
    os << "KARTYA " << nev << " " << manaKoltseg << " " << ikon << std::endl;
}

Kartya::~Kartya() {}