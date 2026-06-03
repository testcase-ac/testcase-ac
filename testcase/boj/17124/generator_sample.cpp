#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

namespace {
constexpr int MAX_VALUE = 1000000000;

int randomUnused(set<int>& used, int lo, int hi) {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        int value = rnd.next(lo, hi);
        if (used.insert(value).second) return value;
    }
    for (int value = lo; value <= hi; ++value) {
        if (used.insert(value).second) return value;
    }
    quitf(_fail, "no unused value in requested range");
}

void shuffleValues(vector<int>& values) {
    shuffle(values.begin(), values.end());
}

vector<int> makeAroundTargets(const vector<int>& targets, int count, int span) {
    set<int> used;
    vector<int> values;
    for (int i = 0; i < count; ++i) {
        int base = targets[rnd.next((int)targets.size())];
        int lo = max(1, base - span);
        int hi = min(MAX_VALUE, base + span);
        int available = hi - lo + 1;
        if ((int)used.size() < available) {
            values.push_back(randomUnused(used, lo, hi));
        } else {
            values.push_back(randomUnused(used, 1, MAX_VALUE));
        }
    }
    shuffleValues(values);
    return values;
}

vector<int> makeRandomDistinct(int count, int lo, int hi) {
    set<int> used;
    vector<int> values;
    for (int i = 0; i < count; ++i) {
        values.push_back(randomUnused(used, lo, hi));
    }
    shuffleValues(values);
    return values;
}

void printCase(const vector<int>& a, const vector<int>& b) {
    println((int)a.size(), (int)b.size());
    println(a);
    println(b);
}
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 5);

        if (mode == 0) {
            int m = rnd.next(2, 7);
            vector<int> b = makeRandomDistinct(m, 2, 80);
            sort(b.begin(), b.end());

            set<int> usedA;
            vector<int> a;
            for (int i = 1; i < m && (int)a.size() < rnd.next(3, 9); ++i) {
                int left = b[i - 1];
                int right = b[i];
                if ((left + right) % 2 == 0) {
                    int mid = (left + right) / 2;
                    if (usedA.insert(mid).second) a.push_back(mid);
                }
                if (usedA.insert(left + 1).second) a.push_back(left + 1);
                if (usedA.insert(right - 1).second) a.push_back(right - 1);
            }
            while ((int)a.size() < 3) a.push_back(randomUnused(usedA, 1, 90));
            shuffleValues(a);
            shuffleValues(b);
            printCase(a, b);
        } else if (mode == 1) {
            int n = rnd.next(3, 9);
            int pivot = rnd.next(1, MAX_VALUE);
            vector<int> a = makeRandomDistinct(n, 1, MAX_VALUE);
            vector<int> b{pivot};
            printCase(a, b);
        } else if (mode == 2) {
            vector<int> b;
            int low = rnd.next(1, 20);
            int high = rnd.next(MAX_VALUE - 30, MAX_VALUE);
            b.push_back(low);
            b.push_back(high);
            int extra = rnd.next(0, 4);
            set<int> usedB(b.begin(), b.end());
            for (int i = 0; i < extra; ++i) b.push_back(randomUnused(usedB, 100, MAX_VALUE - 100));

            set<int> usedA;
            vector<int> a;
            a.push_back(randomUnused(usedA, 1, 25));
            a.push_back(randomUnused(usedA, MAX_VALUE - 25, MAX_VALUE));
            while ((int)a.size() < rnd.next(4, 9)) {
                a.push_back(randomUnused(usedA, 1, MAX_VALUE));
            }
            shuffleValues(a);
            shuffleValues(b);
            printCase(a, b);
        } else if (mode == 3) {
            int m = rnd.next(3, 8);
            vector<int> b = makeRandomDistinct(m, 10, 200);
            int n = rnd.next(4, 10);
            vector<int> a = makeAroundTargets(b, n, rnd.next(1, 12));
            printCase(a, b);
        } else if (mode == 4) {
            int n = rnd.next(8, 14);
            int m = rnd.next(8, 14);
            int start = rnd.next(1, 100);
            vector<int> a, b;
            for (int i = 0; i < n; ++i) a.push_back(start + 2 * i);
            for (int i = 0; i < m; ++i) b.push_back(start + 2 * i + 1);
            shuffleValues(a);
            shuffleValues(b);
            printCase(a, b);
        } else {
            int n = rnd.next(3, 10);
            int m = rnd.next(3, 10);
            vector<int> a = makeRandomDistinct(n, 1, MAX_VALUE);
            vector<int> b = makeRandomDistinct(m, 1, MAX_VALUE);
            printCase(a, b);
        }
    }

    return 0;
}
