#include "testlib.h"

#include <vector>
using namespace std;

long long applyOp(long long value, char op) {
    if (op == '*') return value * value;
    if (op == '+') return value + value;
    return 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int limit = 1000000000;
    int mode = rnd.next(0, 6);
    long long s = 1;
    long long t = 1;

    if (mode == 0) {
        s = rnd.next(1, limit);
        t = s;
    } else if (mode == 1) {
        s = rnd.next(2, limit);
        t = 1;
    } else if (mode == 2) {
        s = rnd.next(2, 31622);
        t = s * s;
    } else if (mode == 3) {
        s = rnd.next(1, 500000000);
        t = s + s;
    } else if (mode == 4) {
        s = rnd.next(2, 1000);
        t = s;

        vector<char> ops = {'*', '+', '/'};
        int steps = rnd.next(2, 6);
        for (int i = 0; i < steps; ++i) {
            vector<char> candidates;
            for (char op : ops) {
                long long next = applyOp(t, op);
                if (1 <= next && next <= limit) candidates.push_back(op);
            }
            if (candidates.empty()) break;
            t = applyOp(t, rnd.any(candidates));
        }
    } else if (mode == 5) {
        s = rnd.next(2, 100);
        t = rnd.next(2, 1000);
        if (s == t) ++t;
    } else {
        s = rnd.next(1, limit);
        t = rnd.next(1, limit);
    }

    println(s, t);
    return 0;
}
