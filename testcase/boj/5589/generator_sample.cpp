#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int randomBit(double oneProbability) {
    return rnd.next() < oneProbability ? 1 : 0;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int r = rnd.next(1, 10);
    int c = rnd.next(1, 24);
    vector<vector<int>> a(r, vector<int>(c));

    if (mode == 0) {
        r = rnd.next(1, 3);
        c = rnd.next(1, 8);
        a.assign(r, vector<int>(c));
        double p = rnd.any(vector<double>{0.0, 0.15, 0.5, 0.85, 1.0});
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) a[i][j] = randomBit(p);
        }
    } else if (mode == 1) {
        r = rnd.next(2, 10);
        c = rnd.next(2, 20);
        a.assign(r, vector<int>(c));
        int rowShift = rnd.next(0, 1);
        int colShift = rnd.next(0, 1);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                a[i][j] = ((i + rowShift) ^ (j + colShift)) & 1;
            }
        }
    } else if (mode == 2) {
        r = rnd.next(3, 10);
        c = rnd.next(4, 24);
        a.assign(r, vector<int>(c));
        vector<int> rowFlip(r), colFlip(c);
        for (int i = 0; i < r; ++i) rowFlip[i] = rnd.next(0, 1);
        for (int j = 0; j < c; ++j) colFlip[j] = rnd.next(0, 1);
        int base = rnd.next(0, 1);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                a[i][j] = base ^ rowFlip[i] ^ colFlip[j];
                if (rnd.next(0, 9) == 0) a[i][j] ^= 1;
            }
        }
    } else if (mode == 3) {
        r = rnd.next(2, 10);
        c = rnd.next(8, 30);
        a.assign(r, vector<int>(c));
        int patterns = rnd.next(1, min(6, c));
        vector<vector<int>> columns(patterns, vector<int>(r));
        for (int p = 0; p < patterns; ++p) {
            for (int i = 0; i < r; ++i) columns[p][i] = rnd.next(0, 1);
        }
        for (int j = 0; j < c; ++j) {
            int p = rnd.next(0, patterns - 1);
            bool invert = rnd.next(0, 3) == 0;
            for (int i = 0; i < r; ++i) a[i][j] = columns[p][i] ^ invert;
        }
    } else if (mode == 4) {
        r = rnd.next(8, 10);
        c = rnd.next(20, 60);
        a.assign(r, vector<int>(c));
        double p = rnd.next(0.25, 0.75);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) a[i][j] = randomBit(p);
        }
    } else {
        r = rnd.next(1, 10);
        c = rnd.any(vector<int>{1, 2, 9999, 10000});
        a.assign(r, vector<int>(c));
        double p = rnd.any(vector<double>{0.02, 0.98});
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) a[i][j] = randomBit(p);
        }
    }

    println(r, c);
    for (int i = 0; i < r; ++i) println(a[i]);

    return 0;
}
