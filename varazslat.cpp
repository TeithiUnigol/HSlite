#include "varazslat.h"

Varazslat::Varazslat():Kartya(),sebzes(0),gyogyitas(0),vedelem(0){}
Varazslat::Varazslat(Varazslat& v):Kartya(v),sebzes(v.sebzes),gyogyitas(v.gyogyitas),vedelem(v.vedelem){}
Varazslat::Varazslat(const char *nev, int mana, char ikon,double sebzes,double gyogyitas,double vedelem):
Kartya(nev,mana,ikon),sebzes(sebzes),gyogyitas(gyogyitas),vedelem(vedelem){}
bool Varazslat::kijatszas(int* mana,Karakter& kiv){
    if (this->manaKoltseg <= *mana)
    {
        *mana-=manaKoltseg;
        kiv.sebzodik(this->sebzes,nullptr);
        kiv.regen(this->gyogyitas);
        kiv.vedelemValt(this->vedelem);

        return true;
    }
    
    return false;
}