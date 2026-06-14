#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char pickChar(int alphabet) {
    return char('a' + rnd.next(alphabet));
}

vector<string> makeBase(int n, int m, int mode, int alphabet) {
    vector<string> base(n, string(m, 'a'));

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                base[i][j] = pickChar(alphabet);
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            char a = pickChar(alphabet);
            char b = pickChar(alphabet);
            if (alphabet > 1) {
                while (b == a) b = pickChar(alphabet);
            }
            for (int j = 0; j < m; ++j) {
                base[i][j] = (j % 2 == 0 ? a : b);
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            char c = pickChar(alphabet);
            for (int j = 0; j < m; ++j) {
                base[i][j] = c;
            }
        }
    } else {
        int blockH = rnd.next(1, 3);
        int blockW = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                base[i][j] = char('a' + ((i / blockH + j / blockW) % alphabet));
            }
        }
    }

    return base;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(1, mode == 4 ? 12 : 9);
    int m = rnd.next(1, mode == 4 ? 12 : 9);
    int scaleH = rnd.next(1, 5);
    int scaleW = rnd.next(1, 5);

    if (mode == 1) scaleH = 1;
    if (mode == 2) scaleW = 1;
    if (mode == 4) {
        scaleH = rnd.next(2, 4);
        scaleW = rnd.next(2, 4);
    }

    int alphabet = rnd.next(1, 5);
    vector<string> base = makeBase(n, m, mode % 4, alphabet);

    int ni = n * scaleH;
    int mj = m * scaleW;
    println(ni, mj);

    for (int i = 0; i < n; ++i) {
        string expandedRow;
        for (int j = 0; j < m; ++j) {
            expandedRow += string(scaleW, base[i][j]);
        }
        for (int repeat = 0; repeat < scaleH; ++repeat) {
            println(expandedRow);
        }
    }

    return 0;
}
