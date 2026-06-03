#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampPreference(int value) {
    return max(1, min(3000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    vector<int> preference(3);

    if (mode == 0) {
        n = rnd.next(1, 12);
        for (int i = 0; i < 3; ++i) {
            preference[i] = rnd.next(1, 20);
        }
    } else if (mode == 1) {
        n = rnd.next(1, 1000);
        for (int i = 0; i < 3; ++i) {
            preference[i] = clampPreference(n + rnd.next(-3, 3));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 1000);
        preference = {
            rnd.next(1, min(3000, max(1, n / 2))),
            rnd.next(n, 3000),
            rnd.next(n, 3000),
        };
        shuffle(preference.begin(), preference.end());
    } else if (mode == 3) {
        n = rnd.next(1, 1000);
        for (int i = 0; i < 3; ++i) {
            preference[i] = rnd.next(2500, 3000);
        }
    } else {
        n = rnd.any(vector<int>{1, 2, 999, 1000});
        for (int i = 0; i < 3; ++i) {
            preference[i] = rnd.any(vector<int>{1, 2, n, min(3000, n + 1), 2999, 3000});
        }
    }

    println(n);
    println(preference);

    return 0;
}
