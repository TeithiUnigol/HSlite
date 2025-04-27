#include "boss.h"

Boss::Boss():Karakter(),specialSebzes(0){}
//TODO
Boss::Boss(Karakter &karakter,double special):Karakter(karakter),specialSebzes(special){}

Boss::Boss(Boss &boss):Karakter(boss),specialSebzes(boss.specialSebzes){}

void Boss::special(Karakter &k){
    k.sebzodik(specialSebzes,nullptr);
}