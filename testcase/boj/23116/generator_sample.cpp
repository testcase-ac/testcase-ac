#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

constexpr int MAX_VALUE = (1 << 20) - 1;

vector<int> shuffled(vector<int> values) {
    shuffle(values.begin(), values.end());
    return values;
}

int smallMask() {
    return rnd.next(0, (1 << rnd.next(1, 10)) - 1);
}

vector<int> makePossibleSet() {
    int n = rnd.next(2, 9);
    int base = smallMask();
    vector<int> candidates;
    for (int extra = 1; extra < (1 << 12); ++extra) {
        candidates.push_back(base | extra);
    }
    shuffle(candidates.begin(), candidates.end());

    set<int> values;
    values.insert(base);
    for (int value : candidates) {
        values.insert(value);
        if ((int)values.size() == n) break;
    }
    return shuffled(vector<int>(values.begin(), values.end()));
}

vector<int> makeImpossibleSet() {
    int n = rnd.next(2, 8);
    int base = rnd.next(0, (1 << 8) - 1);
    vector<int> extras;
    for (int extra = 1; extra < (1 << 12); ++extra) {
        if ((extra & (1 << 8) & (1 << 9)) == 0) {
            extras.push_back(extra);
        }
    }
    shuffle(extras.begin(), extras.end());

    set<int> values;
    values.insert(base | (1 << 8));
    values.insert(base | (1 << 9));
    for (int extra : extras) {
        if ((base | extra) == base) continue;
        values.insert(base | extra);
        if ((int)values.size() == n) break;
    }
    return shuffled(vector<int>(values.begin(), values.end()));
}

vector<int> makeBoundarySet() {
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        int middle = rnd.next(1, MAX_VALUE - 1);
        return shuffled({0, middle, MAX_VALUE});
    }
    if (mode == 1) {
        int bit = 1 << rnd.next(0, 19);
        return shuffled({bit, MAX_VALUE});
    }
    return shuffled({0});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);
    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int mode = rnd.next(0, 4);
        vector<int> values;
        if (mode == 0) {
            values = {rnd.next(0, MAX_VALUE)};
        } else if (mode <= 2) {
            values = makePossibleSet();
        } else if (mode == 3) {
            values = makeImpossibleSet();
        } else {
            values = makeBoundarySet();
        }

        println((int)values.size());
        println(values);
    }

    return 0;
}
