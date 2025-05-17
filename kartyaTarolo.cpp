#include "kartyaTarolo.h"
#include <random>

// #include <time.h>

KartyaTarolo::KartyaTarolo() : tomb(nullptr), kapacitas(0), meret(0) {}

KartyaTarolo::KartyaTarolo(size_t kapacitas) : kapacitas(kapacitas), meret(0)
{
    tomb = new Kartya *[kapacitas];
    for (size_t i = 0; i < kapacitas; ++i)
    {
        tomb[i] = nullptr;
    }
    //TODO kitörölni a végén
    #ifndef CPORTA
        //srand(time(0));
    #endif
}

KartyaTarolo::KartyaTarolo(const KartyaTarolo &t) : kapacitas(t.kapacitas), meret(t.meret)
{
    tomb = new Kartya *[kapacitas];

    for (size_t i = 0; i < meret; ++i)
    {
        tomb[i] = t.tomb[i]->clone();
    }
}

void KartyaTarolo::randomBeszur(Kartya *kartya)
{
    if (meret >= kapacitas)
    {
        throw std::overflow_error("megtelt");
    }

    size_t index = rand() % (kapacitas);
    while (tomb[index] != nullptr)
    {
        ++index;
        if (index == kapacitas)
        {
            index = 0;
        }
    }
    tomb[index] = kartya->clone();

    ++meret;
}

void KartyaTarolo::berak(Kartya *kartya, size_t index)
{
    if (meret >= kapacitas)
    {
        kiurites();
        throw "megtelt";
    }else{
    tomb[index] = kartya->clone();
    ++meret;    
    }
}

Kartya *KartyaTarolo::kihuz(size_t index)
{
    Kartya *kartya = tomb[index];
    tomb[index] = nullptr;
    --meret;
    return kartya;
}

size_t KartyaTarolo::getMeret() const
{
    return meret;
}

size_t KartyaTarolo::getKapacitas() const
{
    return kapacitas;
}
Kartya *KartyaTarolo::operator[](size_t index)
{
    if (index >= kapacitas)
    {
        throw std::out_of_range("tulindex");
    }
    return tomb[index];
}

void KartyaTarolo::kiurites()
{
    for (size_t i = 0; i < kapacitas; ++i)
    {
        if (tomb[i]!=nullptr)
        {
            delete tomb[i];
        }
        
        tomb[i] = nullptr;
    }
    meret = 0;
}

KartyaTarolo::~KartyaTarolo()
{
    kiurites();
    delete[] tomb;
}