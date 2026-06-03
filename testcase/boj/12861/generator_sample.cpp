#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int p;
    int q;
    set<int> chosen;

    if (mode == 0) {
        p = rnd.next(1, 30);
        q = 1;
        chosen.insert(rnd.next(1, p));
    } else if (mode == 1) {
        p = rnd.next(2, 60);
        q = rnd.next(1, min(12, p));
        int start = rnd.next(1, p - q + 1);
        for (int i = 0; i < q; ++i) chosen.insert(start + i);
    } else if (mode == 2) {
        p = rnd.next(3, 120);
        q = rnd.next(2, min(18, p));
        chosen.insert(1);
        chosen.insert(p);
        while ((int)chosen.size() < q) chosen.insert(rnd.next(1, p));
    } else if (mode == 3) {
        p = rnd.next(10, 250);
        q = rnd.next(3, min(25, p));
        for (int i = 0; i < q; ++i) {
            long long value = 1 + (long long)i * (p - 1) / max(1, q - 1);
            chosen.insert((int)value);
        }
        while ((int)chosen.size() < q) chosen.insert(rnd.next(1, p));
    } else if (mode == 4) {
        p = rnd.next(100, 10000);
        q = rnd.next(20, 100);
        while ((int)chosen.size() < q) {
            int block = rnd.next(0, 2);
            if (block == 0) {
                chosen.insert(rnd.next(1, min(p, 150)));
            } else if (block == 1) {
                chosen.insert(rnd.next(max(1, p - 149), p));
            } else {
                chosen.insert(rnd.next(1, p));
            }
        }
    } else {
        p = rnd.next(1, 500);
        q = rnd.next(1, min(35, p));
        while ((int)chosen.size() < q) chosen.insert(rnd.next(1, p));
    }

    vector<int> rooms(chosen.begin(), chosen.end());
    if (rnd.next(0, 1)) shuffle(rooms.begin(), rooms.end());

    println(p, q);
    println(rooms);

    return 0;
}
