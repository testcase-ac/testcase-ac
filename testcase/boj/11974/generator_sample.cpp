#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(5, 12);
    } else if (mode == 2) {
        n = rnd.next(8, 20);
    } else if (mode == 3) {
        n = rnd.next(10, 30);
    } else if (mode == 4) {
        n = rnd.next(12, 35);
    } else {
        n = rnd.next(25, 60);
    }

    vector<int> ids;
    set<int> used;

    auto addId = [&](int value) {
        while (used.count(value)) {
            value = (value + 7 <= 1000000) ? value + 7 : value % 7;
        }
        ids.push_back(value);
        used.insert(value);
    };

    auto addResidue = [&](int residue, int minValue, int maxValue) {
        int first = minValue + (residue - minValue % 7 + 7) % 7;
        int last = maxValue - (maxValue % 7 - residue + 7) % 7;
        if (first > last) {
            first = residue;
            last = 1000000 - (1000000 % 7 - residue + 7) % 7;
        }
        int steps = (last - first) / 7;
        addId(first + 7 * rnd.next(0, steps));
    };

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            addResidue(rnd.next(0, 6), 0, 30);
        }
    } else if (mode == 1) {
        int residue = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            addResidue(residue, 0, 200);
        }
    } else if (mode == 2) {
        int segment = rnd.next(2, n);
        int sumResidue = 0;
        for (int i = 0; i < n; ++i) {
            int residue;
            if (i + 1 == segment) {
                residue = (7 - sumResidue) % 7;
            } else {
                residue = rnd.next(0, 6);
                sumResidue = (sumResidue + residue) % 7;
            }
            addResidue(residue, 0, 500);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            addResidue(rnd.next(0, 6), 999000, 1000000);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int residue = (i % 2 == 0) ? rnd.next(0, 1) : rnd.next(5, 6);
            addResidue(residue, 0, 1000);
        }
        shuffle(ids.begin(), ids.end());
    } else {
        for (int i = 0; i < n; ++i) {
            addResidue(i % 7, 0, 1000000);
        }
        shuffle(ids.begin(), ids.end());
    }

    println(n);
    for (int id : ids) {
        println(id);
    }

    return 0;
}
