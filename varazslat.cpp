#include "varazslat.h"

Varazslat::Varazslat():Kartya(),sebzes(0),gyogyitas(0),vedelem(0){}
Varazslat::Varazslat(Varazslat& v):Kartya(v),sebzes(v.sebzes),gyogyitas(v.gyogyitas),vedelem(v.vedelem){}
Varazslat::Varazslat(const char *nev, int mana, char ikon,int sebzes,int gyogyitas,int vedelem):
Kartya(nev,mana,ikon),sebzes(sebzes),gyogyitas(gyogyitas),vedelem(vedelem){}
bool Varazslat::kijatszas(int* mana,Kartya* kiv){
    if (this->manaKoltseg <= *mana)
    {
        *mana-=manaKoltseg;
        kiv->vedelemValt(this->vedelem);
        kiv->sebzodik(this->sebzes,nullptr);
        kiv->regen(this->gyogyitas);

        return true;
    }
    
    return false;
}

Kartya* Varazslat::clone() {
    return new Varazslat(*this);
}

void Varazslat::mentes(std::ostream& os){
    os << "VARAZSLAT " << nev << " " << manaKoltseg << " " << ikon <<" " << sebzes <<" " << gyogyitas <<" " << vedelem << std::endl;
}