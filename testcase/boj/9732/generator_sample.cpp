#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    vector<int> powers = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 4096, 8192};
    vector<int> mixed = {6, 10, 12, 18, 24, 36, 48, 72, 96, 120, 210, 360, 840, 1260, 2520, 5040, 7560};
    vector<int> high = {9991, 9999, 10000, 9990, 9984, 9973, 9960, 9900};

    int t = rnd.next(4, 9);
    println(t);

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int mode = rnd.next(0, 5);
        int n = rnd.next(1, 5);
        int m = rnd.next(1, 6);

        if (mode == 0) {
            n = rnd.next(1, 2);
            m = rnd.next(1, 3);
        } else if (mode == 4) {
            n = rnd.next(2, 4);
            m = rnd.next(1, 4);
        }

        println(n, m);

        vector<vector<int>> a(n, vector<int>(m));
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < m; ++col) {
                if (mode == 0) {
                    a[row][col] = rnd.next(2, 12);
                } else if (mode == 1) {
                    a[row][col] = rnd.any(primes);
                } else if (mode == 2) {
                    a[row][col] = rnd.any(powers);
                } else if (mode == 3) {
                    a[row][col] = rnd.any(mixed);
                } else if (mode == 4 && row % 2 == 1) {
                    a[row][col] = a[row - 1][col];
                } else {
                    a[row][col] = rnd.any(high);
                }
            }
        }

        for (int row = 0; row < n; ++row) {
            println(a[row]);
        }
    }

    return 0;
}
