#include "testlib.h"

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

int n;
int maxValue;
vector<int> targetMedian;

struct Answer {
    vector<int> values;
};

Answer readAnswer(InStream& stream) {
    vector<int> values(2 * n - 1);
    vector<int> seen(maxValue + 1, 0);
    Fenwick prefix(maxValue);

    for (int i = 0; i < 2 * n - 1; ++i) {
        values[i] = stream.readInt(1, maxValue, format("a[%d]", i + 1).c_str());
        if (seen[values[i]]) {
            stream.quitf(_wa, "value %d appears more than once", values[i]);
        }
        seen[values[i]] = 1;
        prefix.add(values[i], 1);

        if (i % 2 == 0) {
            int medianIndex = i / 2;
            int expected = targetMedian[medianIndex];
            int less = prefix.sum(expected - 1);
            int lessOrEqual = prefix.sum(expected);
            int rank = medianIndex + 1;

            if (less >= rank || lessOrEqual < rank) {
                stream.quitf(_wa,
                             "prefix %d has median different from %d",
                             i + 1,
                             expected);
            }
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after permutation");
    }
    return {values};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    maxValue = 2 * n - 1;
    targetMedian.resize(n);
    for (int i = 0; i < n; ++i) {
        targetMedian[i] = inf.readInt();
    }

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid permutation with matching prefix medians");
}
