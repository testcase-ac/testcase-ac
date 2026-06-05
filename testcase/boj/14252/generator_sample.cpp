#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>
using namespace std;

static void addValue(set<int>& values, int x) {
    if (1 <= x && x <= 100000) values.insert(x);
}

static void addCoprimeRun(set<int>& values) {
    int len = rnd.next(2, 10);
    int start = rnd.next(1, 80);
    for (int i = 0; i < len; ++i) addValue(values, start + i);
}

static void addHardPair(set<int>& values) {
    vector<pair<int, int>> known = {
        {2184, 2200}, {27830, 27846}, {32214, 32230}, {57860, 57876},
        {62244, 62260}, {87890, 87906}, {92274, 92290},
    };

    if (rnd.next(0, 3) == 0) {
        auto p = rnd.any(known);
        addValue(values, p.first);
        addValue(values, p.second);
        return;
    }

    int base = 6 * rnd.next(1, 1500);
    int gap = rnd.any(vector<int>{2, 4, 6, 8, 10, 12, 16});
    addValue(values, base);
    addValue(values, base + gap);
}

static void addBridgeablePair(set<int>& values) {
    int a = 2 * rnd.next(2, 8000);
    int b = a + rnd.any(vector<int>{6, 8, 10, 12, 18, 24});
    addValue(values, a);
    addValue(values, b);

    if (rnd.next(0, 2) == 0) {
        for (int x = a + 1; x < b; ++x) {
            if (gcd(a, x) == 1 && gcd(x, b) == 1) {
                addValue(values, x);
                break;
            }
        }
    }
}

static void addRandomSet(set<int>& values) {
    int len = rnd.next(3, 12);
    int lo = rnd.next(1, 500);
    int span = rnd.next(len + 5, 120);
    while ((int)values.size() < len) addValue(values, lo + rnd.next(0, span));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    set<int> values;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        addValue(values, rnd.next(1, 100000));
    } else if (mode == 1) {
        addCoprimeRun(values);
    } else if (mode == 2) {
        addHardPair(values);
    } else if (mode == 3) {
        addBridgeablePair(values);
    } else {
        addRandomSet(values);
        if (rnd.next(0, 1)) addHardPair(values);
        if (rnd.next(0, 1)) addBridgeablePair(values);
    }

    vector<int> a(values.begin(), values.end());
    while ((int)a.size() > 14) a.pop_back();
    shuffle(a.begin(), a.end());

    println((int)a.size());
    println(a);
    return 0;
}
