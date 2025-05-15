#include "boss.h"

Boss::Boss():Karakter(),specialSebzes(0){}

Boss::Boss(Karakter &karakter,double special):Karakter(karakter),specialSebzes(special){}

Boss::Boss(const Boss &boss):Karakter(boss),specialSebzes(boss.specialSebzes){}

Boss::Boss(const char *nev, int mana, char ikon, double hp, double maxhp, bool aktiv, double special)
    : Karakter(nev,mana,ikon,hp,maxhp,aktiv),specialSebzes(special) {}

void Boss::special(Karakter &k){
    k.sebzodik(specialSebzes,nullptr);
}