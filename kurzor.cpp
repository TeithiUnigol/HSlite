#include "kurzor.h"
#include "boss.h"
#include "kartyaTarolo.h"

Kurzor::Kurzor() : p1(), p2(), sel1_a(), mov_a() {}

Kurzor::Kurzor(Jatekos* p1,Jatekos* p2)
    : p1(p1), p2(p2), sel1_a(), mov_a()
{
}

void Kurzor::lepes(irany ir,int fazis,int jatekos)
{
    switch (fazis)
    {
    case 1:
        fazis1Lepes(ir,jatekos);
        break;
    case 2:
        fazis2Lepes(ir,jatekos);
        break;
    default:
        break;
    }
}

void Kurzor::fazis1Lepes(irany ir,int jatekos)
{
    if (sel1_a.pointer == nullptr)
    {
        // kártya kiválasztása a kézből
        KartyaTarolo &kez = aktJatekos(jatekos)->getTarolo(TaroloTipus::Kez);
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
            MinionLerakas(ir, mov_a.index,jatekos);
        }
        else // mágia
        {
            // mivel mindkettő mérete megegyezik
            size_t maxIndex = p1->getTarolo(TaroloTipus::Minionok).getKapacitas();
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
                gorgeto(mov_a.szint, true, 3);
                SzintDekoder();
                break;
            case le:
                gorgeto(mov_a.szint, false, 3);
                SzintDekoder();
                break;
            default:
                break;
            }
        }
    }
}

void Kurzor::MinionLerakas(irany ir, size_t &index,int jatekos)
{
    KartyaTarolo &minionTomb = aktJatekos(jatekos)->getTarolo(TaroloTipus::Minionok);
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
        mov_a.pointer = &p1->Getboss();
        break;
    case 1:
        mov_a.pointer = p1->getTarolo(TaroloTipus::Minionok)[mov_a.index];
        break;
    case 2:
        mov_a.pointer = p2->getTarolo(TaroloTipus::Minionok)[mov_a.index];
        break;
    case 3:
        mov_a.pointer = &p2->Getboss();
        break;

    default:
        break;
    }
}

// minionok és boss támadnak
void Kurzor::fazis2Lepes(irany ir,int jatekos)
{
    size_t maxIndex = p1->getTarolo(TaroloTipus::Minionok).getKapacitas();
    if (sel1_a.pointer == nullptr)
    {
        switch (ir)
        {
        case jobbra:
            gorgeto(mov_a.index,true,maxIndex);
            SzintDekoder();
            break;

        case balra:
            gorgeto(mov_a.index,false,maxIndex);
            SzintDekoder();
            break;
        case fel:
            mov_a.szint -=2*jatekos;
            gorgeto(mov_a.szint,true,1);
            mov_a.szint += 2 * jatekos;
            SzintDekoder();
            break;
        case le:
            mov_a.szint -=2*jatekos;
            gorgeto(mov_a.szint,false,1);
            mov_a.szint += 2 * jatekos;
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
            gorgeto(mov_a.index,true,maxIndex);
            SzintDekoder();
            break;

        case balra:
            gorgeto(mov_a.index,false,maxIndex);
            SzintDekoder();
            break;
        case fel:
            if (jatekos == 0)
            {
                if (mov_a.szint > 2)
                {
                    mov_a.szint = 2;
                }
                else
                {
                    mov_a.szint = 3;
                }
            }
            else
            {
                if (mov_a.szint > 0)
                {
                    mov_a.szint = 0;
                }
                else
                {
                    mov_a.szint = 1;
                }
            }

            mov_a.szint -= 2 * jatekos;
            gorgeto(mov_a.szint,true,1);
            mov_a.szint += 2 * jatekos;

            SzintDekoder();
            break;
        case le:
            mov_a.szint -= 2 * jatekos;
            gorgeto(mov_a.szint,false,1);
            mov_a.szint += 2 * jatekos;
            SzintDekoder();
            break;
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
        gorgetendo = gorgetendo % (maxT + 1);
    }
    else
    {
        if (gorgetendo == 0)
        {
            gorgetendo = maxT;
        }
        else
        {
            --gorgetendo;
        }
    }
}

//EZ is GM-be
/*
void Kurzor::kivalaszt()
{
    if (sel1_a.pointer == nullptr)
    {
        sel1_a.pointer = mov_a.pointer;
    }
    else
    {
        if (aktJatekos(true).Kijatszas(sel1_a.pointer, mov_a.pointer))
        {
            throw "";
        }
        
        sel1_a.pointer = nullptr;
        mov_a.pointer = nullptr;
    }
}



void Kurzor::kovFazis(int fazis)
{
    sel1_a.pointer = nullptr;
    fazis += 1;
    if (fazis == 3)
    {
        jatekos = (jatekos + 1) % 2;
        if (jatekos == 0)
        {
            mov_a.szint = 0;
            p1.ujKor();
        }
        else
        {
            mov_a.szint = 3;
            p2.ujKor();
        }
    }
}

*/
//Ez is GM-be
Jatekos* Kurzor::aktJatekos(int akt)
{
    if (akt == 0)
    {
        return p1;
    }
    else
    {
        return p2;
    }
}