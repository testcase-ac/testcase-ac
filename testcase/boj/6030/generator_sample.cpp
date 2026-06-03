#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> divisorRich = {12, 24, 36, 48, 60, 72, 120, 180, 240, 360, 720, 840, 1260, 1680, 2520, 5040};
    vector<int> powers = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
    vector<int> primeLike = {2, 3, 5, 7, 11, 97, 101, 997, 1009, 2999, 4001, 5003};

    int p = 1;
    int q = 1;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        p = rnd.next(1, 6000);
        q = rnd.next(1, 6000);
    } else if (mode == 1) {
        p = rnd.next(0, 1) ? 1 : 6000;
        q = rnd.next(1, 6000);
    } else if (mode == 2) {
        p = rnd.any(divisorRich);
        q = rnd.any(divisorRich);
    } else if (mode == 3) {
        p = rnd.any(powers);
        q = rnd.any(powers);
    } else if (mode == 4) {
        p = rnd.any(primeLike);
        q = rnd.any(primeLike);
    } else {
        p = rnd.any(divisorRich);
        q = rnd.next(1, 25);
        if (rnd.next(0, 1)) {
            int tmp = p;
            p = q;
            q = tmp;
        }
    }

    println(p, q);
    return 0;
}
