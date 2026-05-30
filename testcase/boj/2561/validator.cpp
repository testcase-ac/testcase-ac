#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static int breakpointCount(const vector<int>& a) {
    int n = (int)a.size() - 2;
    int result = 0;
    for (int i = 0; i <= n; ++i) {
        if (abs(a[i + 1] - a[i]) != 1) {
            ++result;
        }
    }
    return result;
}

static bool isSortedBoard(const vector<int>& a) {
    int n = (int)a.size() - 2;
    for (int i = 1; i <= n; ++i) {
        if (a[i] != i) {
            return false;
        }
    }
    return true;
}

static bool canSortInReversals(vector<int>& a, int remaining) {
    int breaks = breakpointCount(a);
    if (breaks == 0) {
        return true;
    }
    if (remaining == 0 || breaks > 2 * remaining) {
        return false;
    }

    int n = (int)a.size() - 2;
    vector<int> cuts;
    for (int i = 0; i <= n; ++i) {
        if (abs(a[i + 1] - a[i]) != 1) {
            cuts.push_back(i);
            cuts.push_back(i + 1);
        }
    }
    sort(cuts.begin(), cuts.end());
    cuts.erase(unique(cuts.begin(), cuts.end()), cuts.end());

    for (int left : cuts) {
        if (left < 1 || left > n) {
            continue;
        }
        for (int right : cuts) {
            if (right < left || right > n) {
                continue;
            }
            reverse(a.begin() + left, a.begin() + right + 1);
            if (canSortInReversals(a, remaining - 1)) {
                return true;
            }
            reverse(a.begin() + left, a.begin() + right + 1);
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 1000, "N");
    inf.readEoln();

    vector<int> input = inf.readInts(n, 1, n, "a_i");
    inf.readEoln();

    vector<int> seen(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        ensuref(!seen[input[i]], "duplicate value %d at position %d", input[i], i + 1);
        seen[input[i]] = 1;
    }

    vector<int> board(n + 2);
    board[0] = 0;
    for (int i = 0; i < n; ++i) {
        board[i + 1] = input[i];
    }
    board[n + 1] = n + 1;

    ensuref(isSortedBoard(board) || canSortInReversals(board, 3),
            "board state must be reachable from sorted order with at most three reversals");

    inf.readEof();
}
