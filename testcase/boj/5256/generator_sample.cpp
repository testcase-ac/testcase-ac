#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

class Fenwick {
public:
    explicit Fenwick(int n) : tree(n + 1, 0) {}

    void add(int idx, int value) {
        for (int i = idx; i < (int)tree.size(); i += i & -i) {
            tree[i] += value;
        }
    }

    int sum(int idx) const {
        int result = 0;
        for (int i = idx; i > 0; i -= i & -i) {
            result += tree[i];
        }
        return result;
    }

private:
    vector<int> tree;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int sizeMode = rnd.next(0, 4);
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode == 1) {
        n = rnd.next(2, 6);
    } else {
        n = rnd.next(7, 20);
    }

    int maxValue = 2 * n - 1;
    vector<int> b;
    set<int> unused;
    Fenwick selected(maxValue);
    for (int value = 1; value <= maxValue; ++value) {
        unused.insert(value);
    }

    auto useValue = [&](int value) {
        unused.erase(value);
        selected.add(value, 1);
    };

    auto useLessThan = [&](int value, int count) {
        for (int used = 0; used < count; ++used) {
            auto it = unused.lower_bound(value);
            --it;
            selected.add(*it, 1);
            unused.erase(it);
        }
    };

    auto useGreaterThan = [&](int value, int count) {
        for (int used = 0; used < count; ++used) {
            auto it = unused.upper_bound(value);
            selected.add(*it, 1);
            unused.erase(it);
        }
    };

    auto countLessThan = [&](int value) {
        int count = 0;
        for (int candidate : unused) {
            if (candidate >= value) {
                break;
            }
            ++count;
        }
        return count;
    };

    auto countGreaterThan = [&](int value) {
        int count = 0;
        for (auto it = unused.upper_bound(value); it != unused.end(); ++it) {
            ++count;
        }
        return count;
    };

    int firstMode = rnd.next(0, 3);
    int first = firstMode == 0 ? 1 : firstMode == 1 ? maxValue : rnd.next(1, maxValue);
    b.push_back(first);
    useValue(first);

    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            continue;
        }

        vector<int> candidates;
        for (int target = 1; target <= maxValue; ++target) {
            int lessNow = selected.sum(target - 1);
            int greaterNow = (2 * i - 1) - selected.sum(target);
            bool hasTarget = unused.find(target) == unused.end();

            int needLess = i - lessNow;
            int needGreater = i - greaterNow;
            int needTarget = hasTarget ? 0 : 1;

            if (needLess >= 0 && needGreater >= 0 &&
                needLess + needGreater + needTarget == 2) {
                if (countLessThan(target) >= needLess &&
                    countGreaterThan(target) >= needGreater) {
                    candidates.push_back(target);
                }
            }
        }

        int target;
        int mode = rnd.next(0, 4);
        if (mode == 0) {
            target = candidates.front();
        } else if (mode == 1) {
            target = candidates.back();
        } else if (mode == 2) {
            target = candidates[(int)candidates.size() / 2];
        } else {
            target = rnd.any(candidates);
        }

        int lessNow = selected.sum(target - 1);
        int greaterNow = (2 * i - 1) - selected.sum(target);
        bool hasTarget = unused.find(target) == unused.end();
        int needLess = i - lessNow;
        int needGreater = i - greaterNow;

        if (!hasTarget) {
            useValue(target);
        }
        useLessThan(target, needLess);
        useGreaterThan(target, needGreater);
        b.push_back(target);
    }

    println(n);
    println(b);

    return 0;
}
