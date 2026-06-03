#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int s = 1;
    int c = 1;
    vector<int> lengths;

    if (mode == 0) {
        s = rnd.next(1, 5);
        c = rnd.next(s, s + 8);
        int upper = rnd.next(1, 20);
        for (int i = 0; i < s; ++i) {
            lengths.push_back(rnd.next(1, upper));
        }
    } else if (mode == 1) {
        s = rnd.next(2, 8);
        c = rnd.next(s, s * 4);
        int unit = rnd.next(1, 200);
        for (int i = 0; i < s; ++i) {
            int pieces = rnd.next(1, 6);
            int remainder = rnd.next(0, unit - 1);
            lengths.push_back(unit * pieces + remainder);
        }
    } else if (mode == 2) {
        s = rnd.next(1, 10);
        c = rnd.next(s, 100);
        for (int i = 0; i < s; ++i) {
            lengths.push_back(rnd.next(999999900, 1000000000));
        }
    } else if (mode == 3) {
        s = rnd.next(3, 15);
        c = rnd.next(s, s * 10);
        int base = rnd.next(2, 1000);
        for (int i = 0; i < s; ++i) {
            int pattern = rnd.next(0, 2);
            if (pattern == 0) {
                lengths.push_back(base);
            } else if (pattern == 1) {
                lengths.push_back(base * rnd.next(1, 20));
            } else {
                lengths.push_back(max(1, base - rnd.next(0, base - 1)));
            }
        }
    } else if (mode == 4) {
        s = rnd.next(1, 6);
        c = rnd.next(max(s, 50), 1000000);
        for (int i = 0; i < s; ++i) {
            lengths.push_back(rnd.next(1, 1000));
        }
    } else {
        s = rnd.next(8, 30);
        c = rnd.next(s, min(1000000, s * rnd.next(20, 200)));
        int lo = rnd.next(1, 10000);
        int hi = rnd.next(lo, min(1000000000, lo + rnd.next(1000, 1000000)));
        for (int i = 0; i < s; ++i) {
            lengths.push_back(rnd.next(lo, hi));
        }
    }

    shuffle(lengths.begin(), lengths.end());

    println(s, c);
    for (int length : lengths) {
        println(length);
    }

    return 0;
}
