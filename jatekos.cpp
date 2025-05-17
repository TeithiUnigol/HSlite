#include "jatekos.h"
#include "minion.h"

Jatekos::Jatekos() : maxMana(0), mana(0), boss(), kez(0), huzo(0), minionok(0), csomag(0) {}

Jatekos::Jatekos(const Boss &boss, const KartyaTarolo &huzoPakli, const KartyaTarolo &kezPakli, const KartyaTarolo &MinionPakli, const KartyaTarolo &csomag, int maxMana, int mana) : maxMana(maxMana), mana(mana), boss(boss), kez(kezPakli), huzo(huzoPakli), minionok(MinionPakli), csomag(csomag) {}
Jatekos::Jatekos(const Boss &boss, size_t MinionPakliMeret, size_t kezMeret, const KartyaTarolo &csom, int maxMana) : maxMana(maxMana), mana(maxMana), boss(boss), kez(kezMeret), huzo(csom), minionok(MinionPakliMeret), csomag(csom)
{
    huzopakliKever();
}
Jatekos::Jatekos(const Jatekos &j) : maxMana(j.maxMana), mana(j.mana), boss(j.boss), kez(j.kez.getKapacitas()), huzo(j.huzo.getKapacitas()), minionok(j.minionok.getKapacitas()), csomag(j.csomag.getKapacitas())
{
    kez = j.kez;
    huzo = j.huzo;
    minionok = j.minionok;
    csomag = j.csomag;
}

Jatekos &Jatekos::operator=(const Jatekos &forras)
{
    if (this == &forras)
        return *this;

    maxMana = forras.maxMana;
    mana = forras.mana;
    boss = forras.boss;

    kez = forras.kez;
    huzo = forras.huzo;
    minionok = forras.minionok;
    csomag = forras.csomag;

    return *this;
}

void Jatekos::kezfeltolt()
{
    int index = 0;

    while (kez.getMeret() != kez.getKapacitas() && huzo.getMeret() > 0)
    {
        kez.berak(huzo.kihuz(huzo.getMeret() - 1), index);
        ++index;
    }
}

void Jatekos::ujKor()
{
    boss.reaktiv();
    for (size_t i = 0; i < minionok.getKapacitas(); i++)
    {
        Minion *M = dynamic_cast<Minion *>(minionok[i]);
        if (M != nullptr)
        {
            M->reaktiv();
        }
    }
    kezfeltolt();
    ++maxMana;
    mana = maxMana;
}

void Jatekos::huzopakliKever()
{
    huzo.kiurites();
    for (size_t i = 0; i < csomag.getMeret(); i++)
    {
        huzo.randomBeszur(csomag[i]);
    }
}

bool Jatekos::Kijatszas(Kartya *k1, Kartya *k2)
{
    bool ret = k1->kijatszas(&mana, k2);
    return ret;
}

Boss &Jatekos::Getboss()
{
    return this->boss;
}

KartyaTarolo &Jatekos::getTarolo(TaroloTipus tipus)
{
    switch (tipus)
    {
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

int Jatekos::getMana() const
{
    return mana;
}

// const Boss& boss,size_t MinionPakliMeret,size_t kezMeret,const KartyaTarolo& csom,int maxMana
void Jatekos::mentes(std::ostream &os)
{
    os << csomag.getMeret() << " " << minionok.getKapacitas() << " " << kez.getKapacitas() << " " << mana << std::endl;
    boss.mentes(os);
    for (size_t i = 0; i < csomag.getMeret(); i++)
    {
        csomag[i]->mentes(os);
    }
}