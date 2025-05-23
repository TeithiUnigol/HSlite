#include "boss.h"

Boss::Boss():Karakter(),specialSebzes(0){}

Boss::Boss(Karakter &karakter,int special):Karakter(karakter),specialSebzes(special){}

Boss::Boss(const Boss &boss):Karakter(boss),specialSebzes(boss.specialSebzes){}

Boss::Boss(const char *nev, int mana, char ikon, int hp, int maxhp, bool aktiv, int special)
    : Karakter(nev,mana,ikon,hp,maxhp,aktiv),specialSebzes(special) {}

void Boss::tamadas(Kartya *celpont){
    if (aktiv)
    {       
        celpont->sebzodik(specialSebzes,nullptr);
        this->aktiv = false;
    }
}


void Boss::mentes(std::ostream& os){
    os << "BOSS \"" << nev << "\" " << manaKoltseg << " " << ikon << " " << hp <<" " << maxHp << " " << aktiv << " " << specialSebzes<<std::endl;
}
void Boss::betoltes(std::istream& is){
    Karakter::betoltes(is);
    is >> specialSebzes;

    if (!is) {
        throw std::runtime_error("Helytelen bemenetfile");
    }
}
void Boss::tartalomkiir(int xBehuz,int Ykezd,bool inKez){
    int y = Ykezd;
    if(inKez){econio_gotoxy(xBehuz,y++);std::cout << "Man: " << manaKoltseg;}
    econio_gotoxy(xBehuz,y++);
    std::cout<<"HP: "<<hp<<"/"<<maxHp;;
    econio_gotoxy(xBehuz,y++);
    std::cout<<"SPEC: "<<specialSebzes;

}

Kartya* Boss::clone() {
    return new Boss(*this);
}