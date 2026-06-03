#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static void applyReverse(vector<int>& board, int l, int r) {
    reverse(board.begin() + l - 1, board.begin() + r);
}

static pair<int, int> randomInterval(int n) {
    int l = rnd.next(1, n);
    int r = rnd.next(l, n);
    return {l, r};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 5;
    } else if (mode == 6) {
        n = rnd.next(500, 10000);
    } else {
        n = rnd.next(5, 80);
    }

    vector<int> board(n);
    for (int i = 0; i < n; ++i) {
        board[i] = i + 1;
    }

    if (mode == 0) {
        // Already sorted, using the allowed no-op reversal behavior.
    } else if (mode == 1) {
        auto [l, r] = randomInterval(n);
        applyReverse(board, l, r);
    } else if (mode == 2) {
        applyReverse(board, 1, n);
        auto [l, r] = randomInterval(n);
        applyReverse(board, l, r);
    } else if (mode == 3) {
        int split = rnd.next(1, n - 1);
        applyReverse(board, 1, split);
        applyReverse(board, split + 1, n);
    } else if (mode == 4) {
        int l = rnd.next(1, n - 2);
        int mid = rnd.next(l + 1, n - 1);
        int r = rnd.next(mid + 1, n);
        applyReverse(board, l, r);
        applyReverse(board, l, mid);
    } else if (mode == 5) {
        auto [l1, r1] = randomInterval(n);
        auto [l2, r2] = randomInterval(n);
        applyReverse(board, l1, r1);
        applyReverse(board, l2, r2);
    } else {
        int width1 = rnd.next(1, 25);
        int width2 = rnd.next(1, 25);
        int l1 = rnd.next(1, n - width1 + 1);
        int l2 = rnd.next(1, n - width2 + 1);
        applyReverse(board, l1, l1 + width1 - 1);
        applyReverse(board, l2, l2 + width2 - 1);
    }

    println(n);
    println(board);

    return 0;
}
