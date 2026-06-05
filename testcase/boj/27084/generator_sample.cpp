#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(2, 25);
        a.resize(n);
        iota(a.begin(), a.end(), 1);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        a.assign(n, rnd.next(1, n));
    } else if (mode == 2) {
        n = rnd.next(3, 30);
        int heavy = rnd.next(1, n);
        int heavyCount = rnd.next(2, n);
        a.assign(heavyCount, heavy);
        for (int value = 1; (int)a.size() < n; ++value) {
            if (value != heavy) a.push_back(value);
        }
    } else if (mode == 3) {
        n = rnd.next(4, 30);
        int labels = rnd.next(2, min(n, 8));
        for (int value = 1; value <= labels; ++value) {
            int count = rnd.next(1, max(1, n / labels + 2));
            while (count-- && (int)a.size() < n) a.push_back(value);
        }
        while ((int)a.size() < n) a.push_back(rnd.next(1, labels));
    } else if (mode == 4) {
        int labels = rnd.next(2, 10);
        for (int value = 1; value <= labels; ++value) {
            int count = rnd.next(1, 4);
            while (count--) a.push_back(value);
        }
        n = (int)a.size();
    } else {
        n = rnd.next(8, 40);
        int labels = rnd.next(1, min(n, 12));
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, labels));
    }

    shuffle(a.begin(), a.end());

    println(n);
    println(a);

    return 0;
}
