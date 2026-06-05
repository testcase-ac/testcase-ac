#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const long long MIN_X = -1000000000LL;
const long long MAX_X = 1000000000LL;

void addUnique(vector<long long>& xs, set<long long>& used, long long x) {
    if (x < MIN_X || x > MAX_X || used.count(x)) return;
    xs.push_back(x);
    used.insert(x);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<long long> xs;
    set<long long> used;

    if (mode == 0) {
        long long a = rnd.next(-20, 20);
        long long d = rnd.next(1, 30);
        xs = {a, a + d};
    } else if (mode == 1) {
        int n = rnd.next(2, 16);
        long long start = rnd.next(-100, 100);
        if ((start & 1LL) != rnd.next(0, 1)) ++start;
        for (int i = 0; i < n; ++i) xs.push_back(start + 2LL * i);
    } else if (mode == 2) {
        int n = rnd.next(3, 24);
        long long base = rnd.next(-200, 200);
        for (int i = 0; i < n; ++i) addUnique(xs, used, base + rnd.next(-25, 25));
        for (long long x = base - 30; (int)xs.size() < n; ++x) addUnique(xs, used, x);
    } else if (mode == 3) {
        int n = rnd.next(4, 30);
        long long base = rnd.next(-500, 500);
        for (int i = 0; i < n; ++i) xs.push_back(base + i);
    } else if (mode == 4) {
        vector<long long> candidates = {
            MIN_X,
            MIN_X + 1,
            MIN_X + rnd.next(2, 20),
            -rnd.next(0, 20),
            rnd.next(0, 20),
            MAX_X - rnd.next(2, 20),
            MAX_X - 1,
            MAX_X,
        };
        shuffle(candidates.begin(), candidates.end());
        int n = rnd.next(2, (int)candidates.size());
        for (long long x : candidates) {
            addUnique(xs, used, x);
            if ((int)xs.size() == n) break;
        }
    } else {
        int n = rnd.next(5, 28);
        long long base = rnd.next(-1000, 1000);
        for (int i = 0; i < n; ++i) {
            long long gap = rnd.any(vector<long long>{1, 2, 3, 5, 8, 13});
            addUnique(xs, used, base + i * gap + rnd.next(-2, 2));
        }
        for (long long x = base - 50; (int)xs.size() < n; ++x) addUnique(xs, used, x);
    }

    shuffle(xs.begin(), xs.end());
    println((int)xs.size());
    println(xs);

    return 0;
}
