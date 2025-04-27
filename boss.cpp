#include "boss.h"

Boss::Boss():Karakter(),specialSebzes(0){}

Boss::Boss(Karakter &karakter,double special):Karakter(karakter),specialSebzes(special){}

void Boss::special(Karakter &k){
    k.sebzodik(specialSebzes,nullptr);
}