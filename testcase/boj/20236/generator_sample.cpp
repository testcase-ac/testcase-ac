#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

struct Operation {
    int a;
    int b;
    int w;
};

int pickDifferent(const vector<int>& values, int x) {
    int y = rnd.any(values);
    while (y == x) y = rnd.any(values);
    return y;
}

void addNoise(vector<Operation>& ops, const vector<int>& values, int c, int count) {
    for (int i = 0; i < count; ++i) {
        int a = rnd.any(values);
        int b = rnd.any(values);
        int w = rnd.next(0, 1);
        if (w == 0 && rnd.next(100) < 65) a = pickDifferent(values, c);
        ops.push_back({a, b, w});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> values = {1, 2, 3, 4, 5, 7, 11, 1000000000};
    shuffle(values.begin(), values.end());
    int valueCount = rnd.next(3, (int)values.size());
    values.resize(valueCount);

    int c = rnd.any(values);
    int mode = rnd.next(0, 4);
    vector<Operation> ops;

    if (mode == 0) {
        int length = rnd.next(1, min(8, valueCount + 3));
        int cur = c;
        for (int i = 0; i < length; ++i) {
            int nxt = rnd.next(100) < 30 ? cur : rnd.any(values);
            ops.push_back({cur, nxt, 1});
            cur = nxt;
        }
        addNoise(ops, values, c, rnd.next(0, 8));
    } else if (mode == 1) {
        int length = rnd.next(2, min(7, valueCount + 2));
        int cur = c;
        for (int i = 0; i < length - 1; ++i) {
            int nxt = pickDifferent(values, cur);
            ops.push_back({cur, nxt, 1});
            cur = nxt;
        }
        ops.push_back({cur, c, 1});
        addNoise(ops, values, c, rnd.next(1, 6));
    } else if (mode == 2) {
        int from = rnd.next(100) < 70 ? c : rnd.any(values);
        ops.push_back({from, pickDifferent(values, from), 1});
        ops.push_back({from, pickDifferent(values, from), 1});
        addNoise(ops, values, c, rnd.next(1, 9));
    } else {
        int count = rnd.next(1, 20);
        addNoise(ops, values, c, count);
    }

    shuffle(ops.begin(), ops.end());
    println((int)ops.size(), c);
    for (const Operation& op : ops) println(op.a, op.b, op.w);

    return 0;
}
