#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Operation = pair<int, int>;

void addRepeated(vector<Operation>& ops, int t, int a, int count) {
    for (int i = 0; i < count; ++i) ops.push_back({t, a});
}

int pickIndex(int n) {
    if (n == 1) return 1;

    int mode = rnd.next(0, 4);
    if (mode == 0) return 1;
    if (mode == 1) return n;
    if (mode == 2) return rnd.next(1, min(n, 4));
    if (mode == 3) return rnd.next(max(1, n - 3), n);
    return rnd.next(1, n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 6);
    } else if (mode == 2) {
        n = rnd.next(7, 20);
    } else if (mode == 3) {
        n = rnd.next(20, 80);
    } else if (mode == 4) {
        n = rnd.next(100, 1000);
    } else {
        n = rnd.next(1000, 30000);
    }

    vector<Operation> ops;

    if (mode == 0) {
        int q = rnd.next(1, 20);
        for (int i = 0; i < q; ++i) ops.push_back({rnd.next(1, 2), 1});
    } else if (mode == 1) {
        int q = rnd.next(4, 24);
        int type = rnd.next(1, 2);
        for (int i = 0; i < q; ++i) ops.push_back({type, pickIndex(n)});
    } else if (mode == 2) {
        int q = rnd.next(8, 40);
        int row = pickIndex(n);
        int col = pickIndex(n);
        for (int i = 0; i < q; ++i) {
            ops.push_back({i % 2 == 0 ? 1 : 2, i % 2 == 0 ? row : col});
        }
    } else if (mode == 3) {
        int hotRow = pickIndex(n);
        int hotCol = pickIndex(n);
        addRepeated(ops, 1, hotRow, rnd.next(3, 12));
        addRepeated(ops, 2, hotCol, rnd.next(3, 12));

        int extra = rnd.next(6, 30);
        for (int i = 0; i < extra; ++i) ops.push_back({rnd.next(1, 2), pickIndex(n)});
        shuffle(ops.begin(), ops.end());
    } else if (mode == 4) {
        int q = rnd.next(20, 80);
        for (int i = 0; i < q; ++i) {
            int t = rnd.next(1, 2);
            int a = i % 3 == 0 ? pickIndex(n) : rnd.next(1, n);
            ops.push_back({t, a});
        }
    } else {
        int q = rnd.next(40, 120);
        for (int i = 0; i < q; ++i) {
            int t = i % 4 == 0 ? 1 : rnd.next(1, 2);
            int a = i % 5 == 0 ? pickIndex(n) : rnd.next(1, n);
            ops.push_back({t, a});
        }
    }

    println(n, static_cast<int>(ops.size()));
    for (auto [t, a] : ops) println(t, a);

    return 0;
}
