#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static bool isSorted(const vector<int>& a) {
    for (int i = 0; i < (int)a.size(); ++i) {
        if (a[i] != i + 1) {
            return false;
        }
    }
    return true;
}

static bool canSortWithTwoReversals(vector<int> a, int depth) {
    if (isSorted(a)) {
        return true;
    }
    if (depth == 0) {
        return false;
    }

    int n = (int)a.size();
    int left = 0;
    while (left < n && a[left] == left + 1) {
        ++left;
    }

    int right = n - 1;
    while (right >= 0 && a[right] == right + 1) {
        --right;
    }

    vector<int> position(n + 1);
    for (int i = 0; i < n; ++i) {
        position[a[i]] = i;
    }

    vector<pair<int, int>> candidates;
    candidates.push_back({left, position[left + 1]});
    candidates.push_back({position[right + 1], right});

    for (auto [l, r] : candidates) {
        if (l > r) {
            swap(l, r);
        }
        vector<int> next = a;
        reverse(next.begin() + l, next.begin() + r + 1);
        if (canSortWithTwoReversals(next, depth - 1)) {
            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 10000, "n");
    inf.readEoln();

    vector<int> board = inf.readInts(n, 1, n, "a_i");
    inf.readEoln();
    inf.readEof();

    vector<int> seen(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        ensuref(!seen[board[i]], "board is not a permutation: value %d appears more than once", board[i]);
        seen[board[i]] = 1;
    }

    ensuref(canSortWithTwoReversals(board, 2), "board cannot be restored by at most two reversals");
}
