#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> bales;

    if (mode == 0) {
        n = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) bales.push_back(rnd.next(1, 100));
    } else if (mode == 1) {
        n = rnd.next(3, 20);
        int value = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) bales.push_back(value);
    } else if (mode == 2) {
        n = rnd.next(8, 20);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                bales.push_back(rnd.next(1, 15));
            } else {
                bales.push_back(rnd.next(70, 100));
            }
        }
    } else if (mode == 3) {
        n = rnd.next(12, 20);
        for (int i = 0; i < n; ++i) bales.push_back(rnd.next(1, 100));
    } else if (mode == 4) {
        n = rnd.next(8, 18);
        vector<int> choices = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
        for (int i = 0; i < n; ++i) bales.push_back(rnd.any(choices));
    } else {
        n = rnd.next(6, 20);
        int base = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            int offset = rnd.next(-base + 1, min(100 - base, 10));
            bales.push_back(base + offset);
        }
    }

    shuffle(bales.begin(), bales.end());

    println(n);
    for (int bale : bales) println(bale);

    return 0;
}
