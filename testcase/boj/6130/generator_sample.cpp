#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 60);
    vector<int> cows;

    if (mode == 0) {
        int value = rnd.next(1, 3);
        cows.assign(n, value);
    } else if (mode == 1) {
        int first = rnd.next(0, n);
        int second = rnd.next(first, n);
        cows.insert(cows.end(), first, 1);
        cows.insert(cows.end(), second - first, 2);
        cows.insert(cows.end(), n - second, 3);
    } else if (mode == 2) {
        int first = rnd.next(0, n);
        int second = rnd.next(first, n);
        cows.insert(cows.end(), n - second, 3);
        cows.insert(cows.end(), second - first, 2);
        cows.insert(cows.end(), first, 1);
    } else if (mode == 3) {
        int c1 = rnd.next(1, 20);
        int c2 = rnd.next(1, 20);
        int c3 = rnd.next(1, 20);
        cows.insert(cows.end(), c2, 2);
        cows.insert(cows.end(), c3, 3);
        cows.insert(cows.end(), c1, 1);
        shuffle(cows.begin(), cows.end());
    } else {
        int groups = rnd.next(3, 12);
        for (int i = 0; i < groups; ++i) {
            int value = i % 3 + 1;
            if (rnd.next(0, 1)) {
                value = 3 - i % 3;
            }
            int len = rnd.next(1, 6);
            cows.insert(cows.end(), len, value);
        }
    }

    println(static_cast<int>(cows.size()));
    for (int cow : cows) {
        println(cow);
    }

    return 0;
}
