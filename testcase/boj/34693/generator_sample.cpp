#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t;
    if (mode == 0) {
        t = rnd.next(1, 8);
    } else if (mode == 1) {
        t = rnd.next(8, 30);
    } else if (mode == 2) {
        t = rnd.next(1, 20);
    } else if (mode == 3) {
        t = rnd.next(20, 80);
    } else if (mode == 4) {
        t = rnd.next(80, 200);
    } else {
        t = rnd.next(900, 1000);
    }

    vector<int> ks;
    ks.reserve(t);

    vector<int> edge = {
        1, 2, 3, 4, 5, 14, 99, 100,
        999999999, 1000000000
    };

    for (int i = 0; i < t; ++i) {
        int selector = rnd.next(0, 99);
        int k;
        if (selector < 25) {
            k = rnd.any(edge);
        } else if (selector < 45) {
            k = rnd.next(1, 30);
        } else if (selector < 60) {
            int base = rnd.next(1, 500);
            k = 2 * base - rnd.next(0, 1);
        } else if (selector < 75) {
            k = rnd.next(999999900, 1000000000);
        } else {
            k = rnd.next(1, 1000000000);
        }
        ks.push_back(k);
    }

    println(t);
    for (int k : ks) {
        println(k);
    }

    return 0;
}
