#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const int MAX_N = 2147483647;

int randomValue(int mode) {
    if (mode == 0) {
        vector<int> values = {0, 1, 2, 3, 7, 15, 31, 63, 127};
        return rnd.any(values);
    }
    if (mode == 1) {
        vector<int> values = {0, MAX_N, MAX_N - 1, 1 << 30, (1 << 30) - 1};
        return rnd.any(values);
    }
    if (mode == 2) {
        int base = rnd.next(0, 12);
        return rnd.next(0, 3) == 0 ? base : base * rnd.next(1, 5);
    }
    return rnd.next(0, MAX_N);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 5);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int q = rnd.next(1, 30);
        int mode = rnd.next(0, 3);
        int k;
        if (mode == 0) {
            k = 1;
        } else if (mode == 1) {
            k = rnd.next(1, q);
        } else if (mode == 2) {
            k = rnd.next(q, 100000);
        } else {
            k = rnd.any(vector<int>{1, 2, 3, q, 100000});
        }

        println(q, k);

        int inserts = 0;
        vector<int> seen;
        for (int i = 0; i < q; ++i) {
            bool mustInsert = (i == q - 1 && inserts == 0);
            bool doPrint = !mustInsert && (i == 0 || rnd.next(0, 99) < 35);

            if (doPrint) {
                println("print");
                continue;
            }

            int value;
            if (!seen.empty() && rnd.next(0, 99) < 30) {
                value = rnd.any(seen);
            } else {
                value = randomValue(mode);
            }
            seen.push_back(value);
            ++inserts;
            println("insert", value);
        }
    }

    return 0;
}
