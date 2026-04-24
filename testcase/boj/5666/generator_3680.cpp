#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 10);
    for (int i = 0; i < T; i++) {
        int H, P;
        int type = rnd.next(0, 5);
        if (type == 0) {
            // fully random
            H = rnd.next(1, 1000);
            P = rnd.next(1, 1000);
        } else if (type == 1) {
            // large H, small P
            H = rnd.wnext(1000, 2) + 1;
            P = rnd.wnext(1000, -2) + 1;
        } else if (type == 2) {
            // small H, large P
            H = rnd.wnext(1000, -2) + 1;
            P = rnd.wnext(1000, 2) + 1;
        } else if (type == 3) {
            // H == P
            P = rnd.next(1, 1000);
            H = P;
        } else if (type == 4) {
            // single participant
            P = 1;
            H = rnd.next(1, 1000);
        } else {
            // integer average
            P = rnd.next(1, 1000);
            int maxk = 1000 / P;
            if (maxk < 1) maxk = 1;
            int k = rnd.next(1, maxk);
            H = P * k;
        }
        println(H, P);
    }

    return 0;
}
