#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

static vector<int> makeMines(int n, int mode) {
    vector<int> mines(n, 0);

    if (mode == 0) {
        double density = rnd.next(0.0, 0.45);
        for (int i = 0; i < n; ++i) mines[i] = rnd.next() < density;
    } else if (mode == 1) {
        double density = rnd.next(0.55, 1.0);
        for (int i = 0; i < n; ++i) mines[i] = rnd.next() < density;
    } else if (mode == 2) {
        int parity = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) mines[i] = (i % 2 == parity);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 5) == 0) mines[i] ^= 1;
        }
    } else if (mode == 3) {
        int blocks = rnd.next(1, min(n, 4));
        for (int b = 0; b < blocks; ++b) {
            int l = rnd.next(0, n - 1);
            int r = rnd.next(l, min(n - 1, l + rnd.next(0, 5)));
            for (int i = l; i <= r; ++i) mines[i] = 1;
        }
    } else {
        int count = rnd.next(0, n);
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i;
        shuffle(order.begin(), order.end());
        for (int i = 0; i < count; ++i) mines[order[i]] = 1;
    }

    return mines;
}

static string makeDigits(const vector<int>& mines) {
    int n = (int)mines.size();
    string digits;
    for (int i = 0; i < n; ++i) {
        int count = mines[i];
        if (i > 0) count += mines[i - 1];
        if (i + 1 < n) count += mines[i + 1];
        digits.push_back(char('0' + count));
    }
    return digits;
}

static string makeCells(const vector<int>& mines) {
    int n = (int)mines.size();
    string cells(n, '#');
    double revealProb = rnd.next(0.0, 0.85);
    for (int i = 0; i < n; ++i) {
        if (mines[i] && rnd.next() < revealProb) cells[i] = '*';
    }
    return cells;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0 && rnd.next(0, 3) == 0) {
            n = 1;
        } else if (rnd.next(0, 8) == 0) {
            n = rnd.next(31, 100);
        } else {
            n = rnd.next(1, 30);
        }

        int mode = rnd.next(0, 4);
        vector<int> mines = makeMines(n, mode);
        println(n);
        println(makeDigits(mines));
        println(makeCells(mines));
    }

    return 0;
}
