#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

vector<vector<int>> makeRandomMatrix(int n) {
    vector<vector<int>> a(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) a[i][i] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int v = rnd.next(0, 1);
            a[i][j] = v == 1 ? 2 : 0;
            a[j][i] = v == 1 ? 0 : 2;
        }
    }
    return a;
}

vector<vector<int>> makeRankedMatrix(int n) {
    vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;
    shuffle(order.begin(), order.end());

    vector<int> rank(n);
    for (int i = 0; i < n; ++i) rank[order[i]] = i;

    vector<vector<int>> a(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                a[i][j] = 1;
            } else if (rank[i] < rank[j]) {
                a[i][j] = 2;
            }
        }
    }
    return a;
}

vector<vector<int>> makeDominantMatrix(int n) {
    vector<vector<int>> a = makeRandomMatrix(n);
    int dominant = rnd.next(0, n - 1);
    for (int i = 0; i < n; ++i) {
        if (i == dominant) continue;
        a[dominant][i] = 2;
        a[i][dominant] = 0;
    }
    return a;
}

vector<int> makeMoves(int n, int mode) {
    vector<int> moves(20);
    if (mode == 0) {
        int gesture = rnd.next(1, n);
        fill(moves.begin(), moves.end(), gesture);
    } else if (mode == 1) {
        int period = rnd.next(1, min(n, 5));
        vector<int> pattern;
        for (int i = 0; i < period; ++i) pattern.push_back(rnd.next(1, n));
        for (int i = 0; i < 20; ++i) moves[i] = pattern[i % period];
    } else if (mode == 2) {
        vector<int> pool;
        for (int i = 1; i <= n; ++i) pool.push_back(i);
        shuffle(pool.begin(), pool.end());
        int used = rnd.next(1, min(n, 4));
        pool.resize(used);
        for (int i = 0; i < 20; ++i) moves[i] = rnd.any(pool);
    } else {
        for (int i = 0; i < 20; ++i) moves[i] = rnd.next(1, n);
    }
    return moves;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int k;
    if (mode == 0) {
        n = 1;
        k = 1;
    } else if (mode == 1) {
        n = rnd.next(1, 3);
        k = rnd.next(1, min(6, n));
    } else if (mode == 2) {
        n = rnd.next(4, 6);
        k = rnd.next(1, min(6, n));
    } else if (mode == 3) {
        n = 9;
        k = rnd.next(1, 6);
    } else if (mode == 4) {
        n = rnd.next(6, 9);
        k = 6;
    } else {
        n = rnd.next(1, 9);
        k = rnd.next(1, 6);
    }

    vector<vector<int>> a;
    if (mode == 2 || mode == 4) {
        a = makeRankedMatrix(n);
    } else if (mode == 3 || mode == 6) {
        a = makeDominantMatrix(n);
    } else {
        a = makeRandomMatrix(n);
    }

    int moveMode1 = rnd.next(0, 3);
    int moveMode2 = rnd.next(0, 3);
    if (mode == 0) {
        moveMode1 = 0;
        moveMode2 = 0;
    }

    println(n, k);
    for (int i = 0; i < n; ++i) println(a[i]);
    println(makeMoves(n, moveMode1));
    println(makeMoves(n, moveMode2));

    return 0;
}
