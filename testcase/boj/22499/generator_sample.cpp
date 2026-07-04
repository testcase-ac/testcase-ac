#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 24);
    vector<int> a;

    auto addMany = [&](int value, int count) {
        while (count-- > 0 && (int)a.size() < n) a.push_back(value);
    };

    if (mode == 0) {
        n = rnd.next(1, 18);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(0, 6));
    } else if (mode == 1) {
        n = rnd.next(2, 24);
        addMany(0, rnd.next(1, min(8, n)));
        if ((int)a.size() < n) {
            addMany(1, rnd.next(0, min(8, n - (int)a.size())));
        }
        while ((int)a.size() < n) a.push_back(rnd.next(2, 12));
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        addMany(2, rnd.next(1, min(5, n)));
        if ((int)a.size() < n) {
            addMany(3, rnd.next(1, min(5, n - (int)a.size())));
        }
        while ((int)a.size() < n) a.push_back(rnd.next(0, 9));
    } else if (mode == 3) {
        n = rnd.next(1, 16);
        for (int i = 0; i < n; ++i) {
            int base = rnd.next(0, 4);
            if (base == 0) a.push_back(0);
            else if (base == 1) a.push_back(1);
            else a.push_back(rnd.next(999999990, 1000000000));
        }
    } else if (mode == 4) {
        n = rnd.next(4, 24);
        vector<int> pool = {0, 1, 2, 3, 4, 5, 10, 100, 1000000000};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    } else {
        n = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            int kind = rnd.next(0, 9);
            if (kind < 2) a.push_back(0);
            else if (kind < 4) a.push_back(1);
            else if (kind < 7) a.push_back(rnd.next(2, 30));
            else a.push_back(rnd.next(1, 1000000000));
        }
    }

    shuffle(a.begin(), a.end());

    println((int)a.size());
    for (int x : a) println(x);

    return 0;
}
