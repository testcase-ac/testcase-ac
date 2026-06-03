#include "testlib.h"
#include <array>
#include <vector>
using namespace std;

const int MAX_VALUE = 1000000000;

int randomValue(int mode) {
    if (mode == 0) return rnd.next(0, 15);
    if (mode == 1) return rnd.next(0, 1023);
    if (mode == 2) return rnd.next(MAX_VALUE - 1024, MAX_VALUE);
    return rnd.next(0, MAX_VALUE);
}

void printRow(const vector<int>& row) {
    println(row);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n = 1;
        if (mode == 0) {
            n = rnd.next(1, 3);
        } else if (mode == 1) {
            n = rnd.next(4, 10);
        } else if (mode == 2) {
            n = rnd.next(8, 20);
        } else if (mode == 3) {
            n = rnd.next(20, 50);
        } else {
            n = rnd.any(vector<int>{1, 2, 5, 17, 50});
        }

        int valueMode = rnd.next(0, 3);
        int k = randomValue(valueMode);
        array<vector<int>, 4> rows;
        for (int i = 0; i < 4; ++i) rows[i].resize(n);

        if (mode == 0) {
            int base = randomValue(valueMode);
            for (int i = 0; i < 4; ++i) {
                int rowValue = (i == 3 ? (base ^ k) : base);
                rowValue %= (MAX_VALUE + 1);
                fill(rows[i].begin(), rows[i].end(), rowValue);
            }
        } else if (mode == 1) {
            for (int i = 0; i < n; ++i) {
                int a = randomValue(valueMode);
                int b = randomValue(valueMode);
                int c = randomValue(valueMode);
                int d = a ^ b ^ c ^ k;
                if (d > MAX_VALUE) d = randomValue(0);
                rows[0][i] = a;
                rows[1][i] = b;
                rows[2][i] = c;
                rows[3][i] = d;
            }
        } else {
            int duplicatePool = rnd.next(1, min(n, 8));
            vector<int> pool;
            for (int i = 0; i < duplicatePool; ++i) pool.push_back(randomValue(valueMode));

            for (int row = 0; row < 4; ++row) {
                for (int i = 0; i < n; ++i) {
                    if (rnd.next(0, 99) < 65) {
                        rows[row][i] = rnd.any(pool);
                    } else {
                        rows[row][i] = randomValue(valueMode);
                    }
                }
            }

            if (n > 0 && rnd.next(0, 1)) {
                int a = rows[0][0];
                int b = rows[1][0];
                int c = rows[2][0];
                int d = a ^ b ^ c ^ k;
                if (d <= MAX_VALUE) rows[3][0] = d;
            }
        }

        if (rnd.next(0, 3) == 0) k = rnd.any(vector<int>{0, 1, MAX_VALUE});

        println(n, k);
        for (int row = 0; row < 4; ++row) printRow(rows[row]);
    }

    return 0;
}
