#include "minion.h"

Minion::Minion() : Karakter(), ero(0), vedelem(0) {}

Minion::Minion(Karakter &k, int ero) : Karakter(k), ero(ero), vedelem(0) {}

Minion::Minion(Minion &m) : Karakter(m), ero(m.ero), vedelem(m.vedelem) {}

Minion::Minion(const char *nev, int mana, char ikon, int hp, int maxhp, bool aktiv, int ero, int vedelem) : Karakter(nev, mana, ikon, hp, maxhp, aktiv), ero(ero), vedelem(vedelem)
{
}

Minion &Minion::operator=(const Minion &minion)
{
    if (this != &minion)
    {
        Karakter::operator=(minion);
        this->ero = minion.ero;
        this->vedelem = minion.vedelem;
    }
    return *this;
}

void Minion::sebzodik(int sebzes, Kartya *tamado)
{
    if (this->vedelem >= sebzes)
    {
        this->vedelem -= sebzes;
    }
    else if (this->vedelem > 0)
    {
        int s = sebzes;
        s -= this->vedelem;
        this->vedelem = 0;
        hp -= s;
    }
    else
    {
        hp -= sebzes;
    }

    if (hp <= 0)
    {
        halal();
    }
    else if (tamado != nullptr && tamado->isMinion())
    {
        tamado->sebzodik(this->ero, nullptr);
    }
}

void Minion::vedelemValt(int d)
{
    vedelem += d;

    if (d < 0 && this->vedelem < 0)
    {
        this->vedelem = 0;
    }
}

bool Minion::kijatszas(int *mana, Kartya *kiv)
{
    if (this->manaKoltseg <= *mana)
    {
        return true;
    }

    return false;
}

void Minion::tamadas(Kartya *celpont)
{
    if (aktiv)
    {
        celpont->sebzodik(ero, this);
        aktiv = false;
    }
}

void Minion::mentes(std::ostream &os)
{
    os << "MINION \"" << nev << "\" " << manaKoltseg << " " << ikon << " " << hp << " " << maxHp << " " << aktiv << " " << ero << " " << vedelem << std::endl;
}
void Minion::betoltes(std::istream &is)
{
    Karakter::betoltes(is);
    is >> ero >> vedelem;

    if (!is)
    {
        throw std::runtime_error("Helytelen bemenetfile");
    }
}

void Minion::reaktiv()
{
    this->aktiv = true;
    this->vedelem = 0;
}

int Minion::minionVedelem()
{
    return this->vedelem;
}

int Minion::minionhp()
{
    return this->hp;
}

bool Minion::isMinion()
{
    return true;
}

void Minion::tartalomkiir(int xBehuz, int Ykezd, bool inKez)
{
    int y = Ykezd;
    if (inKez)
    {
        econio_gotoxy(xBehuz, y++);
        std::cout << "Man: " << manaKoltseg;
    }
    econio_gotoxy(xBehuz, y++);
    std::cout << "HP: " << hp;
    econio_gotoxy(xBehuz, y++);
    std::cout << "ERO: " << ero;
    econio_gotoxy(xBehuz, y++);
    std::cout << "VED: " << vedelem;
}

Kartya *Minion::clone()
{
    return new Minion(*this);
}