#include "testlib.h"

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
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    int maxValue = 2 * n - 1;
    vector<int> b = inf.readInts(n, 1, maxValue, "b_i");
    inf.readEoln();
    inf.readEof();

    set<int> unused;
    for (int value = 1; value <= maxValue; ++value) {
        unused.insert(value);
    }

    Fenwick selected(maxValue);
    auto useValue = [&](int value) {
        auto it = unused.find(value);
        ensuref(it != unused.end(), "value %d is required more than once", value);
        unused.erase(it);
        selected.add(value, 1);
    };

    auto useLessThan = [&](int value, int count, int step) {
        for (int used = 0; used < count; ++used) {
            auto it = unused.lower_bound(value);
            ensuref(it != unused.begin(),
                    "step %d needs %d unused values less than %d", step, count, value);
            --it;
            int chosen = *it;
            unused.erase(it);
            selected.add(chosen, 1);
        }
    };

    auto useGreaterThan = [&](int value, int count, int step) {
        for (int used = 0; used < count; ++used) {
            auto it = unused.upper_bound(value);
            ensuref(it != unused.end(),
                    "step %d needs %d unused values greater than %d", step, count, value);
            int chosen = *it;
            unused.erase(it);
            selected.add(chosen, 1);
        }
    };

    useValue(b[0]);

    for (int i = 1; i < n; ++i) {
        int target = b[i];
        int lessNow = selected.sum(target - 1);
        int greaterNow = (2 * i - 1) - selected.sum(target);
        bool hasTarget = unused.find(target) == unused.end();

        int needLess = i - lessNow;
        int needGreater = i - greaterNow;
        int needTarget = hasTarget ? 0 : 1;

        ensuref(needLess >= 0 && needGreater >= 0,
                "step %d cannot reduce counts around median %d", i + 1, target);
        ensuref(needLess + needGreater + needTarget == 2,
                "step %d cannot make %d the next prefix median", i + 1, target);

        if (needTarget) {
            useValue(target);
        }
        useLessThan(target, needLess, i + 1);
        useGreaterThan(target, needGreater, i + 1);
    }
}
