#include "kartyaTarolo.h"
#include <random>

// #include <time.h>

KartyaTarolo::KartyaTarolo(size_t kapacitas) : kapacitas(kapacitas), meret(0)
{
    tomb = new Kartya *[kapacitas];
    for (size_t i = 0; i < kapacitas; ++i)
    {
        tomb[i] = nullptr;
    }
    // a teszthez nem kell
    // srand(time(0));
}

KartyaTarolo::KartyaTarolo(const KartyaTarolo&){
    
}

void KartyaTarolo::randomBeszur(Kartya *kartya)
{
    if (meret >= kapacitas)
    {
        throw std::overflow_error("megtelt");
    }

    size_t index = rand() % (kapacitas);
    while (tomb[index] == nullptr)
    {
        ++index;
        if (index == kapacitas)
        {
            index = 0;
        }
    }
    tomb[index] = kartya;

    ++meret;
}

void KartyaTarolo::berak(Kartya *kartya,size_t index)
{
    if (meret >= kapacitas)
    {
        throw std::overflow_error("megtelt");
    }
    tomb[index] = kartya;
    ++meret;
}

Kartya *KartyaTarolo::kihuz(size_t index)
{
    Kartya *kartya = tomb[index];
    tomb[index] = nullptr;
    --meret;    
    return kartya;
}

size_t KartyaTarolo::getMeret()const
{
    return meret;
}

size_t KartyaTarolo::getKapacitas()const{
    return kapacitas;
}
Kartya *KartyaTarolo::operator[](size_t index)
{
    if (index >= meret)
    {
        throw std::out_of_range("tulindex");
    }
    return tomb[index];
}

void KartyaTarolo::kiurites()
{
    for (size_t i = 0; i < meret; ++i)
    {
        delete tomb[i];
        tomb[i] = nullptr;
    }
    meret = 0;
}

KartyaTarolo::~KartyaTarolo()
{
    kiurites();
    delete[] tomb;
}