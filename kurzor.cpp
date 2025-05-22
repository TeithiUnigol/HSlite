#include "kurzor.h"

Kurzor::Kurzor() : p1(), p2(), mov_a(), sel1_a() {}

Kurzor::Kurzor(Jatekos *p1, Jatekos *p2)
    : p1(p1), p2(p2), mov_a(), sel1_a()
{
}

Kurzor &Kurzor::operator=(const Kurzor &kurz)
{
    this->p1 = kurz.p1;
    this->p2 = kurz.p2;
    this->mov_a = kurz.mov_a;
    this->sel1_a = kurz.sel1_a;
    return *this;
}

void Kurzor::lepes(irany ir, int fazis, int jatekos, Jatekos *aktJ)
{
    switch (fazis)
    {
    case 1:
        fazis1Lepes(ir, jatekos, aktJ);
        break;
    case 2:
        fazis2Lepes(ir, jatekos);
        break;
    default:
        break;
    }
}

void Kurzor::fazis1Lepes(irany ir, int jatekos, Jatekos *aktJ)
{
    if (sel1_a.pointer == nullptr)
    {

        // kártya kiválasztása a kézből
        KartyaTarolo &kez = aktJ->getTarolo(TaroloTipus::Kez);
        switch (ir)
        {
        case jobbra:
            gorgeto(mov_a.index, true, kez.getKapacitas());
            mov_a.pointer = kez[mov_a.index];

            break;

        case balra:
            gorgeto(mov_a.index, false, kez.getKapacitas());
            mov_a.pointer = kez[mov_a.index];
            break;
        default:
            break;
        }
    }
    else
    {
        // Kártya elhelyezése
        /// Ha minion kártyáról beszélünk, azt kizárólag a saját minion kártyái közötti üres helyekre rakhatja
        ///  Egy minion esetén nincs értelme a fel és le mozgásnak
        if (sel1_a.pointer->isMinion())
        {
            MinionLerakas(ir, mov_a.index, jatekos, aktJ);
        }
        else // mágia
        {
            // mivel mindkettő mérete megegyezik
            size_t maxIndex = aktJ->getTarolo(TaroloTipus::Minionok).getKapacitas();
            switch (ir)
            {
            case jobbra:
                gorgeto(mov_a.index, true, maxIndex);
                SzintDekoder();
                break;

            case balra:
                gorgeto(mov_a.index, false, maxIndex);
                SzintDekoder();
                break;
            case fel:
                if (mov_a.szint == 2 || mov_a.szint == 5)
                {
                    gorgeto(mov_a.szint, false, 6);
                }
                gorgeto(mov_a.szint, false, 6);

                SzintDekoder();
                break;
            case le:
                // itt van a lépéses hiba szintdekoder a ludas
                if (mov_a.szint == 0 || mov_a.szint == 3)
                {
                    gorgeto(mov_a.szint, true, 6);
                }
                gorgeto(mov_a.szint, true, 6);
                SzintDekoder();
                break;
            default:
                break;
            }
        }
    }
}

void Kurzor::MinionLerakas(irany ir, size_t &index, int jatekos, Jatekos *aktJ)
{
    KartyaTarolo &minionTomb = aktJ->getTarolo(TaroloTipus::Minionok);
    switch (ir)
    {
    case jobbra:
        gorgeto(mov_a.index, true, minionTomb.getKapacitas());
        mov_a.pointer = minionTomb[index];
        break;

    case balra:
        gorgeto(mov_a.index, false, minionTomb.getKapacitas());
        mov_a.pointer = minionTomb[index];
        break;
    default:
        break;
    }
}

void Kurzor::SzintDekoder()
{
    switch (mov_a.szint)
    {
    case 0:
        mov_a.pointer = p1->Getboss();
        break;
    case 1:
        mov_a.pointer = p1->getTarolo(TaroloTipus::Kez)[mov_a.index];
        break;

    case 2:
        mov_a.pointer = p1->getTarolo(TaroloTipus::Minionok)[mov_a.index];
        break;
    case 3:
        mov_a.pointer = p2->getTarolo(TaroloTipus::Minionok)[mov_a.index];
        break;

    case 4:
        mov_a.pointer = p2->getTarolo(TaroloTipus::Kez)[mov_a.index];
        break;

    case 5:
        mov_a.pointer = p2->Getboss();
        break;

    default:
        break;
    }
}

// minionok és boss támadnak
void Kurzor::fazis2Lepes(irany ir, int jatekos)
{
    size_t maxIndex = p1->getTarolo(TaroloTipus::Minionok).getKapacitas();
    if (sel1_a.pointer == nullptr)
    {
        switch (ir)
        {
        case jobbra:
            gorgeto(mov_a.index, true, maxIndex - 1);
            SzintDekoder();
            break;

        case balra:
            gorgeto(mov_a.index, false, maxIndex - 1);
            SzintDekoder();
            break;
        case fel:
        case le:
            switch (mov_a.szint)
            {
            case 0:
                mov_a.szint = 2;
                mov_a.index =0;
                mov_a.pointer = p1->getTarolo(TaroloTipus::Minionok)[mov_a.index];
                break;
            case 2:
            mov_a.szint = 0;
                mov_a.index =0;
                mov_a.pointer = p1->Getboss();
                break;
                case 3:
                mov_a.szint = 5;
                mov_a.index =0;
                mov_a.pointer = p2->Getboss();
                break;
            case 5:
            mov_a.szint = 3;
                mov_a.index =0;
                mov_a.pointer = p2->getTarolo(TaroloTipus::Minionok)[mov_a.index];
                break;
            default:
                break;
            }
            
            SzintDekoder();
            break;
        default:
            break;
        }
    }
    else
    { // kit tamadnak
        switch (ir)
        {
        case jobbra:
            gorgeto(mov_a.index, true, maxIndex);
            SzintDekoder();
            break;

        case balra:
            gorgeto(mov_a.index, false, maxIndex);
            SzintDekoder();
            break;
        case fel:
        case le:
            switch (mov_a.szint)
            {
            case 0:
                mov_a.szint = 2;
                mov_a.index =0;
                mov_a.pointer = p1->getTarolo(TaroloTipus::Minionok)[mov_a.index];
                break;
            case 2:
            mov_a.szint = 0;
                mov_a.index =0;
                mov_a.pointer = p1->Getboss();
                break;
                case 3:
                mov_a.szint = 5;
                mov_a.index =0;
                mov_a.pointer = p2->getTarolo(TaroloTipus::Minionok)[mov_a.index];
                break;
            case 5:
            mov_a.szint = 3;
                mov_a.index =0;
                mov_a.pointer = p2->Getboss();
                break;
            default:
                break;
            }
        default:
            break;
        }
    }
}

template <typename T>
void Kurzor::gorgeto(T &gorgetendo, bool poz, T maxT)
{
    if (poz)
    {
        ++gorgetendo;
        gorgetendo = gorgetendo % (maxT);
    }
    else
    {
        if (gorgetendo == 0)
        {
            gorgetendo = maxT - 1;
        }
        else
        {
            --gorgetendo;
        }
    }
}

bool Kurzor::kivalaszt(int fazis, Jatekos *aktJ, Jatekos *ellenfelJ, int jatekos)
{
    bool siker = true;
    if (sel1_a.pointer == nullptr)
    {
        // kiválasztottuk a Kártyát, amit szeretnénk végrehajtani
        if (mov_a.pointer->getIkon() == ' ') // mivel üres karakterrel nem lehet akciót végrehajtani
        {
            siker = false;
        }
        else
        {

            sel1_a.pointer = mov_a.pointer;
            sel1_a.szint = mov_a.szint;
            sel1_a.index = mov_a.index;

            switch (fazis)
            {
            case 1:
                mov_a.szint = jatekos == 0 ? 2 : 3;
                mov_a.index = 0;
                mov_a.pointer = jatekos == 0 ? p1->getTarolo(TaroloTipus::Minionok)[mov_a.index] : p2->getTarolo(TaroloTipus::Minionok)[mov_a.index];
                break;
            default:
                mov_a.szint = jatekos == 0 ? 5 : 0;
                mov_a.index = 0;
                mov_a.pointer = jatekos == 0 ? p2->Getboss() : p1->Getboss();
            break;
            }
            return true;
        }
    }
    else
    {
        // A mov most a célpontot határozza meg
        if (fazis == 1)
        {
            if (!aktJ->Kijatszas(sel1_a.pointer, sel1_a.index, mov_a.pointer, mov_a.index))
            {
                siker = false;
            }
        }
        else
        {
            if (mov_a.pointer->getIkon() != ' ')
            {
                sel1_a.pointer->tamadas(mov_a.pointer);
            }
            else
            {
                siker = false;
            }
        }
    }

    sel1_a.pointer = nullptr;
    sel1_a.szint = -1;
    switch (fazis)
    {
    case 1:
        mov_a.szint = jatekos == 0 ? 1 : 4;
        mov_a.index = 0;
        mov_a.pointer = jatekos == 0 ? p1->getTarolo(TaroloTipus::Kez)[mov_a.index] : p2->getTarolo(TaroloTipus::Kez)[mov_a.index];
        break;
        default:
        mov_a.szint = jatekos == 0 ? 0 : 5;
        mov_a.index = 0;
        mov_a.pointer = jatekos == 0 ? p1->Getboss() : p2->Getboss();
        break;
    }

    return siker;
}

mozgo &Kurzor::getMov()
{
    return mov_a;
}

mozgo &Kurzor::getSel1()
{
    return sel1_a;
}