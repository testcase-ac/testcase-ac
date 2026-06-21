#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> sequence;

    if (mode == 0) {
        n = 3;
        sequence.push_back(rnd.next(1, n));
    } else if (mode == 1) {
        n = rnd.next(4, 12);
        int center = rnd.next(1, n);
        sequence.assign(n - 2, center);
    } else if (mode == 2) {
        n = rnd.next(5, 14);
        int alphabet = rnd.next(2, n);
        for (int i = 0; i < n - 2; ++i) {
            sequence.push_back(rnd.next(1, alphabet));
        }
    } else if (mode == 3) {
        n = rnd.next(5, 15);
        int lo = rnd.next(1, n);
        int hi = rnd.next(lo, n);
        for (int i = 0; i < n - 2; ++i) {
            sequence.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 4) {
        n = rnd.next(6, 16);
        for (int i = 0; i < n - 2; ++i) {
            int value;
            if (rnd.next(0, 99) < 70) {
                value = rnd.next(max(1, n - 3), n);
            } else {
                value = rnd.next(1, n);
            }
            sequence.push_back(value);
        }
    } else {
        n = rnd.next(4, 18);
        for (int i = 0; i < n - 2; ++i) {
            sequence.push_back(rnd.next(1, n));
        }
        shuffle(sequence.begin(), sequence.end());
    }

    println(n);
    println(sequence);

    return 0;
}
