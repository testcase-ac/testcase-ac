#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int t = rnd.next(5, 12);
    vector<int> ns(t);
    // Reserve maximum possible for other cases if we include a large case
    int maxSmallPer = 2000;
    int reservedMax = (t - 1) * maxSmallPer;
    int largeMin = 60000;
    int largeMax = 100000 - reservedMax;
    bool includeLarge = (largeMax >= largeMin) && rnd.next(0, 1);
    int largePos = includeLarge ? rnd.next(0, t - 1) : -1;
    int largeN = includeLarge ? rnd.next(largeMin, largeMax) : 0;

    for (int i = 0; i < t; i++) {
        if (includeLarge && i == largePos) {
            ns[i] = largeN;
        } else {
            // Small or medium case
            double r = rnd.next();
            if (r < 0.1) {
                ns[i] = 1;
            } else if (r < 0.2) {
                ns[i] = 2;
            } else if (r < 0.3) {
                ns[i] = 3;
            } else if (r < 0.4) {
                ns[i] = 4;
            } else if (r < 0.5) {
                ns[i] = 5;
            } else if (r < 0.8) {
                ns[i] = rnd.next(6, 20);
            } else {
                ns[i] = rnd.next(21, maxSmallPer);
            }
        }
    }

    // Output
    println(t);
    for (int x : ns) {
        println(x);
    }
    return 0;
}
