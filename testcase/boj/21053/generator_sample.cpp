#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> hype;

    if (mode == 0) {
        n = rnd.next(1, 8);
        int value = rnd.next(1, 3);
        hype.assign(n, value);
    } else if (mode == 1) {
        int ones = rnd.next(1, 8);
        int twos = rnd.next(1, 12);
        int threes = rnd.next(1, 8);
        n = ones + twos + threes;
        hype.insert(hype.end(), ones, 1);
        hype.insert(hype.end(), twos, 2);
        hype.insert(hype.end(), threes, 3);
    } else if (mode == 2) {
        n = rnd.next(3, 35);
        hype.resize(n);
        int start = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            hype[i] = (start + i - 1) % 3 + 1;
        }
    } else if (mode == 3) {
        n = rnd.next(3, 45);
        hype.resize(n);
        vector<int> weights = {rnd.next(1, 8), rnd.next(1, 8), rnd.next(1, 8)};
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(1, weights[0] + weights[1] + weights[2]);
            if (pick <= weights[0]) {
                hype[i] = 1;
            } else if (pick <= weights[0] + weights[1]) {
                hype[i] = 2;
            } else {
                hype[i] = 3;
            }
        }
    } else if (mode == 4) {
        int chunks = rnd.next(2, 8);
        for (int c = 0; c < chunks; ++c) {
            int value = rnd.next(1, 3);
            int len = rnd.next(1, 7);
            hype.insert(hype.end(), len, value);
        }
        n = (int)hype.size();
    } else {
        n = rnd.next(40, 120);
        hype.resize(n);
        for (int i = 0; i < n; ++i) {
            if (i < n / 4) {
                hype[i] = rnd.next(1, 2);
            } else if (i > 3 * n / 4) {
                hype[i] = rnd.next(2, 3);
            } else {
                hype[i] = rnd.next(1, 3);
            }
        }
    }

    println(n);
    println(hype);
    return 0;
}
