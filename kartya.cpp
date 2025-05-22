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
/*
void Kartya::manaKiir(std::ostream &os) const
{
    os << manaKoltseg;
}*/

int Kartya::getMana()const{
    return manaKoltseg;
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

char Kartya::getIkon() const
{
    return ikon;
}

bool Kartya::isMinion()
{
    return false;
}

void Kartya::sebzodik(int sebzes, Kartya *tamado){}
void Kartya::tamadas(Kartya *celpont){}
void Kartya::vedelemValt(int d){}
bool Kartya::regen(int hp){return false;}

void Kartya::ures()
{
    ikon = ' ';
    nev = " ";
    manaKoltseg = 0;
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


void Kartya::mentes(std::ostream& os){
    os << "KARTYA \"" << nev << "\" " << manaKoltseg << " " << ikon << std::endl;
}

void Kartya::betoltes(std::istream& is){
    is >> std::ws;
    char quote;
    is.get(quote);
    if (quote!='"')
    {
        throw "Helytelen bemenetfile";
    }
    std::getline(is, nev, '"');

    is >> manaKoltseg >> ikon;
}

void Kartya::tartalomkiir(int xBehuz,int Ykezd,bool inKez){
    int y = Ykezd;
    if(inKez){econio_gotoxy(xBehuz,y++);std::cout<<"M: "<<manaKoltseg;}
}

Kartya::~Kartya() {}