#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> interesting = {1, 2, 3, 4, 5, 7, 8, 13, 16, 31, 32};
    int n = rnd.any(interesting);
    int m = rnd.any(interesting);

    vector<string> image(n, string(m, '0'));
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        char bit = char('0' + rnd.next(0, 1));
        for (int i = 0; i < n; ++i) {
            image[i].assign(m, bit);
        }
    } else if (mode == 1) {
        int block = rnd.any(vector<int>{1, 2, 4});
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                image[i][j] = char('0' + ((i / block + j / block) & 1));
            }
        }
    } else if (mode == 2) {
        int stripeWidth = rnd.any(vector<int>{1, 2, 3, 4});
        bool vertical = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int stripe = vertical ? j / stripeWidth : i / stripeWidth;
                image[i][j] = char('0' + (stripe & 1));
            }
        }
    } else if (mode == 3) {
        int halfN = (n + 1) / 2;
        int halfM = (m + 1) / 2;
        vector<string> tile(halfN, string(halfM, '0'));
        for (int i = 0; i < halfN; ++i) {
            for (int j = 0; j < halfM; ++j) {
                tile[i][j] = char('0' + rnd.next(0, 1));
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                image[i][j] = tile[i % halfN][j % halfM];
            }
        }
    } else if (mode == 4) {
        int splitN = rnd.next(1, n);
        int splitM = rnd.next(1, m);
        char a = char('0' + rnd.next(0, 1));
        char b = char('0' + rnd.next(0, 1));
        char c = char('0' + rnd.next(0, 1));
        char d = char('0' + rnd.next(0, 1));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i < splitN && j < splitM) image[i][j] = a;
                else if (i < splitN) image[i][j] = b;
                else if (j < splitM) image[i][j] = c;
                else image[i][j] = d;
            }
        }
    } else if (mode == 5) {
        double oneProbability = rnd.next(0.15, 0.85);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                image[i][j] = rnd.next() < oneProbability ? '1' : '0';
            }
        }
    } else {
        int base = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int bit = base ^ ((i == 0 || j == 0 || i + 1 == n || j + 1 == m) ? 1 : 0);
                if (rnd.next(0, 9) == 0) bit ^= 1;
                image[i][j] = char('0' + bit);
            }
        }
    }

    println(n, m);
    for (const string& row : image) {
        println(row);
    }

    return 0;
}
