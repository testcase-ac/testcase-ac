#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 5) {
        n = rnd.next(35, 80);
    } else {
        n = rnd.next(1, 18);
    }

    vector<int> inversion(n);
    if (mode == 0) {
        fill(inversion.begin(), inversion.end(), 0);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            inversion[i] = i;
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            inversion[i] = rnd.next(0, min(i, 2));
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            inversion[i] = (i % 2 == 0) ? 0 : i;
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            inversion[i] = rnd.next(0, i);
        }
    } else {
        int cap = rnd.next(3, 12);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                inversion[i] = i;
            } else {
                inversion[i] = rnd.next(0, min(i, cap));
            }
        }
    }

    println(n);
    println(inversion);
    return 0;
}
