#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 35);
    set<int> values;

    if (mode == 0) {
        int start = rnd.next(1, 80);
        int diff = rnd.next(1, 18);
        int len = rnd.next(3, min(14, n));
        for (int i = 0; i < len; ++i) values.insert(start + diff * i);
    } else if (mode == 1) {
        int start = rnd.next(999700, 999940);
        int diff = rnd.next(1, 20);
        int len = rnd.next(3, min(12, n));
        while (start + diff * (len - 1) > 1000000) --len;
        for (int i = 0; i < len; ++i) values.insert(start + diff * i);
    } else if (mode == 2) {
        int base = rnd.next(1, 120);
        int clusters = rnd.next(2, 5);
        for (int c = 0; c < clusters; ++c) {
            int center = base + c * rnd.next(15, 45);
            int width = rnd.next(2, 8);
            for (int x = center; x <= center + width; ++x) values.insert(x);
        }
    } else if (mode == 3) {
        int x = rnd.next(1, 12);
        while ((int)values.size() < n && x <= 1000000) {
            values.insert(x);
            x += rnd.next(25, 80);
        }
    } else if (mode == 4) {
        int first = rnd.next(1, 40);
        int diffA = rnd.next(2, 13);
        int diffB = rnd.next(2, 17);
        int lenA = rnd.next(3, min(9, n));
        int lenB = rnd.next(3, min(9, n));
        for (int i = 0; i < lenA; ++i) values.insert(first + diffA * i);
        int second = first + rnd.next(5, 70);
        for (int i = 0; i < lenB; ++i) values.insert(second + diffB * i);
    }

    while ((int)values.size() < n) {
        if (mode == 1) {
            values.insert(rnd.next(999650, 1000000));
        } else if (mode == 3) {
            values.insert(rnd.next(1, 1000000));
        } else {
            values.insert(rnd.next(1, 350));
        }
    }

    vector<int> tiles(values.begin(), values.end());
    println((int)tiles.size());
    println(tiles);

    return 0;
}
