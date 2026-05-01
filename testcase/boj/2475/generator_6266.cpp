#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<int> a(5);
    // Choose a pattern to expose edge cases and randomness
    int pattern = rnd.next(0, 5);
    switch (pattern) {
        case 0:
            // all zeros
            for (int i = 0; i < 5; i++) a[i] = 0;
            break;
        case 1:
            // all nines
            for (int i = 0; i < 5; i++) a[i] = 9;
            break;
        case 2:
            // ascending from 0
            for (int i = 0; i < 5; i++) a[i] = i;
            break;
        case 3:
            // descending from 9
            for (int i = 0; i < 5; i++) a[i] = 9 - i;
            break;
        case 4:
            // alternating high/low
            for (int i = 0; i < 5; i++) a[i] = (i % 2 == 0 ? 9 : 0);
            break;
        case 5:
        default:
            // fully random
            for (int i = 0; i < 5; i++) a[i] = rnd.next(0, 9);
            break;
    }
    println(a);
    return 0;
}
