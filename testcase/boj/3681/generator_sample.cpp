#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace {

string weight(int lo = 1, int hi = 60) {
    return to_string(rnd.next(lo, hi));
}

string makeChain(int rods, bool heavyTail) {
    string expr = weight(1, 30);
    for (int i = 0; i < rods; ++i) {
        string leaf = heavyTail && i + 1 == rods ? weight(100, 1000) : weight(1, 40);
        if (rnd.next(2) == 0) {
            expr = "[" + expr + "," + leaf + "]";
        } else {
            expr = "[" + leaf + "," + expr + "]";
        }
    }
    return expr;
}

string makePerfect(int depth, int baseWeight, bool perturb) {
    if (depth == 0) {
        int value = baseWeight;
        if (perturb && rnd.next(5) == 0) {
            value += rnd.next(1, 7);
        }
        return to_string(value);
    }

    int nextWeight = min(baseWeight * 2, 999999999);
    return "[" + makePerfect(depth - 1, nextWeight, perturb) + "," +
           makePerfect(depth - 1, nextWeight, perturb) + "]";
}

string makeRandomTree(int depthLeft) {
    if (depthLeft == 0 || rnd.next(100) < 35) {
        return weight(1, 90);
    }

    string left = makeRandomTree(depthLeft - 1);
    string right = makeRandomTree(depthLeft - 1);
    if (rnd.next(2) == 0) {
        swap(left, right);
    }
    return "[" + left + "," + right + "]";
}

string makeCase() {
    int mode = rnd.next(6);
    if (mode == 0) {
        return weight(1, 999);
    }
    if (mode == 1) {
        return makeChain(rnd.next(1, 7), false);
    }
    if (mode == 2) {
        return makeChain(rnd.next(8, 16), true);
    }
    if (mode == 3) {
        return makePerfect(rnd.next(1, 5), rnd.next(1, 8), false);
    }
    if (mode == 4) {
        return makePerfect(rnd.next(2, 5), rnd.next(1, 8), true);
    }
    return makeRandomTree(rnd.next(2, 7));
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 25);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        println(makeCase());
    }

    return 0;
}
