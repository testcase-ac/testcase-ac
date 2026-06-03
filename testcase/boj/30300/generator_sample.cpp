#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

constexpr int kMaxA = (1 << 30) - 1;

int randomValue(int mode) {
    if (mode == 0) return rnd.next(0, 31);
    if (mode == 1) return rnd.next(0, 255);
    if (mode == 2) return kMaxA ^ rnd.next(0, 255);
    if (mode == 3) return 1 << rnd.next(0, 29);
    return rnd.next(0, kMaxA);
}

vector<int> makeCase() {
    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    vector<int> a;

    if (mode == 0) {
        int mexPrefix = rnd.next(0, min(n, 10));
        for (int i = 0; i < mexPrefix; ++i) a.push_back(i);
        while ((int)a.size() < n) a.push_back(rnd.next(0, 31));
    } else if (mode == 1) {
        int mask = (1 << rnd.next(1, 10)) - 1;
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(0, mask));
    } else if (mode == 2) {
        int base = rnd.next(0, kMaxA);
        for (int i = 0; i < n; ++i) a.push_back(base | rnd.next(0, 255));
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int bit = rnd.next(0, 29);
            int extra = rnd.next(0, (1 << min(bit + 1, 10)) - 1);
            a.push_back((1 << bit) | extra);
        }
    } else if (mode == 4) {
        int distinct = rnd.next(1, min(n, 6));
        vector<int> pool;
        for (int i = 0; i < distinct; ++i) pool.push_back(randomValue(rnd.next(0, 4)));
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    } else {
        for (int i = 0; i < n; ++i) a.push_back(randomValue(rnd.next(0, 4)));
    }

    shuffle(a.begin(), a.end());
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    vector<vector<int>> cases;
    cases.reserve(t);
    int totalN = 0;

    for (int tc = 0; tc < t; ++tc) {
        vector<int> a = makeCase();
        totalN += (int)a.size();
        cases.push_back(a);
    }

    if (rnd.next(0, 3) == 0 && totalN + 1 <= 100000) {
        vector<int> edgeValues = {0, 1, kMaxA};
        cases.push_back(vector<int>{rnd.any(edgeValues)});
    }

    println((int)cases.size());
    for (const vector<int>& a : cases) {
        println((int)a.size());
        println(a);
    }

    return 0;
}
