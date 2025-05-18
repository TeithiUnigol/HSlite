#include "kurzor.h"

Kurzor::Kurzor() : p1(), p2(), mov_a(), sel1_a() {}

Kurzor::Kurzor(Jatekos *p1, Jatekos *p2)
    : p1(p1), p2(p2), mov_a(), sel1_a()
{
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
                if (mov_a.szint == 2 && mov_a.szint == 5)
                {
                    gorgeto(mov_a.szint, true, 6);
                }
                gorgeto(mov_a.szint, true, 6);

                SzintDekoder();
                break;
            case le:
                if (mov_a.szint == 0 && mov_a.szint == 3)
                {
                    gorgeto(mov_a.szint, false, 6);
                }
                gorgeto(mov_a.szint, false, 3);
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
        mov_a.pointer = &p1->Getboss();
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
        mov_a.pointer = &p2->Getboss();
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
            gorgeto(mov_a.index, true, maxIndex);
            SzintDekoder();
            break;

        case balra:
            gorgeto(mov_a.index, false, maxIndex);
            SzintDekoder();
            break;
        case fel:
            mov_a.szint -= 2 * jatekos;
            gorgeto(mov_a.szint, true, 1);
            mov_a.szint += 2 * jatekos;
            SzintDekoder();
            break;
        case le:
            mov_a.szint -= 2 * jatekos;
            gorgeto(mov_a.szint, false, 1);
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
            gorgeto(mov_a.index, true, maxIndex);
            SzintDekoder();
            break;

        case balra:
            gorgeto(mov_a.index, false, maxIndex);
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
            gorgeto(mov_a.szint, true, 1);
            mov_a.szint += 2 * jatekos;

            SzintDekoder();
            break;
        case le:
            mov_a.szint -= 2 * jatekos;
            gorgeto(mov_a.szint, false, 1);
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
    if (sel1_a.pointer == nullptr)
    {
        // kiválasztottuk a Kártyát, amit szeretnénk végrehajtani
        if (mov_a.pointer == nullptr) // mivel üres karakterrel nem lehet akciót végrehajtani
        {
            return false;
        }
        sel1_a.pointer = mov_a.pointer;
        sel1_a.szint = mov_a.szint;
        sel1_a.index = mov_a.index;

        mov_a.index = 0;
        mov_a.pointer = nullptr;
        if (sel1_a.pointer->isMinion())
        {
            mov_a.szint = jatekos + 2;
        }else{
            mov_a.szint = jatekos *5;
        }
    }
    /*else
    {
        // A mov most a célpontot határozza meg

                if (!aktJ->Kijatszas(sel1_a.pointer, mov_a.pointer)) {
                    if (fazis == 1)
                    {
                        mov_a.pointer = aktJ->getTarolo(TaroloTipus::Kez)[0];
                        mov_a.index = 0;
                    }else{

                    }

                    return false; //Nem lehet kijátszani. Pl kevés a mana
                } else {
                    if (fazis == 1) {
                        // Ha kézből játszottuk ki, távolítsuk el onnan
                        aktiv->getTarolo(TaroloTipus::Kez).kihuz(kurz.getSel1().index);
                    } else {
                        // Harci fázis, vizsgáljuk a célpontot
                        switch (kurz.getMov().szint) {
                            case 0: // Boss támadás
                                if (ellenfel->Getboss().getElet() == 0) {
                                    isJatek = false;
                                }
                                break;
                            case 1: // Ellenfél minion támadása
                            {
                                Kartya* cel = ellenfel->getTarolo(TaroloTipus::Minionok)[kurz.getMov().index];
                                if (cel && cel->getElet() == 0) {
                                    ellenfel->getTarolo(TaroloTipus::Minionok).kihuz(kurz.getMov().index);
                                }
                                break;
                            }
                            case 2: // Ellenfél kézben lévő minion? ez valószínűleg logikai hiba
                                break;
                            case 3: // valami más?
                                break;
                        }
                    }

                    // Végén: reseteljük a kurzort
                    kurz.getSel1().pointer = nullptr;
                    kurz.getMov().pointer = nullptr;
                }
    }*/
    return false;
}

mozgo &Kurzor::getMov()
{
    return mov_a;
}

mozgo &Kurzor::getSel1()
{
    return sel1_a;
}