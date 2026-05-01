#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int caseId = rnd.next(0, 4);
    int T;
    if (caseId == 0) {
        // Small impossible times (1-9)
        T = rnd.next(1, 9);
    } else if (caseId == 1) {
        // C-only times (10,20,...,90)
        T = rnd.next(1, 9) * 10;
    } else if (caseId == 2) {
        // B-only times (60,120,...,600)
        T = rnd.next(1, 10) * 60;
    } else if (caseId == 3) {
        // A-only times (300,600,...,up to 10000)
        int maxK = 10000 / 300;
        T = rnd.next(1, maxK) * 300;
    } else {
        // Random, half divisible by 10, half any
        if (rnd.next(0, 1) == 0) {
            T = rnd.next(1, 1000) * 10;
        } else {
            T = rnd.next(1, 10000);
        }
    }
    println(T);
    return 0;
}
