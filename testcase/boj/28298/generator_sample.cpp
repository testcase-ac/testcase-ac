#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char randomColor(const string& alphabet) {
    return alphabet[rnd.next((int)alphabet.size())];
}

int randomMultiple(int k, int maxValue) {
    return k * rnd.next(1, maxValue / k);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int k;
    int n;
    int m;

    if (mode == 0) {
        k = 1;
        n = rnd.next(1, 12);
        m = rnd.next(1, 18);
    } else if (mode == 1) {
        k = rnd.next(1, 8);
        n = k;
        m = k * rnd.next(1, 4);
    } else {
        k = rnd.next(1, 7);
        n = randomMultiple(k, 30);
        m = randomMultiple(k, 30);
    }

    string alphabet;
    if (mode == 4) {
        alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    } else {
        int colors = rnd.next(2, 6);
        alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        alphabet.resize(colors);
    }

    vector<string> tile(k, string(k, 'A'));
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            tile[i][j] = randomColor(alphabet);
        }
    }

    vector<string> board(n, string(m, 'A'));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            board[i][j] = tile[i % k][j % k];
        }
    }

    if (mode == 2) {
        int changes = rnd.next(1, max(1, n * m / 4));
        for (int t = 0; t < changes; ++t) {
            int i = rnd.next(n);
            int j = rnd.next(m);
            board[i][j] = randomColor(alphabet);
        }
    } else if (mode == 3) {
        for (int x = 0; x < k; ++x) {
            for (int y = 0; y < k; ++y) {
                char a = randomColor(alphabet);
                char b = randomColor(alphabet);
                if (alphabet.size() > 1) {
                    while (b == a) {
                        b = randomColor(alphabet);
                    }
                }

                int seen = 0;
                for (int i = x; i < n; i += k) {
                    for (int j = y; j < m; j += k) {
                        board[i][j] = (seen++ % 2 == 0 ? a : b);
                    }
                }
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                board[i][j] = char('A' + (i * 7 + j * 11 + rnd.next(26)) % 26);
            }
        }
    }

    println(n, m, k);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
