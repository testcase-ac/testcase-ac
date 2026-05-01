#include "testlib.h"
using namespace std;

struct Board {
    int N, M;
    vector<string> g;
};

Board genFullSmall() {
    Board b;
    b.N = rnd.next(1, 3);
    b.M = rnd.next(1, 3);
    b.g.assign(b.N, string(b.M, '.'));
    return b;
}

Board genRandomSparseSmall() {
    Board b;
    b.N = rnd.next(2, 6);
    b.M = rnd.next(2, 6);
    int cells = b.N * b.M;
    int E = rnd.next(1, min(10, cells)); // number of empty cells

    vector<pair<int,int>> pos;
    pos.reserve(cells);
    for (int i = 0; i < b.N; ++i)
        for (int j = 0; j < b.M; ++j)
            pos.push_back({i, j});
    shuffle(pos.begin(), pos.end());

    b.g.assign(b.N, string(b.M, '*'));
    for (int k = 0; k < E; ++k) {
        int r = pos[k].first;
        int c = pos[k].second;
        b.g[r][c] = '.';
    }
    return b;
}

Board genLineBoard() {
    Board b;
    bool horizontal = rnd.next(0, 1);
    if (horizontal) {
        b.N = 1;
        b.M = rnd.next(2, 10);
    } else {
        b.N = rnd.next(2, 10);
        b.M = 1;
    }
    b.g.assign(b.N, string(b.M, '*'));
    int maxE = min(10, b.N * b.M);
    int empties = 0;

    for (int i = 0; i < b.N; ++i) {
        for (int j = 0; j < b.M; ++j) {
            if (empties < maxE && rnd.next(0, 99) < 60) {
                b.g[i][j] = '.';
                ++empties;
            }
        }
    }
    if (empties == 0) {
        int r = rnd.next(0, b.N - 1);
        int c = rnd.next(0, b.M - 1);
        b.g[r][c] = '.';
    }
    return b;
}

Board genUnsolvableSplit() {
    Board b;
    b.N = rnd.next(2, 6);
    b.M = rnd.next(4, 7);
    int N = b.N, M = b.M;
    vector<string> g(N, string(M, '*'));

    int barrierCol = rnd.next(1, M - 2); // 0..barrierCol-1 left, barrierCol+1..M-1 right

    vector<pair<int,int>> left, right;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (j < barrierCol) left.push_back({i, j});
            else if (j > barrierCol) right.push_back({i, j});
        }
    }

    int maxL = (int)left.size();
    int maxR = (int)right.size();
    int E1 = rnd.next(1, min(5, maxL));
    int E2 = rnd.next(1, min(5, maxR));
    while (E1 + E2 > 12 && (E1 > 1 || E2 > 1)) {
        if (E1 > E2 && E1 > 1) --E1;
        else if (E2 > 1) --E2;
        else break;
    }

    shuffle(left.begin(), left.end());
    shuffle(right.begin(), right.end());

    for (int i = 0; i < E1; ++i)
        g[left[i].first][left[i].second] = '.';
    for (int i = 0; i < E2; ++i)
        g[right[i].first][right[i].second] = '.';

    b.g = g;
    return b;
}

Board genRandomMedium() {
    Board b;
    b.N = rnd.next(4, 7);
    b.M = rnd.next(4, 7);
    int cells = b.N * b.M;
    int E = rnd.next(3, min(12, cells));

    vector<pair<int,int>> pos;
    pos.reserve(cells);
    for (int i = 0; i < b.N; ++i)
        for (int j = 0; j < b.M; ++j)
            pos.push_back({i, j});
    shuffle(pos.begin(), pos.end());

    b.g.assign(b.N, string(b.M, '*'));
    for (int k = 0; k < E; ++k) {
        int r = pos[k].first;
        int c = pos[k].second;
        b.g[r][c] = '.';
    }
    return b;
}

Board generateType(int type) {
    if (type == 0) return genFullSmall();
    if (type == 1) return genRandomSparseSmall();
    if (type == 2) return genRandomMedium();
    if (type == 3) return genUnsolvableSplit();
    return genLineBoard(); // type 4
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 3);
    vector<Board> tests;
    tests.reserve(T);
    bool hasUnsolvable = false;

    for (int i = 0; i < T; ++i) {
        int type = rnd.next(0, 4); // 0..4
        if (type == 3) hasUnsolvable = true;
        Board b = generateType(type);

        // Ensure at least one empty cell
        bool anyDot = false;
        for (int r = 0; r < b.N; ++r) {
            if (b.g[r].find('.') != string::npos) {
                anyDot = true;
                break;
            }
        }
        if (!anyDot) {
            int rr = rnd.next(0, b.N - 1);
            int cc = rnd.next(0, b.M - 1);
            b.g[rr][cc] = '.';
        }

        tests.push_back(b);
    }

    if (!hasUnsolvable) {
        int idx = rnd.next(0, T - 1);
        tests[idx] = genUnsolvableSplit();
    }

    for (auto &b : tests) {
        println(b.N, b.M);
        for (int i = 0; i < b.N; ++i)
            println(b.g[i]);
    }

    return 0;
}
