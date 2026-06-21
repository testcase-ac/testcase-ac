#include "testlib.h"
#include <array>
#include <string>
#include <vector>
using namespace std;

char randomLetter() {
    return rnd.any(string("JOI"));
}

array<string, 2> randomEmblem() {
    return {string{randomLetter(), randomLetter()},
            string{randomLetter(), randomLetter()}};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int m = 2, n = 2;
    if (mode == 0) {
        m = rnd.next(2, 4);
        n = rnd.next(2, 5);
    } else {
        m = rnd.next(2, 8);
        n = rnd.next(2, 9);
    }

    array<string, 2> emblem = randomEmblem();
    vector<string> flag(m, string(n, 'J'));

    if (mode == 0) {
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                flag[i][j] = randomLetter();
    } else if (mode == 1) {
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                flag[i][j] = emblem[i % 2][j % 2];

        int changes = rnd.next(1, max(1, m * n / 3));
        for (int k = 0; k < changes; ++k)
            flag[rnd.next(0, m - 1)][rnd.next(0, n - 1)] = randomLetter();
    } else if (mode == 2) {
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                flag[i][j] = randomLetter();

        int blocks = rnd.next(1, min(4, (m - 1) * (n - 1)));
        for (int k = 0; k < blocks; ++k) {
            int r = rnd.next(0, m - 2);
            int c = rnd.next(0, n - 2);
            flag[r][c] = emblem[0][0];
            flag[r][c + 1] = emblem[0][1];
            flag[r + 1][c] = emblem[1][0];
            flag[r + 1][c + 1] = emblem[1][1];
        }
    } else if (mode == 3) {
        char fill = randomLetter();
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                flag[i][j] = fill;

        int changes = rnd.next(0, max(1, m + n));
        for (int k = 0; k < changes; ++k)
            flag[rnd.next(0, m - 1)][rnd.next(0, n - 1)] = randomLetter();
    } else {
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                flag[i][j] = emblem[i < 2 ? i : rnd.next(0, 1)]
                                   [j < 2 ? j : rnd.next(0, 1)];

        int r = rnd.next(0, m - 2);
        int c = rnd.next(0, n - 2);
        int cell = rnd.next(0, 3);
        flag[r + cell / 2][c + cell % 2] = randomLetter();
    }

    println(m, n);
    for (const string& row : flag)
        println(row);
    println(emblem[0]);
    println(emblem[1]);

    return 0;
}
