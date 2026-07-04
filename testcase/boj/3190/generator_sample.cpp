#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int N = (mode == 0 ? rnd.next(2, 5) : rnd.next(6, 20));

    vector<pair<int, int>> cells;
    for (int r = 1; r <= N; ++r) {
        for (int c = 1; c <= N; ++c) {
            if (r != 1 || c != 1) cells.push_back({r, c});
        }
    }

    vector<pair<int, int>> preferred;
    if (mode == 1 || mode == 2) {
        for (int c = 2; c <= N; ++c) preferred.push_back({1, c});
        for (int r = 2; r <= N; ++r) preferred.push_back({r, N});
        for (int c = N - 1; c >= 1; --c) preferred.push_back({N, c});
    } else if (mode == 3) {
        for (int r = 1; r <= N; ++r) {
            for (int c = 1; c <= N; ++c) {
                if ((r + c) % 2 == 0 && !(r == 1 && c == 1)) {
                    preferred.push_back({r, c});
                }
            }
        }
    }

    shuffle(cells.begin(), cells.end());
    shuffle(preferred.begin(), preferred.end());

    int maxK = min(100, N * N - 1);
    int K;
    if (mode == 0) {
        K = rnd.next(0, min(maxK, 5));
    } else if (mode == 1) {
        K = rnd.next(1, min(maxK, max(1, N - 1)));
    } else if (mode == 2) {
        K = rnd.next(min(maxK, N / 2), min(maxK, 2 * N));
    } else {
        K = rnd.next(0, min(maxK, 25));
    }

    vector<pair<int, int>> apples;
    set<pair<int, int>> used;
    for (auto p : preferred) {
        if ((int)apples.size() == K) break;
        if (used.insert(p).second) apples.push_back(p);
    }
    for (auto p : cells) {
        if ((int)apples.size() == K) break;
        if (used.insert(p).second) apples.push_back(p);
    }

    int L;
    if (mode == 0) {
        L = rnd.next(1, 8);
    } else if (mode == 1) {
        L = rnd.next(2, 12);
    } else if (mode == 2) {
        L = rnd.next(8, 30);
    } else {
        L = rnd.next(1, 20);
    }

    vector<pair<int, char>> turns;
    int current = 0;
    for (int i = 0; i < L; ++i) {
        int step;
        if (mode == 2) {
            step = rnd.next(1, 3);
        } else if (mode == 1) {
            step = rnd.next(max(1, N / 3), max(1, N));
        } else {
            step = rnd.next(1, max(2, N + 3));
        }
        current = min(10000 - (L - i - 1), current + step);

        char turn;
        if (mode == 2) {
            turn = (i % 2 == 0 ? 'D' : rnd.any(string("LD")));
        } else {
            turn = rnd.any(string("LD"));
        }
        turns.push_back({current, turn});
    }

    println(N);
    println((int)apples.size());
    for (auto p : apples) println(p.first, p.second);
    println((int)turns.size());
    for (auto t : turns) println(t.first, t.second);

    return 0;
}
