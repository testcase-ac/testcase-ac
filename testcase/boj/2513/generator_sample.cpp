#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int pickStudents(int k, int mode) {
    if (mode == 0) return rnd.next(1, min(2000, k));
    if (mode == 1) return rnd.next(max(1, k - 2), min(2000, k + 2));
    if (mode == 2) return rnd.next(1, 2000);
    return rnd.any(vector<int>{1, min(2000, k), 2000});
}

void addRange(vector<int>& candidates, set<int>& seen, int lo, int hi, int s) {
    for (int x = lo; x <= hi; ++x) {
        if (x == s || seen.count(x)) continue;
        seen.insert(x);
        candidates.push_back(x);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    int k = (mode == 1 ? rnd.next(1, 5) : rnd.next(1, 40));
    if (mode == 4) k = rnd.any(vector<int>{1, 2, 1999, 2000});

    int s = rnd.next(5, 99995);
    if (mode == 2) s = rnd.any(vector<int>{0, 1, 99999, 100000});
    if (mode == 3) s = rnd.next(100, 99900);

    vector<pair<int, int>> apartments;

    vector<int> candidates;
    set<int> seen;
    int nearSpan = rnd.next(max(n + 2, 16), 90);

    if (mode == 2) {
        if (s != 0) {
            seen.insert(0);
            candidates.push_back(0);
        }
        if (s != 100000) {
            seen.insert(100000);
            candidates.push_back(100000);
        }
    }

    if (mode != 5) {
        addRange(candidates, seen, max(0, s - nearSpan), max(0, s - 1), s);
    }
    if (mode != 3) {
        addRange(candidates, seen, min(100000, s + 1), min(100000, s + nearSpan), s);
    }
    addRange(candidates, seen, 0, min(100000, 3 * n), s);
    addRange(candidates, seen, max(0, 100000 - 3 * n), 100000, s);

    shuffle(candidates.begin(), candidates.end());
    for (int i = 0; i < n; ++i) {
        apartments.push_back({candidates[i], pickStudents(k, mode % 4)});
    }

    shuffle(apartments.begin(), apartments.end());

    println(n, k, s);
    for (const auto& apartment : apartments) {
        println(apartment.first, apartment.second);
    }

    return 0;
}
